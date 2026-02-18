#!/bin/sh
set -e

# NEW: make sure socket directory exists
mkdir -p /run/mysqld
chown mysql:mysql /run/mysqld

sql=/tmp/init.sql
cat > "$sql" <<SQL
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
CREATE DATABASE IF NOT EXISTS \`${MYSQL_DATABASE}\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON \`${MYSQL_DATABASE}\`.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
SQL

# Start a temporary local-only server
mysqld --skip-networking --socket=/run/mysqld/mysqld.sock \
       --datadir=/var/lib/mysql --user=mysql --daemonize

# Wait for socket
for i in $(seq 1 50); do
  [ -S /run/mysqld/mysqld.sock ] && break
  sleep 0.2
  [ "$i" -eq 50 ] && echo "mysqld socket wait timeout" && exit 1
done

# Apply SQL and shutdown
mariadb --protocol=SOCKET --socket=/run/mysqld/mysqld.sock -uroot < "$sql"
mysqladmin --protocol=SOCKET --socket=/run/mysqld/mysqld.sock -uroot -p"${MYSQL_ROOT_PASSWORD}" shutdown
rm -f "$sql"
echo "[init_db] Done."
