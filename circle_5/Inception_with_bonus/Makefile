# ===== Inception — ultra-clean Makefile (mandatory + bonus) =====
MAKEFLAGS += --no-print-directory -s

COMPOSE := docker compose -f srcs/docker-compose.yml
DATA    := /home/$(USER)/data
WP_DIR  := $(DATA)/wp
DB_DIR  := $(DATA)/db
PORTAINER_DIR := $(DATA)/portainer

.PHONY: all build up down re ps logs \
        mariadb wordpress nginx redis ftp adminer static_page portainer \
        clean-data fclean prepare \
        wp-db-grants re-wp wp-fix logs-wp-done

all: up

build: prepare
	$(COMPOSE) build

# Full stack: start services, ensure DB grants, restart WP to complete setup
up: prepare
	$(COMPOSE) up -d --build mariadb
	$(COMPOSE) up -d --build wordpress nginx redis ftp adminer static_page portainer
	$(MAKE) wp-db-grants
	$(MAKE) re-wp

down:
	$(COMPOSE) down

re: down up

ps:
	$(COMPOSE) ps

logs:
	$(COMPOSE) logs -f

# --- Per-service bring-up (mandatory + bonus) --------------------------------
mariadb: prepare
	$(COMPOSE) up -d --build mariadb

wordpress: prepare
	$(COMPOSE) up -d --build wordpress

nginx: prepare
	$(COMPOSE) up -d --build nginx

redis: prepare
	$(COMPOSE) up -d --build redis

ftp: prepare
	$(COMPOSE) up -d --build ftp

adminer: prepare
	$(COMPOSE) up -d --build adminer

static_page: prepare
	$(COMPOSE) up -d --build static_page

portainer: prepare
	$(COMPOSE) up -d --build portainer

# --- Helpers (silent) --------------------------------------------------------

# Ensure DB and user grants exist (idempotent) — completely silent
wp-db-grants:
	$(COMPOSE) exec -T mariadb sh -lc 'mariadb -uroot -p"$$MYSQL_ROOT_PASSWORD" -e "\
		CREATE DATABASE IF NOT EXISTS \`$$MYSQL_DATABASE\` CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci; \
		CREATE USER IF NOT EXISTS \`$$MYSQL_USER\`@\"%\" IDENTIFIED BY \"$$MYSQL_PASSWORD\"; \
		ALTER  USER            \`$$MYSQL_USER\`@\"%\" IDENTIFIED BY \"$$MYSQL_PASSWORD\"; \
		GRANT ALL PRIVILEGES ON \`$$MYSQL_DATABASE\`.* TO \`$$MYSQL_USER\`@\"%\"; \
		FLUSH PRIVILEGES; "' >/dev/null 2>&1

# Restart WP so setup.sh finishes — completely silent
re-wp:
	$(COMPOSE) restart wordpress >/dev/null 2>&1

# One-shot fixer (silent): grants + restart
wp-fix: wp-db-grants re-wp

# Follow WP logs until '--- DONE ---' then exit (kept verbose for usefulness)
logs-wp-done:
	$(COMPOSE) logs -f wordpress | sed '/--- DONE ---/ q'

# --- Cleaning ----------------------------------------------------------------

# Clean only DB data (no sudo). Silent except for docker compose.
clean-data:
	$(COMPOSE) down
	docker run --rm -v $(DATA):/target debian:12-slim sh -lc 'rm -rf /target/db/* || true' >/dev/null 2>&1

# Full clean (containers + volumes + host binds). Silent except for docker compose.
fclean:
	$(COMPOSE) down -v
	docker run --rm -v $(DATA):/target debian:12-slim sh -lc 'rm -rf /target/wp/* /target/db/* /target/portainer/* || true' >/dev/null 2>&1

prepare:
	mkdir -p $(WP_DIR) $(DB_DIR) $(PORTAINER_DIR)
