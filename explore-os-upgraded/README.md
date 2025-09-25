# Explore OS — Upgraded Skeleton

This upgrade adds:
- PS/2 mouse support with on-screen cursor.
- Simple window manager (movable windows, title bars, z-order).
- Embedded initramfs-like virtual filesystem (in-memory files).
- Three demo apps: Explore Browser (reads local pages), File Manager, and Shell.
- Event queue (keyboard + mouse) and app message dispatch.
- Better organization & build targets.

**Still not included:** real networking driver, full filesystem on disk, multithreading, or a real browser engine.

## Build / Run
Requirements: `nasm`, `grub-pc-bin`, `xorriso`, `qemu-system-x86_64`, cross-toolchain `x86_64-elf-*` or use host compiler flags as in the Makefile.

```bash
make
make run
```

If you run into GRUB/tools issues, use `make qemu-kernel` to boot kernel.elf directly in QEMU.

## How to use the demo
- Click and drag the window title bars with the mouse to move windows.
- Type in the Shell window to see input echo; press Enter to create new line.
- Open the File Manager to see embedded files.
- Open Browser to view local "pages" from the embedded virtual filesystem.

## Files of interest
- `kernel/` : core kernel, drivers, wm, apps.
- `grub/grub.cfg` : GRUB config to set framebuffer mode.
- `Makefile` : build & run targets.

