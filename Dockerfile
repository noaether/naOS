FROM gitpod/workspace-full-vnc

USER root

RUN apt-get update && \
    apt-get install -y qemu-kvm qemu-system libgconf-2-4 libx11-dev libxkbfile-dev libsecret-1-dev libnss3 flex build-essential nasm genisoimage bochs bochs-sdl xorriso && \
    apt --fix-broken install && \
    rm -rf /var/lib/apt/lists/*
