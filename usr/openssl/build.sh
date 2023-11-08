#! /bin/bash

ARCH=$1

if [ $ARCH == "" ]
then
	@echo ./build.sh [arch];
exit;
fi

VER=1.1.1t
OPENSSL_DIR=/opt/xlocal/crl/c/usr/openssl-$VER
PREFIX=/opt/xlocal/crl/c/usr/openssl/v$VER
TOOLCHAIN=/opt/ext/toolchain/x64/v7

if [ $ARCH == "a32" ]
then
$OPENSSL_DIR/Configure \
--openssldir=$OPENSSL_DIR \
--prefix=$PREFIX/$ARCH \
--cross-compile-prefix=$TOOLCHAIN/arm-linux-gnueabi/bin/arm-linux-gnueabi- \
--release \
-fPIC \
-static \
no-tests \
no-rdrand \
no-ts \
no-ui-console \
no-aria \
no-seed \
no-idea \
no-md2 \
no-mdc2 \
no-rc5 \
no-rc4 \
no-asm \
no-shared \
no-zlib-dynamic \
no-engine \
no-hw \
linux-armv4;
make;
make test;
make depend;
make install_sw;
fi

if [ $ARCH == "ha32" ]
then
$OPENSSL_DIR/Configure \
--openssldir=$OPENSSL_DIR \
--prefix=$PREFIX/$ARCH \
--cross-compile-prefix=$TOOLCHAIN/arm-linux-gnueabihf/bin/arm-linux-gnueabihf- \
--release \
-fPIC \
-static \
no-tests \
no-rdrand \
no-ts \
no-ui-console \
no-aria \
no-seed \
no-idea \
no-md2 \
no-mdc2 \
no-rc5 \
no-rc4 \
no-asm \
no-shared \
no-zlib-dynamic \
no-engine \
no-hw \
linux-armv4;
make;
make test;
make depend;
make install_sw;
fi

if [ $ARCH == "ha64"  -o $ARCH == "a64" ]
then
$OPENSSL_DIR/Configure \
--openssldir=$OPENSSL_DIR \
--prefix=$PREFIX/$ARCH \
--cross-compile-prefix=$TOOLCHAIN/aarch64-linux-gnu/bin/aarch64-linux-gnu- \
--release \
-fPIC \
-static \
no-tests \
no-rdrand \
no-ts \
no-ui-console \
no-aria \
no-seed \
no-idea \
no-md2 \
no-mdc2 \
no-rc5 \
no-rc4 \
no-asm \
no-shared \
no-zlib-dynamic \
no-engine \
no-hw \
linux-armv4;
make;
make test;
make depend;
make install_sw;
fi


if [ $ARCH == "x32" ]
then
$OPENSSL_DIR/config \
--openssldir=$OPENSSL_DIR \
--prefix=$PREFIX/$ARCH \
--release \
-m32 \
-fPIC \
-static \
no-tests \
no-rdrand \
no-ts \
no-ui-console \
no-aria \
no-seed \
no-idea \
no-md2 \
no-mdc2 \
no-rc5 \
no-rc4 \
no-asm \
no-shared \
no-zlib-dynamic;
make;
make test;
make depend;
make install_sw;
fi

if [ $ARCH == "x64" ]
then
$OPENSSL_DIR/config \
--openssldir=$OPENSSL_DIR \
--prefix=$PREFIX/$ARCH \
--release \
-m64 \
-fPIC \
-static \
no-tests \
no-rdrand \
no-ts \
no-ui-console \
no-aria \
no-seed \
no-idea \
no-md2 \
no-mdc2 \
no-rc5 \
no-rc4 \
no-asm \
no-shared \
no-zlib-dynamic;
make;
make test;
make depend;
make install_sw;
fi
