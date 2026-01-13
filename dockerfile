# ---------- Stage 1: Build ----------
FROM ubuntu:22.04 AS builder

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libcurl4-openssl-dev \
    zlib1g-dev \
    nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN cmake -S . -B build \
    -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build -j$(nproc)

# ---------- Stage 2: Runtime ----------
FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

# -------- Runtime Environment Variables --------
ENV URL=""
ENV KEY=""
ENV EXCHANGE_1=""
ENV EXCHANGE_2=""

RUN apt-get update && apt-get install -y \
    libcurl4 \
    zlib1g \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY --from=builder /app/build/main .

CMD ["./main"]
