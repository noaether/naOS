FROM gitpod/workspace-full-vnc

RUN sudo apt-get update && \
    sudo apt-get install -y libgconf2-4 libx11-dev libxkbfile-dev libsecret-1-dev libnss3 && \
    sudo rm -rf /var/lib/apt/lists/*