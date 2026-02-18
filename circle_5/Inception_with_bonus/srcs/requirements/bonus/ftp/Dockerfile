# srcs/requirements/bonus/ftp/Dockerfile
FROM debian:12-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    vsftpd ca-certificates tzdata procps && \
    rm -rf /var/lib/apt/lists/*

# Create directory used by vsftpd for runtime files
RUN mkdir -p /var/run/vsftpd

# Copy configuration and entrypoint
COPY conf/vsftpd.conf /etc/vsftpd.conf
COPY tools/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

EXPOSE 21 21000-21010

ENTRYPOINT ["/entrypoint.sh"]
