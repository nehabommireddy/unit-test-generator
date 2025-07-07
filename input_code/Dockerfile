# Start with the base Ubuntu image
FROM ubuntu:22.04

# Set the timezone
ENV TZ=UTC
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install necessary dependencies
RUN apt-get update -yqq \
    && apt-get install -yqq --no-install-recommends \
    software-properties-common \
    sudo curl wget cmake make pkg-config locales git \
    gcc-11 g++-11 openssl libssl-dev libjsoncpp-dev uuid-dev \
    zlib1g-dev libc-ares-dev postgresql-server-dev-all \
    libmariadb-dev libsqlite3-dev libhiredis-dev \
    && rm -rf /var/lib/apt/lists/* \
    && locale-gen en_US.UTF-8

# Set environment variables
ENV LANG=en_US.UTF-8 \
    LANGUAGE=en_US:en \
    LC_ALL=en_US.UTF-8 \
    CC=gcc-11 \
    CXX=g++-11 \
    AR=gcc-ar-11 \
    RANLIB=gcc-ranlib-11 \
    IROOT=/install

# Clone and build Drogon
ENV DROGON_ROOT="$IROOT/drogon"
RUN git clone https://github.com/drogonframework/drogon $DROGON_ROOT
WORKDIR $DROGON_ROOT
RUN ./build.sh

# Copy your app's source code
COPY . /app
WORKDIR /app

# Pull submodules if used
RUN git submodule update --init --recursive

# Build your Drogon app
RUN mkdir -p build && cd build && cmake .. && make -j$(nproc)

# Final working directory and run command
WORKDIR /app
CMD ["./build/org_chart"] 