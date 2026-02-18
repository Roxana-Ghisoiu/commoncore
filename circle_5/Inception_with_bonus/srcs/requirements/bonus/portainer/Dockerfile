FROM debian:12-slim

RUN apt-get update && \
    apt-get install -y --no-install-recommends curl ca-certificates tini && \
    rm -rf /var/lib/apt/lists/*

RUN mkdir -p /opt/portainer
RUN curl -L https://github.com/portainer/portainer/releases/download/2.33.2/portainer-2.33.2-linux-amd64.tar.gz \
    -o /opt/portainer/portainer.tar.gz && \
    tar -xzf /opt/portainer/portainer.tar.gz -C /opt/portainer --strip-components=1 && \
    rm /opt/portainer/portainer.tar.gz

RUN mkdir -p /data

EXPOSE 9000

ENTRYPOINT ["/usr/bin/tini", "--"]
CMD ["/opt/portainer/portainer", "--data=/data"]
