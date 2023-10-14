#!/bin/bash

export cc_prefix="$HOME/opt/cross"
export cc_target=i686-elf
export PATH="$cc_prefix/bin:$PATH"

export ncpu=$(($(nproc --all) - 2))  # Number of cores minus 2

# Ensure ncpu is at least 1
if [[ $ncpu -lt 1 ]]; then
    ncpu=1
fi

# Detect the package manager
pkg_manager=""

if command -v apt &>/dev/null; then
    pkg_manager="apt"
elif command -v yum &>/dev/null; then
    pkg_manager="yum"
elif command -v yay &>/dev/null; then
    pkg_manager="yay"  # Assuming yay is used for the Arch User Repository (AUR)
elif command -v pacman &>/dev/null; then
    pkg_manager="pacman"  # Assuming pacman is used for the Arch User Repository (AUR)
else
    echo "Unsupported package manager. Please install required packages manually and re-run the script."
    exit 1
fi

# Install required packages based on the detected package manager
case $pkg_manager in
    "apt")
        sudo apt update
        sudo apt install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev
        ;;
    "yum")
        wget https://nasm.us/nasm.repo -O /etc/yum.repos.d/nasm.repo
        sudo yum -y install gcc make bison flex gmp-devel mpfr-devel libmpc-devel texinfo isl-devel
        ;;
    "yay" | "pacman")
        yay -S --noconfirm base-devel gmp mpfr libmpc texinfo isl
        ;;
esac

# Remove any existing cross-compiler installation
rm -rf $HOME/src
rm -rf $cc_prefix

mkdir -p $HOME/src
cd $HOME/src

wget https://ftp.gnu.org/gnu/binutils/binutils-2.34.tar.xz
tar -xf binutils-2.34.tar.xz

wget https://ftp.gnu.org/gnu/gcc/gcc-9.4.0/gcc-9.4.0.tar.gz
tar -xf gcc-9.4.0.tar.gz

mkdir build-binutils
cd build-binutils
../binutils-2.34/configure --target=$cc_target --prefix="$cc_prefix" --with-sysroot --disable-nls --disable-werror
make -j$ncpu
make install -j$ncpu

cd $HOME/src

which -- $cc_target-as || echo "$cc_target-as is not in the PATH"

mkdir build-gcc
cd build-gcc
../gcc-9.4.0/configure --target=$cc_target --prefix="$cc_prefix" --disable-nls --enable-languages=c --without-headers
make all-gcc -j$ncpu
make all-target-libgcc -j$ncpu
make install-gcc -j$ncpu
make install-target-libgcc -j$ncpu

# Set up environment variables for Bash shell
echo "export PATH=$HOME/opt/cross/bin:\$PATH" >> ~/.bashrc
echo "export cc_prefix=$HOME/opt/cross" >> ~/.bashrc
echo "export cc_target=i686-elf" >> ~/.bashrc

# Set up environment variables for Fish shell (if Fish is installed)
if command -v fish &>/dev/null; then
    fish -c "set -U fish_user_paths $HOME/opt/cross/bin $fish_user_paths"
    fish -c "set -Ux cc_prefix $HOME/opt/cross"
    fish -c "set -Ux cc_target i686-elf"
fi

# Check if nasm is installed
if command -v nasm &>/dev/null; then
    echo "nasm already installed"
else
    echo "nasm not installed. Installing..."

    cd $HOME/src
    wget https://www.nasm.us/pub/nasm/releasebuilds/2.16.01/nasm-2.16.01.tar.gz
    tar xf nasm-2.16.01.tar.gz
    cd nasm-2.16.01
    ./configure
    make install -j$ncpu
fi

# Check if grub-mkrescue exists
if command -v grub-mkrescue &>/dev/null; then
    echo "grub-mkrescue already installed"
else
    echo "grub-mkrescue not installed. Installing..."

    cd $HOME/src
    wget ftp://ftp.gnu.org/gnu/grub/grub-2.06.tar.gz
    tar xf grub-2.06.tar.gz
    cd grub-2.06
    ./configure
    sudo make install -j$ncpu
fi

# Check if xorriso is installed
if command -v xorriso &>/dev/null; then
    echo "xorriso already installed"
else
    echo "xorriso not installed. Installing..."

    cd $HOME/src
    wget https://www.gnu.org/software/xorriso/xorriso-1.5.6.tar.gz
    tar xf xorriso-1.5.6.tar.gz
    cd xorriso-1.5.6
    ./configure
    make install -j$ncpu
fi

echo "Cross-compiler installation complete. Please restart your shell or run 'source ~/.bashrc' (or equivalent for your shell) to update your PATH."
