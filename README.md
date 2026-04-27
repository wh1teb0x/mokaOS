# mokaOS

A hobby x86_64 operating system, written from scratch by following
*Zero kara no OS Jisaku Nyuumon* (the MikanOS book) by Kota Uchida (uchan).

This is a learning project: code is hand-written chapter by chapter rather
than copied from the upstream MikanOS repository, and the build system has
been gradually reshaped to be Makefile-centric instead of relying on a
sourced `buildenv.sh`.

## Status

Boots under QEMU + OVMF and currently renders a desktop background, a
taskbar, a mouse cursor, and a `printk`-driven console.

| Chapters | Topic | Status |
|---|---|---|
| day01 – day04d | UEFI loader, frame buffer, pixel writer, ELF loading | done |
| day05a – day05f | Font rendering, newlib + `sprintf`, scrolling console, `printk` | done |
| day06a | Rectangle drawing, desktop background, mouse cursor | done |
| day06b | PCI bus enumeration | next |
| day06c | USB mouse driver (xHCI) | planned |

## Building

Requires the cross-compilation toolchain bundled with mikanos-build
(newlib + libc++ + freetype for `x86_64-elf`) at
`~/osbook/devenv/x86_64-elf/`, and EDK II at `~/edk2/`.

```sh
./build.sh
```

This produces `kernel/kernel.elf` and
`~/edk2/Build/MokaLoaderX64/.../Loader.efi`.

The kernel `Makefile` accepts overrides:

```sh
make -C kernel BASEDIR=/opt/x86_64-elf EDK2DIR=/opt/edk2
```

## Running

Using the QEMU helper from mikanos-build:

```sh
~/osbook/devenv/run_qemu.sh \
  ~/edk2/Build/MokaLoaderX64/DEBUG_CLANG38/X64/Loader.efi \
  kernel/kernel.elf
```

## Layout

```
mokaOS/
├── kernel/             C++ kernel (KernelMain, graphics, font, console)
├── MokaLoaderPkg/      UEFI loader (EDK II / C)
├── tools/              build helpers (e.g. makefont.py)
├── build.sh            kernel + loader build entry point
├── Makefile            top-level convenience targets (format, build)
└── .clang-format       Google style, 80 cols
```

## Differences from MikanOS

| | MikanOS | mokaOS |
|---|---|---|
| Loader package | `MikanLoaderPkg` | `MokaLoaderPkg` |
| Build flags | exported from `buildenv.sh` before `make` | inlined in `kernel/Makefile` (`BASEDIR ?=`) |
| `make` standalone | needs `source buildenv.sh` first | works on its own |
| Top-level Makefile | none | `make format`, `make build` |
| `clang-format` config | none | Google base, `ColumnLimit: 80` |

## Acknowledgements

Based on *Zero kara no OS Jisaku Nyuumon* by Kota Uchida (uchan), and
follows the structure of the accompanying
[MikanOS](https://github.com/uchan-nos/mikanos) reference implementation.
Code in this repository is hand-written while following the book.
