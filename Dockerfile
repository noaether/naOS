FROM gitpod/workspace-full-vnc

USER root

RUN curl -fsSL https://pkgs.tailscale.com/stable/ubuntu/focal.gpg | sudo apt-key add - \
     && curl -fsSL https://pkgs.tailscale.com/stable/ubuntu/focal.list | sudo tee /etc/apt/sources.list.d/tailscale.list \
     && apt-get update \
     && apt-get install -y tailscale
RUN update-alternatives --set ip6tables /usr/sbin/ip6tables-nft
RUN apt-get update && \
    apt-get install -y libgconf-2-4 libx11-dev libxkbfile-dev libsecret-1-dev libnss3 flex build-essential nasm genisoimage bochs bochs-sdl xorriso && \
    apt --fix-broken install && \
    rm -rf /var/lib/apt/lists/*
