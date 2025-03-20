# Use an image with MPI and OpenMP support
FROM ubuntu:latest

# Install dependencies
RUN apt-get update && apt-get install -y \
    openmpi-bin \
    openmpi-common \
    libopenmpi-dev \
    gcc \
    g++ \
    libomp-dev \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source files into the container
COPY . /app

# Compile the MPI + OpenMP program
RUN mpicc -fopenmp -o distributed_program main.c

# Set the command to run the MPI program
CMD ["mpirun", "--allow-run-as-root", "-np", "2", "./distributed_program"]
