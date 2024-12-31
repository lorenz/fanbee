FROM ubuntu:20.04

RUN apt-get -yy update && apt-get -yy install unzip wget libtinfo5 ninja-build python3 python3-intelhex python3-ecdsa

ENV SDK_VERSION=7.10.00.98 TOOLCHAIN_VERSION=3.0.0.STS

RUN wget -nv -O /tmp/sdk.zip https://dr-download.ti.com/software-development/software-development-kit-sdk/MD-BPlR3djvTV/${SDK_VERSION}/simplelink_cc13xx_cc26xx_sdk_$(echo "$SDK_VERSION" | tr '.' '_')__linux.zip && \
    mkdir -p /src/sdk && \
    ROOT=simplelink_cc13xx_cc26xx_sdk_$(echo "$SDK_VERSION" | tr '.' '_') && \
    unzip /tmp/sdk.zip -d /tmp -x $ROOT/examples/* $ROOT/source/ti/ti_wisunfan/* $ROOT/source/ti/ble5stack/* $ROOT/source/ti/ble5stack_flash/* $ROOT/docs/* $ROOT/tools/ble5stack/* $ROOT/tools/sidewalk/* $ROOT/.metadata/.tirex/* "*/iar/*" && \
    mv /tmp/$ROOT/.metadata /tmp/$ROOT/* /src/sdk/ && \
    rmdir /tmp/$ROOT && \
    rm -f /tmp/sdk.zip

RUN wget -nv -O /tmp/toolchain-installer https://dr-download.ti.com/software-development/ide-configuration-compiler-or-debugger/MD-ayxs93eZNN/${TOOLCHAIN_VERSION}/ti_cgt_armllvm_${TOOLCHAIN_VERSION}_linux-x64_installer.bin && \
    chmod +x /tmp/toolchain-installer && \
    /tmp/toolchain-installer --mode unattended --prefix /tmp && \
    rm /tmp/toolchain-installer && \
    mv /tmp/ti-cgt-armllvm_${TOOLCHAIN_VERSION} /src/toolchain && \
    rm -Rf /src/toolchain/*_uninstaller.* /src/toolchain/armv7r*

# Apply binary patch for link cost calculation
RUN apt-get -yy install bbe && \
    cd /tmp && \
    /src/toolchain/bin/tiarmar x /src/sdk/source/ti/zstack/lib/ticlang/m4f/libZStack_nwk_zr.a nwk_util.o && \
    mv nwk_util.o nwk_util_orig.o && \
    bbe -o nwk_util.o -e "s/\x0c\x28\x84\xbf/\x40\x28\x84\xbf/" -e "s/\x06\x28\x84\xbf/\x20\x28\x84\xbf/" -e "s/\x02\x28\x84\xbf/\x10\x28\x84\xbf/" nwk_util_orig.o && \
    /src/toolchain/bin/tiarmar r /src/sdk/source/ti/zstack/lib/ticlang/m4f/libZStack_nwk_zr.a nwk_util.o
