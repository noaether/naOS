#! /bin/bash

export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

mkdir -p $HOME/src
cd $HOME/src

wget https://ftp.gnu.org/gnu/binutils/binutils-2.34.tar.xz
tar -xf binutils-2.34.tar.xz

wget https://ftp.gnu.org/gnu/gcc/gcc-9.4.0/gcc-9.4.0.tar.gz
tar -xf gcc-9.4.0.tar.gz

mkdir build-binutils
cd build-binutils
../binutils-2.34/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make -j6
make install -j6

cd $HOME/src

which -- $TARGET-as || echo $TARGET-as is not in the PATH

mkdir build-gcc
cd build-gcc
../gcc-9.4.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc -j6
make all-target-libgcc -j6
make install-gcc -j6
make install-target-libgcc -j6

echo "export PATH=$HOME/opt/cross/bin:$PATH" >> ~/.bashrc