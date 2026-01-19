# ---- Builder ----
FROM alpine:edge AS builder

# Install build tools
RUN apk add --no-cache \
    build-base \
    cmake \
    git \
    zlib-dev \
    curl-dev \
    bash

# ---- Build AWS Lambda C++ Runtime ----
WORKDIR /opt
RUN git clone https://github.com/awslabs/aws-lambda-cpp.git
WORKDIR /opt/aws-lambda-cpp/build
RUN cmake .. -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release \
    && make -j$(nproc) \
    && make install

# ---- Build your Lambda executable ----
WORKDIR /app
COPY . .

RUN mkdir -p build
WORKDIR /app/build

# Build the main binary
RUN cmake .. -DCMAKE_BUILD_TYPE=Release -DAWS_LAMBDA_CPP_DIR=/usr/local \
    && cmake --build . --target main -- -j$(nproc)

# ---- Runtime ----
FROM alpine:edge

# Install minimal runtime dependencies
RUN apk add --no-cache \
    libstdc++ \
    libgcc \
    zlib \
    curl

WORKDIR /app

# Copy Lambda binary from builder
COPY --from=builder /app/build/main /app/main
RUN chmod +x /app/main

# Lambda ENTRYPOINT
ENTRYPOINT ["/app/main"]
