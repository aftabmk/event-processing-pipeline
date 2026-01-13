# ---- Builder ----
FROM alpine:edge AS builder

RUN apk add --no-cache \
    build-base \
    cmake \
    zlib-dev \
    curl-dev

WORKDIR /app
COPY . .

RUN mkdir -p build
WORKDIR /app/build

RUN cmake .. -DCMAKE_BUILD_TYPE=Release \
    && cmake --build . -- -j$(nproc)

# ---- Runtime ----
FROM alpine:edge

# REQUIRED for C++ binaries
RUN apk add --no-cache \
    libstdc++ \
    libgcc \
    zlib \
    curl

WORKDIR /app

# Copy runtime assets
COPY data.json /app/data.json
COPY --from=builder /app/build/main /app/bin/main

WORKDIR /app/bin
ENTRYPOINT ["./main"]
