
FROM debian:12-slim

# Install nginx + openssl, keep image small
RUN apt-get update && apt-get install -y --no-install-recommends \
    nginx openssl ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Self-signed certificate (OK for defense)
RUN mkdir -p /etc/nginx/ssl && \
    openssl req -x509 -nodes -newkey rsa:4096 \
      -keyout /etc/nginx/ssl/selfsigned.key \
      -out /etc/nginx/ssl/selfsigned.crt \
      -days 365 \
      -subj "/C=LU/ST=Luxemburg/L=Luxemburg/O=42/CN=rghisoiu.42.fr"

# Runtime dirs + docroot (WP volume will mount here)
RUN mkdir -p /run/nginx /var/www/html

# Config + entrypoint
COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY tools/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh

EXPOSE 443
ENTRYPOINT ["/entrypoint.sh"]
