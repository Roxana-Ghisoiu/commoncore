FROM debian:12-slim

# PHP-FPM + extensions + tools (no passwords, no latest tag)
RUN apt-get update && apt-get install -y --no-install-recommends \
    php-fpm php-mysql php-cli php-curl php-xml php-gd php-mbstring \
    curl ca-certificates tar \
 && rm -rf /var/lib/apt/lists/*

# WP-CLI (used by setup.sh later when we add MariaDB)
RUN curl -fsSL https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar -o /usr/local/bin/wp \
 && chmod +x /usr/local/bin/wp

# Replace the default PHP-FPM pool so it listens on TCP 0.0.0.0:9000 (cross-container)
COPY conf/www.conf /etc/php/8.2/fpm/pool.d/www.conf

# Runtime dirs and working dir (WordPress lives here; volume mounts over it)
WORKDIR /var/www/html
RUN mkdir -p /run/php

# Entrypoint & setup (no hacky loops; php-fpm runs in foreground)
COPY tools/setup.sh /setup.sh
COPY tools/entrypoint.sh /entrypoint.sh
RUN chmod +x /setup.sh /entrypoint.sh

EXPOSE 9000
ENTRYPOINT ["/entrypoint.sh"]