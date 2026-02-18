# srcs/requirements/mariadb/Dockerfile
FROM debian:12-slim


RUN apt-get update && apt-get install -y --no-install-recommends \
mariadb-server mariadb-client tzdata ca-certificates tini \
&& rm -rf /var/lib/apt/lists/*


# MariaDB configuration
COPY conf/my.cnf /etc/mysql/my.cnf


# Init/entry scripts
COPY tools/entrypoint.sh /usr/local/bin/entrypoint.sh
COPY tools/init_db.sh /usr/local/bin/init_db.sh
RUN chmod +x /usr/local/bin/entrypoint.sh /usr/local/bin/init_db.sh


# Data dir (will be a bind mount)
RUN mkdir -p /var/lib/mysql && chown -R mysql:mysql /var/lib/mysql


EXPOSE 3306
ENTRYPOINT ["/usr/bin/tini", "--", "/usr/local/bin/entrypoint.sh"]