#!/bin/bash
# SPDX-License-Identifier: GPL-2.0

### Customisable variables
export DEFCONFIG=msm8226_defconfig

export KBUILD_OUTPUT=out
export KBUILD_BUILD_USER="$USER"
export KBUILD_BUILD_HOST=$(cat /etc/hostname)
export DTB_IMAGE="qcom/qcom-msm8926-sony-xperia-yukon-eagle.dtb"
export KERNEL_IMAGE="zImage"
export RAMDISK_PATH="../initramfs"
export RAMDISK_IMAGE="initramfs.cpio.gz"

# mkbootimg var (from AIK)
export BOARD_PAGE_SIZE="2048"
export BOARD_KERNEL_BASE="0x00000000"
export BOARD_KERNEL_OFFSET="0x00088000" # 0x00008000 + 0x00080000
export BOARD_RAMDISK_OFFSET="0x02000000"
export BOARD_SECOND_OFFSET="0x00f00000"
export BOARD_TAGS_OFFSET="0x01e00000"
export BOARD_KERNEL_CMDLINE="console=tty0 pmos.debug-shell"

### End

# Set up environment
function envsetup() {
    export ARCH=arm
    export CROSS_COMPILE=arm-none-eabi-
    export CROSS_COMPILE_ARM32=arm-none-eabi-
    export CROSS_COMPILE_COMPAT=arm-none-eabi-
}

# Wrapper to utilise all available cores
function m() {
    make -j$(nproc) ARCH="$ARCH" CROSS_COMPILE="$CROSS_COMPILE" DTC_EXT="$(command -v dtc)" "$@"
}

# Regenerate defconfig
function rd() {
    m "$DEFCONFIG" savedefconfig || return
    cp "$KBUILD_OUTPUT"/defconfig arch/"$ARCH"/configs/"$DEFCONFIG"
}

# Generate boot.img
function bootimg_gen() {
    local kernel_image_base="$KBUILD_OUTPUT/arch/$ARCH/boot/$KERNEL_IMAGE"
    local dtb_path="$KBUILD_OUTPUT/arch/$ARCH/boot/dts/$DTB_IMAGE"
    local kernel_image_dtb="$KBUILD_OUTPUT/arch/$ARCH/boot/${KERNEL_IMAGE}-dtb"
    local output_bootimg="$KBUILD_OUTPUT/boot.img"

    # Generate $KERNEL_IMAGE
    cat "$kernel_image_base" "$dtb_path" > "$kernel_image_dtb"

    # Generate $RAMDISK_IMAGE
    (cd "$RAMDISK_PATH" && find . \( -name ".git" -o -name "$RAMDISK_IMAGE" \) -prune -o -print | cpio -o -H newc | gzip > "$RAMDISK_IMAGE")

    mkbootimg \
        --kernel "$kernel_image_dtb" \
        --cmdline "$BOARD_KERNEL_CMDLINE" \
        --ramdisk "$RAMDISK_PATH/$RAMDISK_IMAGE" \
        --base "$BOARD_KERNEL_BASE" \
        --kernel_offset "$BOARD_KERNEL_OFFSET" \
        --ramdisk_offset "$BOARD_RAMDISK_OFFSET" \
        --second_offset "$BOARD_SECOND_OFFSET" \
        --tags_offset "$BOARD_TAGS_OFFSET" \
        --pagesize "$BOARD_PAGE_SIZE" \
        -o "$output_bootimg"

    echo "Successfully created boot image: $output_bootimg"
}

# Build kernel
function mka() {
    rd || return
    m || return
    bootimg_gen || return
}

envsetup
