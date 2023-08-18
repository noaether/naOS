FROM gitpod/workspace-full-vnc

RUN sudo apt-get update && \
    sudo apt-get install -y libgconf-2-4 libx11-dev libxkbfile-dev libsecret-1-dev libnss3 flex build-essential nasm genisoimage bochs bochs-sdl && \
    sudo apt --fix-broken install && \
    sudo rm -rf /var/lib/apt/lists/*
