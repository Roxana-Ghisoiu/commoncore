#!/bin/sh
set -e

mkdir -p /run/php
chown -R www-data:www-data /var/www/html || true

# prepare files (safe even if DB not up yet)
/setup.sh || true

# Run php-fpm in foreground (no hacky loops)
if command -v php-fpm8.2 >/dev/null 2>&1; then
  exec php-fpm8.2 -F
elif command -v php-fpm8.1 >/dev/null 2>&1; then
  exec php-fpm8.1 -F
else
  exec php-fpm -F
fi