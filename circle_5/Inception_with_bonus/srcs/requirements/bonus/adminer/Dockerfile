FROM debian:12-slim
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      php-cli php-mysql curl netcat-openbsd ca-certificates \
 && rm -rf /var/lib/apt/lists/*

WORKDIR /var/www/html
RUN curl -fsSL https://github.com/vrana/adminer/releases/download/v4.8.1/adminer-4.8.1.php -o index.php \
 && chown -R www-data:www-data /var/www/html

COPY tools/adminer-entrypoint.sh /usr/local/bin/adminer-entrypoint.sh
RUN chmod +x /usr/local/bin/adminer-entrypoint.sh

EXPOSE 8080
ENTRYPOINT ["/usr/local/bin/adminer-entrypoint.sh"]
