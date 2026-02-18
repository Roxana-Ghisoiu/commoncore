#!/bin/sh
set -e

# Required variables
: "${MYSQL_DATABASE:?Missing MYSQL_DATABASE}"
: "${MYSQL_USER:?Missing MYSQL_USER}"
: "${MYSQL_PASSWORD:?Missing MYSQL_PASSWORD}"
: "${MYSQL_ROOT_PASSWORD:?Missing MYSQL_ROOT_PASSWORD}"

# NEW: ensure runtime & log dirs exist
mkdir -p /run/mysqld /var/log/mysql
chown -R mysql:mysql /run/mysqld /var/log/mysql

# Data dir ownership
chown -R mysql:mysql /var/lib/mysql

# First run initialization
if [ ! -d "/var/lib/mysql/mysql" ]; then
  echo "[entrypoint] First run: initializing database..."
  mariadb-install-db --user=mysql --datadir=/var/lib/mysql --skip-test-db
  /usr/local/bin/init_db.sh
fi

# Run mysqld in foreground
exec mysqld --user=mysql --datadir=/var/lib/mysql --console