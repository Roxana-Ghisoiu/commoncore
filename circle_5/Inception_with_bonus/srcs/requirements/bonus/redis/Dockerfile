FROM debian:12-slim

RUN apt-get update -y && apt-get upgrade -y && \
    apt-get install -y --no-install-recommends redis-server redis-tools ca-certificates && \
    rm -rf /var/lib/apt/lists/*

RUN useradd -m -s /usr/sbin/nologin redisuser && \
    mkdir -p /data && chown -R redisuser:redisuser /data

# config
COPY redis.conf /etc/redis/redis.conf
RUN chmod 644 /etc/redis/redis.conf && chown -R redisuser:redisuser /etc/redis

EXPOSE 6379
USER redisuser

ENTRYPOINT ["redis-server", "/etc/redis/redis.conf", "--appendonly", "yes"]
