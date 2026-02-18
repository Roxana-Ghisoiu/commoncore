FROM debian:12-slim

RUN apt-get update && apt-get install -y --no-install-recommends \
    nginx ca-certificates && \
    rm -rf /var/lib/apt/lists/*

# Nginx config for the static site
COPY conf/static_nginx.conf /etc/nginx/nginx.conf

# Static assets (HTML/CSS/images)
COPY site/ /usr/share/nginx/html/

# Ensure proper permissions for all static assets
RUN find /usr/share/nginx/html -type d -exec chmod 755 {} \; \
 && find /usr/share/nginx/html -type f -exec chmod 644 {} \;

EXPOSE 8000
CMD ["nginx", "-g", "daemon off;"]