#!/bin/sh
set -e

mkdir -p /run/php
chown -R www-data:www-data /var/www/html || true

# prepare files (safe even if DB not up yet)
/setup.sh || true

# Redis Object Cache (minimal but safe) — INSERTED BLOCK
if command -v wp >/dev/null 2>&1 && wp --path=/var/www/html --allow-root core is-installed; then
  chown -R www-data:www-data /var/www/html

  if ! wp --path=/var/www/html plugin is-installed redis-cache --allow-root; then
    wp --path=/var/www/html plugin install redis-cache --activate --allow-root || true
  else
    wp --path=/var/www/html plugin activate redis-cache --allow-root || true
  fi

  wp --path=/var/www/html config set WP_REDIS_HOST "${WP_REDIS_HOST:-redis}" --type=constant --allow-root || true
  wp --path=/var/www/html config set WP_REDIS_PORT "${WP_REDIS_PORT:-6379}" --type=constant --allow-root || true
  if [ -n "${WP_REDIS_PASSWORD:-}" ]; then
    wp --path=/var/www/html config set WP_REDIS_PASSWORD "${WP_REDIS_PASSWORD}" --type=constant --allow-root || true
  fi

  wp --path=/var/www/html redis enable --allow-root || true
fi

# Run php-fpm in foreground (no hacky loops)
if command -v php-fpm8.2 >/dev/null 2>&1; then
  exec php-fpm8.2 -F
elif command -v php-fpm8.1 >/dev/null 2>&1; then
  exec php-fpm8.1 -F
else
  exec php-fpm -F
fi
