#!/bin/sh
set -e

# --- ENV defaults ---
: "${FTP_USER:=wpftp}"
: "${FTP_PASS:?FTP_PASS env is required}"
: "${FTP_HOME:=/var/www/html}"
: "${PASV_ADDRESS:=127.0.0.1}"
: "${PASV_MIN_PORT:=21000}"
: "${PASV_MAX_PORT:=21010}"

# Create home directory if missing (mounted volume should provide it)
mkdir -p "$FTP_HOME"

# Create FTP user if not exists, shell disabled
if ! id "$FTP_USER" >/dev/null 2>&1; then
    useradd -m -d "$FTP_HOME" -s /usr/sbin/nologin "$FTP_USER"
fi

echo "${FTP_USER}:${FTP_PASS}" | chpasswd

# Ensure ownership; if the volume already has different owners, this won't fail the container
chown -R "${FTP_USER}:${FTP_USER}" "$FTP_HOME" 2>/dev/null || true

# Tweak passive settings in vsftpd.conf
sed -i "s|^pasv_address=.*$|pasv_address=${PASV_ADDRESS}|" /etc/vsftpd.conf || true
sed -i "s|^pasv_min_port=.*$|pasv_min_port=${PASV_MIN_PORT}|" /etc/vsftpd.conf || true
sed -i "s|^pasv_max_port=.*$|pasv_max_port=${PASV_MAX_PORT}|" /etc/vsftpd.conf || true

# Run vsftpd in foreground
exec /usr/sbin/vsftpd /etc/vsftpd.conf
