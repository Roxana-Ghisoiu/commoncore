#!/bin/sh
set -e
mkdir -p /run/nginx
exec nginx -g 'daemon off;'
