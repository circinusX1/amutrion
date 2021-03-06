#!/bin/bash

#
# this file might need tweaks
# called form src/make-file
#
CWD=$(pwd)
export PATH=${CWD}/TOOLS/toolchain/bin:$PATH
export BOARD_SETUP=raspberrypi
export OSYSTEM=linux
export ARM_EMBEDDED_SYSROOT=${CWD}/TOOLS/raspberrypi
export PATH=${CWD}/TOOLS/toolchain/bin:$PATH
export ARM_EMBEDDED_INCLUDE=$ARM_EMBEDDED_SYSROOT/usr/include
export ARM_EMBEDDED_INCLUDE_EABI=$ARM_EMBEDDED_SYSROOT/usr/include/arm-linux-gnueabihf
export ARM_EMBEDDED_LIB_EABI=$ARM_EMBEDDED_SYSROOT/usr/lib/arm-linux-gnueabihf/
export GCC_PREFIX=arm-linux-gnueabihf-
export GPP_PREFIX=arm-linux-gnueabihf-
export TCC=arm-linux-gnueabihf-
export CROSS_COMPILE=${GCC_PREFIX}
export ARCH=arm

