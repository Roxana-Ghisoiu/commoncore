#!/bin/sh
set -e

echo "→ Starting Adminer..."

echo "→ Waiting for MariaDB to be ready..."
while ! nc -z mariadb 3306 2>/dev/null; do
    echo "   MariaDB is unavailable - sleeping"
    sleep 2
done
echo "✓ MariaDB is ready"

echo "✓ Adminer is ready to serve on port 8080"
echo "→ Starting PHP built-in server..."

exec php -S 0.0.0.0:8080 -t /var/www/html