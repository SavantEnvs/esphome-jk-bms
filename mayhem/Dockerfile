# syntax=docker/dockerfile:1.7
#
# Commit image for esphome-jk-bms: ESPHome external components (JK-BMS / JK balancer / Heltec balancer
# protocol decoders) built against ESPHome's host platform, with libFuzzer harnesses per wire parser.
FROM ghcr.io/savantenvs/base:20261023

ARG COMMIT
ARG REPO_URL
ARG SOURCE_DATE_EPOCH
ARG SANITIZER_FLAGS
ARG COVERAGE_FLAGS=
ARG MAYHEM_JOBS=

# googletest for upstream's own C++ unit suite (tests/components/*/*_test.cpp), run by mayhem/test.sh.
USER root
RUN [ -n "$SOURCE_DATE_EPOCH" ] && repro-sources-list.sh || true ; \
    apt-get update && apt-get install -yq --no-install-recommends libgtest-dev \
 && rm -rf /var/lib/apt/lists/*

# ESPHome (the framework the components are built into; upstream's run-cpp-tests.sh clones its `dev`
# branch). Pinned to a commit, source only: build.sh compiles the host-platform core it needs from here.
ARG ESPHOME_REV=8c36bc172f4cb5f41db4ac79ec90be801c76ccbc
ARG ESPHOME_SHA256=50546dc04b0929f3d30136390bb12635d181f7f6ecf545df29b41f50bee1e23b
RUN d=/opt/toolchains/deps/esphome-${ESPHOME_REV} && mkdir -p "$d/src" \
 && curl -fsSL -o /tmp/esphome.tgz https://github.com/esphome/esphome/archive/${ESPHOME_REV}.tar.gz \
 && echo "${ESPHOME_SHA256}  /tmp/esphome.tgz" | sha256sum -c - \
 && tar -xzf /tmp/esphome.tgz --strip-components=1 -C "$d/src" \
 && rm -f /tmp/esphome.tgz && chmod -R a+rX,go-w "$d" \
 && ln -s "$d" /opt/toolchains/deps/esphome
ENV ESPHOME_SRC=/opt/toolchains/deps/esphome/src

USER mayhem
WORKDIR /mayhem
COPY --chown=2000:2000 . /mayhem

RUN if [ -x /opt/mayhem/ccache/prefill ]; then /opt/mayhem/ccache/prefill bash mayhem/build.sh; \
    else bash mayhem/build.sh; fi

RUN if [ -f mayhem/test.sh ]; then bash mayhem/test.sh; else echo "no mayhem/test.sh"; fi

LABEL org.opencontainers.image.source="${REPO_URL}" \
      org.opencontainers.image.revision="${COMMIT}" \
      rlenv.tier="commit" \
      rlenv.source_date_epoch="${SOURCE_DATE_EPOCH}" \
      rlenv.user="mayhem"

USER mayhem
WORKDIR /mayhem
