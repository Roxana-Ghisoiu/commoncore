#!/bin/sh
set -e

# -----------------------------------------------------------------------------
# WordPress container logs (non-blocking examples from the host):
#   docker logs wordpress
#   docker logs --tail 50 wordpress
#   timeout 10s docker logs -f wordpress
#   # During DB-less phase (auto-exit when skip message appears):
#   docker logs -f wordpress | sed '/MariaDB not available yet — skipping config\/install for now\./ q'
#   # After adding MariaDB (auto-exit when setup completes):
#   docker logs -f wordpress | sed '/--- DONE ---/ q'
# -----------------------------------------------------------------------------

# Ensure DOMAIN_NAME exists (used at install time)
: "${DOMAIN_NAME:?Missing DOMAIN_NAME in .env}"

# 1) Download WordPress core once (idempotent)
if [ ! -f /var/www/html/wp-settings.php ]; then
  wp core download --path=/var/www/html --allow-root
fi

# 2) DB-aware install: only run if MariaDB is reachable; otherwise skip cleanly
(
  set -e
  cd /var/www/html

  # Probe DB connectivity (silent if DB is absent)
  if php -r '
    $h=getenv("MYSQL_HOST") ?: "mariadb";
    $u=getenv("MYSQL_USER");
    $p=getenv("MYSQL_PASSWORD");
    $d=getenv("MYSQL_DATABASE");
    $m=@new mysqli($h, $u, $p, $d);
    exit($m && !$m->connect_errno ? 0 : 1);
  ' >/dev/null 2>&1; then

    # (1) Core safety guard
    [ -f wp-includes/version.php ] || wp core download --allow-root

    # (2) Create wp-config.php if missing
    [ -f wp-config.php ] || wp config create \
      --dbname="$MYSQL_DATABASE" \
      --dbuser="$MYSQL_USER" \
      --dbpass="$MYSQL_PASSWORD" \
      --dbhost="$MYSQL_HOST" \
      --allow-root

    # (3) Install WordPress if not installed
    wp core is-installed --allow-root || wp core install \
      --url="https://$DOMAIN_NAME" \
      --title="Inception Project" \
      --admin_user="$WP_ADMIN_USER" \
      --admin_password="$WP_ADMIN_PASSWORD" \
      --admin_email="$WP_ADMIN_EMAIL" \
      --skip-email \
      --allow-root

    # (4) Create the second (author) user if missing
    wp user get "$WP_USER_LOGIN" --field=ID --allow-root >/dev/null 2>&1 || wp user create \
      "$WP_USER_LOGIN" "$WP_USER_EMAIL" \
      --user_pass="$WP_USER_PASSWORD" \
      --role=author \
      --allow-root

    echo "--- DONE ---"
  else
    echo "[setup] MariaDB not available yet — skipping config/install for now."
  fi
)

# 3) Keep correct ownership
chown -R www-data:www-data /var/www/html