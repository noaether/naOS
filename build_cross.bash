#! /bin/bash

export CC_PREFIX="$HOME/opt/cross"
export CC_TARGET=i686-elf
export PATH="$CC_PREFIX/bin:$PATH"

rm -rf $HOME/src
rm -rf $HOME/opt/cross

sudo apt install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev

mkdir -p $HOME/src
cd $HOME/src

wget https://ftp.gnu.org/gnu/binutils/binutils-2.34.tar.xz
tar -xf binutils-2.34.tar.xz

wget https://ftp.gnu.org/gnu/gcc/gcc-9.4.0/gcc-9.4.0.tar.gz
tar -xf gcc-9.4.0.tar.gz

mkdir build-binutils
cd build-binutils
../binutils-2.34/configure --target=$CC_TARGET --prefix="$CC_PREFIX" --with-sysroot --disable-nls --disable-werror
make -j6
make install -j6

cd $HOME/src

which -- $CC_TARGET-as || echo $CC_TARGET-as is not in the PATH

mkdir build-gcc
cd build-gcc
../gcc-9.4.0/configure --target=$CC_TARGET --prefix="$CC_PREFIX" --disable-nls --enable-languages=c --without-headers
make all-gcc -j6
make all-target-libgcc -j6
make install-gcc -j6
make install-target-libgcc -j6

echo "export PATH=$HOME/opt/cross/bin:\$PATH" >> ~/.bashrc
echo "export CC_PREFIX=$HOME/opt/cross" >> ~/.bashrc
echo "export CC_TARGET=i686-elf" >> ~/.bashrc

set -U fish_user_paths $HOME/opt/cross/bin $fish_user_paths
set -Ux CC_PREFIX $HOME/opt/cross
set -Ux CC_TARGET i686-elf

