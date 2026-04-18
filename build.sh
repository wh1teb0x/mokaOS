#!/bin/bash -e
MOKA_DIR=$(dirname "$0")

# Build kernel
make -C "$MOKA_DIR/kernel"

# Build loader
cd ~/edk2
export EDK_TOOLS_PATH=$HOME/edk2/BaseTools
source edksetup.sh BaseTools
build -p MokaLoaderPkg/MokaLoaderPkg.dsc -a X64 -t CLANG38
