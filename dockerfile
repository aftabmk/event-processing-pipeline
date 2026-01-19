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

# Copy compiled binary
COPY --from=builder /app/build/main /app/bin/main

# Copy lambda environment wrapper
COPY environment /app/environment

# IMPORTANT: Lambda entrypoint
ENTRYPOINT ["./environment/lambda"]
