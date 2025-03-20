FROM ubuntu:latest

RUN apt-get update && apt-get install -y \
    openmpi-bin \
    openmpi-common \
    libopenmpi-dev \
    gcc \
    g++ \
    libomp-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY . /app

RUN mpicc -fopenmp -o distributed_program main.c

CMD ["mpirun", "--allow-run-as-root", "-np", "2", "./distributed_program"]
