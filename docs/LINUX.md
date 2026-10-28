# Linux (i686)

PLAN.md D1/D2: the port builds 32-bit first, with Clang, on Windows and Linux. This page
covers the Linux build: the toolchain file, what differs from Windows, how it was
verified, and what is still open. P7 (x64, macOS) is out of scope here.

## Status (2026-10-24: rg-game LINKS; RG_NATIVE_ONLY=ON, RG_VU0_MODE=native, -O2 defaults)

Cross build `build/linux-i686` (Debian 12 i386 sysroot, `ninja -j4 -k 0 rg-game`, logs
`out/linux3/build1..4.log`): **`rg-game` links** (ELF32 i386, `EXEC` = non-PIE, image at
0x00400000, 12.4 MB, map `rg-game.map`). All ~23.4k objects compile, including the 8 game
C++ files (the `fnvoid` stage casts are in game/). Nothing has run (no WSL / Linux box here).

Undefined-symbol audit (`tools/native/elf_audit.py`, below): 256 undefined dynamic symbols,
**every one defined by a NEEDED library** (0 with no provider): libc.so.6 207 (stdio, file
system, `mmap`/`mprotect`, `getcontext`/`makecontext`/`swapcontext`, pthreads, semaphores,
`dlopen` and `posix_spawn`/`inotify`/`iconv` for SDL, the time64 entry points
`__clock_gettime64`/`__stat64_time64`/...), libm.so.6 42 (`sinf`, `sqrtf`, `powf`, ...),
libgcc_s.so.1 4 (`__divdi3 __moddi3 __udivdi3 __umoddi3`), libstdc++.so.6 0 (NEEDED, nothing
used), 3 weak (`__gmon_start__`, `_ITM_*`, may stay unresolved). Highest symbol version
**GLIBC_2.34** (the time64 symbols): runs on Debian 12 / Ubuntu 22.04 or newer. No TEXTREL;
interpreter `/lib/ld-linux.so.2`. SDL3 is linked statically (console build: dummy/offscreen
video, disk/dummy audio, see "Cross-building").

Link audit (`tools/native/link_audit.py`, reads the ELF map now): `check`: **PASS** (no `iop`
library); linked emulation = `rg_ps2_gs` (GS model, the software rasterizer of the headless
renderer), `rg_sce_vu0`, the overlay loader/arena: the same library set as a Windows
native-only rg-game minus `rg_gpu` and the Win32 system libraries.

Fixed in this pass (2026-10-24):

| Was | Fix |
| --- | --- |
| `src/sce/padmc/libmc.c` (`$RG_MC_TRACE`): `timespec_get` / `TIME_UTC` (C11, hidden by glibc at `-std=gnu99`) | `mc_wall_ts()`: `timespec_get` on Windows, `clock_gettime(CLOCK_REALTIME)` elsewhere (as runtime.c `rt_wall_ts`) |
| `src/native/render/nr_scene.c` `nr_frame_begin` calls `gpu_nr_filtlog_frame` (src/gpu, new 10-24) unguarded | that call under `#ifdef RG_HAVE_GPU` (one line; renderer lane's file) |
| `src/ps2/gs/gs_async.c`: still `__atomic_load` / `__atomic_store` libcalls although the fields are `_Alignas(8)`: clang picks inline vs libatomic from the **pointer's** type (`volatile uint64_t *` = 4-aligned on i386 SysV) | `ld64` / `st64` take `gsa_u64 *`, a `volatile uint64_t` typedef with `aligned(8)`: inline SSE2 `movq` loads / stores (checked: no `__atomic` call in `gs_async.c.o`), no libatomic (Windows: same code, the MSVC ABI already aligns 8) |
| `cmake/game_link.cmake`: `--no-icf` (not an ELF lld option: `unknown argument`) | `--icf=none` |
| a native-only rg-game without a GPU backend stalls on the title (the frame chain walker was installed only by `gpu_start` with the D3D11 renderer) | the **headless renderer** (next section) |

The 10-18 failures (`nr_scene.c` store hook, `runtime.c` `timespec_get`, `movie_game.h`
`size_t`, `kernel_tests.c` `_putenv`, the 8 C++ fn -> `void *` objects) were all fixed by
10-19 (rows in "Fixes 2026-10-18" below); this build confirms it.

Left for running it (none blocks the link):
- **WSL / a Linux box** with `libc6:i386 libstdc++6:i386 libgcc-s1:i386` (glibc >= 2.34).
- **Save states are Windows-only** (`src/savestate`: PE image walk `ss_map.c`, UCRT heap
  hooks `ss_heap.c`/`ss_hooks.c`; on Linux `--save-state`/`--load-state` are not supported),
  so `tools/fixtures` milestones cannot be used; Linux runs start at power-on. The fixtures
  tooling also assumes `rg-game.exe`.
- No crash handler: `src/game/rg_game_main.c` installs its exception filter on Windows only
  (a `sigaction(SIGSEGV)` handler printing EIP / fault address is the Linux equivalent).
- A windowed run needs SDL3 configured with the X11/Wayland/ALSA/Pulse i386 headers (a
  native build, "Building natively"); the cross build is a console build.

## Headless renderer (no GPU backend: Linux today)

`src/gpu` exists only where a backend is implemented (D3D11, Windows); without the `rg_gpu`
target nothing defines `RG_HAVE_GPU` and configure prints `rg-game: no GPU backend for
Linux: headless renderer` (`cmake/game_link.cmake`). That is the build-time guard: every GPU
call site in src/runtime and src/native/render is already under `#ifdef RG_HAVE_GPU`, so no
stub library is needed.

What runs (`src/runtime/runtime.c gpu_start`, `!RG_HAVE_GPU && RG_NATIVE_ONLY`): a
native-only exe has no DMAC / VIF1 / VU1 models, so the frame chain is still walked natively
(`rg_vif1_chain_hook = vif1_chain`, `nr_fx.c`), but the walker feeds the **software GS model**
(`gs_vif1_gif_sink`), VU1 programs run in `nr_vux.c` and XGKICK to the GS (PATH1), the GIF
channel goes straight to the GS (PATH3, `libdma_native.c`). `nr_scene` is not attached (no
device), so `nr_model_record` returns 0 and the game keeps its original MSCAL + CALL (the
models are drawn by the translated VU1 programs, not by native draw records). Frames are
complete but software-rasterized (slow); `RG_GS_NULL=1` skips rasterizing for logic-only /
timing runs. Startup prints `rg_runtime: no GPU backend in this build: headless renderer
(frame chain walker -> software GS)`. (On Windows a GPU build with `RG_GPU=sw` still does
not install the walker and stalls: unchanged, renderer lane.)

## Audit (no Linux machine needed)

```
python tools/native/elf_audit.py build/linux-i686/rg-game [--list]      # load-time needs
python tools/native/link_audit.py check  build/linux-i686/rg-game.map  # D9 gate on the ELF map
python tools/native/link_audit.py report build/linux-i686/rg-game.map --all
```

`elf_audit.py` (llvm-readelf over the ELF and the NEEDED libraries in the sysroot): header
(class, machine, `EXEC` vs PIE, TEXTREL), interpreter, LOAD segments, every undefined
dynamic symbol by the library that provides it, the highest GLIBC version; exit 1 if a
symbol has no provider. `link_audit.py` reads both map formats (lld-link `/MAP` and
ld.lld `-Map`; on ELF the sizes are the input sections' own, libraries `libX.a` -> `X`,
objects `x.c.o`); `refs` also scans `.a` / `.o`.

## A Linux renderer backend (not built; what it needs)

**2026-10-25: the Vulkan backend exists** (`src/native/render/nr_vulkan.cpp`, docs/NATIVE-VULKAN.md):
built and gated on Windows behind `display.backend` / `RG_GPU_API=vulkan`; what is left for Linux
(CMake wiring without `rg_gpu`, presentation, packaging) is in NATIVE-VULKAN.md "Linux: what
remains". The text below is the pre-implementation analysis.

`src/gpu` is a backend-agnostic core (`gpu_core.cpp`: GS state tracking, render-target
cache, coherence with `gs->vram`, batching, native-draw resolution) over one abstract
class, `GpuBackend` (`src/gpu/gpu_internal.h`), implemented once by `src/native/render/nr_d3d11.cpp`
(`gpu_backend_d3d11_create`; since 2026-10-24 the native-only device `nr_dev.cpp` drives the same
class without the GS model: docs/NATIVE-RENDER.md "Checkpoint 10"). A Vulkan (preferred: compute, fragment-shader interlock,
explicit sync) or GL 4.5 backend implements the same class:

- **Mirror**: a 4 MB storage buffer (`mirror_upload`, `mirror_download` by byte runs,
  optional `mirror_merge` of (data, mask) words in a compute pass).
- **Render targets**: colour RGBA8 and depth at `scale` x native size
  (`rt_create/resize/destroy/clear`); `rt_load` / `rt_writeback` between a target and
  the mirror with the GS swizzles (compute, today `gs_util.hlsl`); `rt_read`.
- **Drawing** (`draw`, `GpuDraw`, `gs_draw.hlsl`): texture sampling from the mirror or
  a decoded RGBA copy (CLUT/TEXA via `set_clut`), alpha test, fog, shader blending with
  a destination snapshot or ordered access (D3D11.3 ROVs = Vulkan
  `VK_EXT_fragment_shader_interlock` / GL `ARB_fragment_shader_interlock`; `rov()`
  false makes the core split batches instead), depth in the shader (`zrov()`) or a
  D32 buffer, exact triangles with double-precision ops (`exact()`, else the core's
  fallback).
- **Native draws** (`nr_draw`, `GpuNrDraw`, `nr_draw.hlsl`): skinned meshes and
  immediate triangles from src/native/render with fixed-function state.
- **Display** (`display`, `display_post`, `gs_post.hlsl`): PCRTC merge of two circuits,
  anti-flicker, SSAA / FXAA / sharpen / gamma, RGBA8 read-back; optional zero-copy
  `shared_out` (Linux: a VkImage / dmabuf shared with the SDL presenter).
- **Snapshots** (`snap_copy/map/unmap`): small async read-backs (optional).
- Shaders: the five HLSL files to SPIR-V (DXC `-spirv`, or a GLSL port); the build
  needs that compiler instead of fxc.
- Wiring: `src/gpu/CMakeLists.txt` `return()`s on non-WIN32 today; a backend choice
  (`RG_GPU_BACKEND=d3d11|vulkan`) and one `gpu_backend_vulkan_create` call in
  `gpu_create` are the only core-side changes. src/native/render then gets
  `RG_HAVE_GPU` on Linux too (it is the RG_NATIVE_ONLY renderer; without a device its
  native draws do nothing and the run falls back to the software GS path: the "Headless
  renderer" section).

### Vulkan or SDL_GPU (decision input, 2026-10-24)

| | Vulkan (`gpu_vulkan.cpp`) | SDL_GPU (SDL3 `SDL_GPUDevice`, already linked) |
| --- | --- | --- |
| ordered blending (ROV) | `VK_EXT_fragment_shader_interlock` (Mesa RADV / ANV, NVIDIA; not all drivers) | not exposed: `rov()` = false, the core splits batches (slower, same pixels) |
| depth in shader (`zrov()`) | with interlock | no: D32 depth buffer path |
| `exact()` double ops | `shaderFloat64` (most desktop GPUs) | not exposed: the core's fallback |
| compute (mirror merge, swizzle load/writeback) | yes | yes (compute pipelines) |
| storage buffer 4 MB mirror, byte-run updates | yes | yes (storage buffers + transfer buffers) |
| shaders | SPIR-V from the 5 HLSL files (DXC `-spirv`) | SPIR-V (Vulkan backend), DXIL / MSL via `SDL_shadercross` for its other backends |
| presentation | own swapchain, or a VkImage shared with the SDL presenter | the SDL window's swapchain directly (`SDL_AcquireGPUSwapchainTexture`) |
| reach | Linux (+ Windows) | Linux, Windows (D3D12), macOS (Metal): the P7 platforms with one backend |

Recommendation: Vulkan first if exact GS blending matters most (interlock = the D3D11.3 ROV
path the core is tuned for); SDL_GPU if one portable backend matters more, accepting the
non-ROV fallbacks the core already has (`rov()` / `zrov()` / `exact()` false).

### Everything a backend needs (checklist)

1. A `GpuBackend` subclass (`src/gpu/gpu_internal.h`, ~25 virtuals): required `name`,
   `exact`, `rov`, `mirror_upload` / `mirror_download`, `rt_create` / `rt_resize` /
   `rt_destroy` / `rt_load` / `rt_writeback` / `rt_read`, `set_clut`, `draw`, `kick`,
   `display`, `display_post`, `set_scale`; optional (defaults fall back) `zrov`,
   `can_merge` + `mirror_merge`, `rt_clear`, `rt_copy`, `set_clut_part`, `clut_load_gpu` /
   `clut_read`, `snap_copy/map/unmap`, `shared_out`, `nr_draw`, `nr_tex_cached`,
   `nr_mesh_prewarm`.
2. Shaders: `src/gpu/shaders/{gs_draw,gs_util,gs_post,nr_draw}.hlsl` (+ `gs_common.hlsli`)
   compiled to SPIR-V at build time (a `find_program(dxc)` or glslang step replacing the fxc rule; the
   HLSL `RasterizerOrderedTexture2D` uses become interlock begin/end).
3. Build wiring: `src/gpu/CMakeLists.txt` stops `return()`ing on non-WIN32 when
   `RG_GPU_BACKEND=vulkan|sdlgpu` (new cache option; `d3d11` stays the Windows default),
   links `Vulkan::Vulkan` (or nothing extra for SDL_GPU); `gpu_create` picks
   `gpu_backend_vulkan_create`. `rg_gpu` existing then defines `RG_HAVE_GPU` for
   rg_runtime / rg_native_render automatically, and the headless renderer above switches
   off by itself (it is `#if !RG_HAVE_GPU`).
4. Presenter: `src/host` presents an RGBA8 frame through SDL today; zero-copy needs the
   backend's output image shared with the SDL window (SDL_GPU: same device, trivial;
   Vulkan: `SDL_Vulkan_CreateSurface` on the window, the backend owns the swapchain).
5. Run-time: `RG_GPU=hw|warp` mapping (`warp` = a software Vulkan, lavapipe), the
   `gpu_start` WARP retry, `gfx_update` scale / SSAA / FXAA options.
6. Tests: `tests/gpu` (`-L gpu`) are D3D11-hosted; they need the backend factory (or
   lavapipe on CI) and their goldens compared against the D3D11 ones (same pixels expected
   where `rov()`/`exact()` hold).
7. Linux packaging: `libvulkan1:i386` + an i386 ICD (Mesa) at run time; a 32-bit Vulkan
   driver is the least-tested combination (consider the x64 build, P7, for the GPU path).

## Status (2026-10-18, superseded: every row fixed by 10-24)

Fresh cross build (`build/linux-i686`, Debian 12 i386 sysroot, `ninja -j4 all rg-game`,
log `out/ovu0/linux-build2.log`). The tree moved a lot since 10-12 (native-only
libraries, native renderer, save states). What breaks now:

| Failure | File (owner) | Cause | Fix |
| --- | --- | --- | --- |
| 8 game C++ objects | game/ (ingest), `overrides/src/main/file/CdDatArchiveOpen_183110.cpp` | function name passed / assigned where the type is `void *` (unchanged since 10-12, see "The game") | **stage proposal** at the end of this page |
| `nr_scene.c` (both clones) | src/native/render (renderer lane) | the store-hook code at line ~1709 uses `gpu_renderer` / `gpu_attached_state` outside `#ifdef RG_HAVE_GPU`: every build without src/gpu fails (Linux, and a Windows configure where fxc is not found) | guard it with `RG_HAVE_GPU` like the file's other GPU paths |
| `runtime.c` (both clones) | src/runtime | `timespec_get` / `TIME_UTC` are C11; the target builds with `-std=gnu99`, so glibc hides them | `clock_gettime(CLOCK_REALTIME)` on non-Windows, or `-std=gnu11` for that target |
| `mv_runtime.c` (both clones) | src/movie/movie_game.h | uses `size_t` with only `<stdint.h>` included (the MSVC headers happen to define it) | `#include <stddef.h>` |
| link of `rg-gs-tests`, `rg-dmac-tests`, `rg-hwbus-tests`, `rg-bindings-tests(-wrong)`, `rg-host-demo` | src/ps2/gs/gs_async.c (renderer lane) | `__atomic_load_n` / `__atomic_store_n` on a plain `uint64_t`: the i386 SysV ABI aligns it to 4, so clang emits generic libatomic calls (`__atomic_load` / `__atomic_store`, undefined); the MSVC ABI aligns it to 8 | declare those fields `_Alignas(8)`: the accesses become inline; `-latomic` also links but is a lock-based fallback |
| `kernel_tests.c` | tests/kernel | `_putenv` (MSVC CRT) | `setenv` under `#ifndef _WIN32` |

Everything else compiles: all platform modules, the SDL3 host, the native-only
services and the other ~25k game objects. The native services
(`src/native/{audio,fs,input,iop,saves,threads}`) are Linux-clean: Win32 appears only
behind `_WIN32` with a POSIX branch (`rg_fs.c` directory scan, `mccard.c` file
operations, `fiber_arena.c` low-address reservation, `fiber_win32.c` vs
`fiber_ucontext.c`); the host layer (src/host) is SDL. **rg-game does not link on Linux
today** (rows above); on 10-12 it linked with 0 undefined symbols once the 8 C++
objects were built by hand.

Changes made in this pass:
- `cmake/game_link.cmake`: Linux link options for rg-game (map file, explicit
  `--no-gc-sections` / `--no-icf` = `/OPT:NOREF /OPT:NOICF`, `--error-limit=0`,
  `--unresolved-symbols=ignore-all` for `RG_GAME_FORCE_UNRESOLVED`); `/DYNAMICBASE:NO`
  is the toolchain's `-no-pie`.
- `cmake/toolchain-linux-i686.cmake`: `-march=pentium4`, the CPU baseline of the
  Windows i686 target, so both platforms compile for the same CPU (needs a fresh
  configure: it is a `*_FLAGS_INIT`).

**Running it**: not possible on this machine; WSL is not installed (left to the user,
nothing was installed). A headless Linux rg-game run needs: the link fixes above; WSL or
a Linux box with the i386 runtime (`libc6:i386 libstdc++6:i386`); the software GS path
(there is no Linux GPU backend, next section); and its own fixture set (states are per
exe; `tools/fixtures` assumes `rg-game.exe`, so the exe name would have to become
platform-neutral there).

## Status (2026-10-12)

| What | State |
| --- | --- |
| Configure + build of every default target (platform modules, SDL3 host, runtime, movie, trace, every test exe) | **builds and links** (cross build from Windows against a Debian 12 i386 sysroot; ELF32, non-PIE) |
| `ctest` on Linux | **not run**: no Linux machine or WSL distro was available (see "Running the tests") |
| `rg-game` (the game) | all ~25k game objects compile except 8 C++ files (below); with those 8 compiled by hand with `-fms-compatibility`, `rg-game` **links with 0 undefined symbols** (ELF32 non-PIE, image at 0x00400000 like the Windows exe; needs libc, libm, libstdc++, libgcc_s) |
| GPU backend (`src/gpu`, D3D11) | Windows-only; skipped on Linux, the software GS rasterizer is used |

## Building natively (Linux or WSL)

Needs CMake >= 3.25 (Debian 12, Ubuntu 24.04 or newer), clang, lld (optional), Ninja,
Python 3 (tests and the game source list), and a 32-bit multilib. Debian/Ubuntu:

```sh
sudo dpkg --add-architecture i386 && sudo apt update
sudo apt install clang lld cmake ninja-build python3 gcc-multilib g++-multilib
# SDL3 window/audio backends (headers only at build time; SDL loads the libs at run time):
sudo apt install libx11-dev:i386 libxext-dev:i386 libxrandr-dev:i386 libxcursor-dev:i386 \
  libxi-dev:i386 libxss-dev:i386 libxfixes-dev:i386 libxkbcommon-dev:i386 \
  libwayland-dev:i386 libwayland-bin wayland-protocols libdecor-0-dev:i386 \
  libasound2-dev:i386 libpulse-dev:i386 libudev-dev:i386 libdbus-1-dev:i386 \
  libegl-dev:i386 libgl-dev:i386 libgles-dev:i386
```

Then, from the source tree (`/mnt../port` under WSL is fine):

```sh
tools/build-linux.sh            # configure + build + rg-smoke + ctest
tools/build-linux.sh --clean    # from scratch
RG_BUILD_DIR=build/linux-i686-native tools/build-linux.sh --no-test
```

The default build dir is `~/rgport-build/linux-i686`: on the Linux file system (much
faster than `/mnt/<drive>` under WSL) and away from the Windows build dirs. By hand:

```sh
cmake -S . -B ~/rgport-build/linux-i686 -G Ninja \
      -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-i686.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build ~/rgport-build/linux-i686
ctest --test-dir ~/rgport-build/linux-i686 -j"$(nproc)" --output-on-failure
```

Without the X11/Wayland/ALSA/Pulse headers SDL3's configure stops; pass
`-DSDL_UNIX_CONSOLE_BUILD=ON` to build anyway (video: dummy/offscreen, audio: disk/dummy).
That is enough for every test (they run headless) but not for a window.

## Cross-building from Windows (compile + link check)

The Windows LLVM release (`../tools\llvm`) targets Linux too. Against a Debian i386
sysroot it compiles and links the whole tree, which is how this page's "builds and links"
was verified. The binaries cannot run on Windows.

The sysroot (`../tools\sysroot-i386-bookworm`, ~100 MB, outside the tree) is the
`data.tar` of these Debian 12 i386 packages, unpacked with symlinks replaced by copies:
`libc6 libc6-dev linux-libc-dev libgcc-12-dev libgcc-s1 libstdc++-12-dev libstdc++6
libcrypt-dev libcrypt1` (from `deb.debian.org`, `dists/bookworm/main/binary-i386`;
the archives are kept in `../tools\dl\debian-i386`). These are toolchain inputs only,
nothing from them enters the port's source.

```powershell
$cmake = "../tools\cmake-3.31.7-windows-x86_64\bin\cmake.exe"
& $cmake -S . -B build\linux-i686 -G Ninja -DCMAKE_MAKE_PROGRAM=../tools/ninja/ninja.exe `
  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-i686.cmake `
  -DRG_LINUX_SYSROOT=../tools/sysroot-i386-bookworm `
  -DCMAKE_BUILD_TYPE=Release -DSDL_UNIX_CONSOLE_BUILD=ON
../tools\ninja\ninja.exe -C build\linux-i686
```

No vcvars shell is needed. Configure takes a few minutes (SDL's feature checks).

## The toolchain file (`cmake/toolchain-linux-i686.cmake`)

- `clang`/`clang++` (first `RG_CLANG_ROOT`, then on Windows `../tools\llvm\bin`,
  then `PATH`), target `i686-linux-gnu`, `-m32`, `llvm-ar`/`llvm-ranlib` when next to clang,
  `-fuse-ld=lld` when `ld.lld` is found (else the system linker).
- **`-fno-pic` and `-no-pie`.** Same code model as the Windows exe. i386 PIC spends
  `%ebx` on the GOT in every function, and the overlay import trampolines
  (`src/ps2/overlay/ovl_asm.h`) push absolute table addresses: an `R_386_32` in `.text`,
  which a PIE link rejects.
- `RG_LINUX_SYSROOT`: cross mode (`CMAKE_SYSROOT`, find-root-path, pkg-config pointed
  into the sysroot). Without it, pkg-config is pointed at the i386 multiarch `.pc` files
  so SDL3 finds the 32-bit X11/Wayland/ALSA/Pulse packages.
- `cmake/toolchain-i686-linux-clang.cmake` (the older, never-run file) now just includes
  this one.

Flags (`rg_flags`, PLAN D2) are the same on both platforms. On Linux `rg_flags` also
links `libm`.

## What differs from Windows

| Area | Windows | Linux |
| --- | --- | --- |
| Guest threads (`src/ps2/kernel`) | `fiber_win32.c` (Fibers, `FIBER_FLAG_FLOAT_SWITCH`) | `fiber_ucontext.c`: `getcontext`/`makecontext`/`swapcontext`; stacks mmapped below 2 GB, with a `PROT_NONE` guard page |
| Game RAM block (`src/runtime/crt0.c`) | `malloc` (exe is not large-address-aware: < 2 GB) | `mmap` with address hints, checked to end below 2 GB |
| `sbrk` (game + `src/crt/crt_heap.c`) | `crt0.c` defines it | same definition; in an ELF executable it interposes libc's `sbrk` for every caller outside libc (glibc's malloc uses its internal `__sbrk`) |
| FILEIO paths (`src/ps2/iop/iop_hle.c`) | case-insensitive file system | exact path first, then a per-component case-insensitive directory scan |
| GPU (`src/gpu`, `tests/gpu`) | D3D11 renderer, `-L gpu` tests | skipped at configure (`src/gpu: Direct3D 11 backend is Windows-only; skipped`); no `gpu` tests are registered; `rg-host-demo` has no `--gpu`; rg-game uses the headless renderer (frame-chain walker -> software GS, "Headless renderer") |
| Save states (`src/savestate`) | PE image walk + UCRT heap hooks | not supported (`--save-state` / `--load-state`); runs start at power-on |
| Movie tool timing (`rg_movie_play.c`) | `QueryPerformanceCounter` | `clock_gettime(CLOCK_MONOTONIC)` |
| `rg-game` link options (`cmake/game_link.cmake`) | `/LARGEADDRESSAWARE:NO /STACK:8M /OPT:NOREF /OPT:NOICF /MAP /DYNAMICBASE:NO` | `-Map=rg-game.map --no-gc-sections --icf=none --error-limit=0` + the toolchain's `-no-pie`; stack = `ulimit -s`; < 2 GB via the pinned allocators |
| Trace host-pointer probe (`trace_regions.c host_readable`) | `VirtualQuery` | returns 0 (untranslatable host pointers get a marker) |

**Why everything guest-visible stays below 2 GB:** DMA addresses (MADR, TADR, tag ADDR)
are 32-bit and bit 31 selects the scratchpad (DMAC.md "Address mapping"). An i686 process
under an x86-64 Linux kernel has a 4 GB address space and maps top-down from just under
4 GB, so a plain `malloc` of 32 MB lands above 2 GB. The two allocators the game's data
lives in (game RAM block, guest thread stacks) are pinned low; the executable's own
`.data`/`.bss` (MAIN data, the overlay arena) load low anyway (non-PIE). Host-side
allocations the game never DMAs from (SDL, the GS model's VRAM, decoders) may be high.

## Running the tests

`ctest` runs on Linux exactly as on Windows (same labels, same skip codes; TOOLCHAIN.md).
Expected differences: no `gpu` label; host tests run headless (no SDL init), so they need
no display. Tests that need `RG_DATA` skip without it, as on Windows.

They have **not been run on Linux yet.** On this machine the WSL feature is not
installed (`wsl.exe` only prints its install usage), and installing it needs admin rights
and a reboot, so it was left to the user:

```powershell
wsl --install -d Debian        # elevated PowerShell; reboot; then create the user
```

then the apt lines above, then `tools/build-linux.sh` from `/mnt../port`.

## The game

`rg-game` and `rg_game_objs` are `EXCLUDE_FROM_ALL`, as on Windows, and use the same
flags (`cmake/game.cmake`). Cross build result (game/ as of 2026-10-12 ~12:00):

- **8 C++ files fail on Linux only**: they pass a function name where the prototype
  says `void *` (`ConstructNewArray_100710(..., SomeCtor, ...)`, `Qsort_132d08`, and
  `v.fn = &ScriptFn...` into a `void *` field). Standard C++ forbids that implicit
  conversion; on the MSVC target clang accepts it as a Microsoft extension, so Windows
  never sees it. `-fms-extensions` alone does not help; `-fms-compatibility` does. Files:
  `main/chara/CharaActInfoInit_215600.cpp`, `main/chara/CharaTableSubRecCloneMaybe_22e880.cpp`,
  `main/file/CdDatArchiveOpen_183110.cpp`, `main/map/WorldSubsysInit_41e580.cpp`,
  `main/map/WorldSubsysInit_411fb0.cpp`, `main/menu/MenuObjLoadFromCfg_387930.cpp`,
  `main/model/EffObjBuildEmitterRecMaybe_1a9890.cpp`,
  `main/script/ScriptEvalQueryOpMaybe_3daaf0.cpp`. Fix options: (a) an ingest stage /
  protos fix that casts (`(void *)Fn`) or declares those parameters as function pointers
  (portable, preferred), or (b) add `-fms-compatibility` to the game's C++ flags on
  non-Windows in `cmake/game.cmake` (one line, but a broad dialect switch).
- Everything else compiles, and with those 8 objects built by hand `rg-game` links.
  Nothing has run.

Open items for the game on Linux (not done here, `cmake/game*.cmake` belong to the
game-link work):

- `cmake/game_link.cmake` Linux link options: done 2026-10-18 (table above).
- `src/game/rg_game_main.c` installs an unhandled-exception filter on Windows only; a
  `sigaction(SIGSEGV)` handler printing EIP and the fault address would be the Linux
  equivalent.

### Fixes 2026-10-18 (late, transition-stutter lane)

The four non-renderer rows of the status table are fixed in the tree (not yet rebuilt on
Linux; no Linux machine here):

| Row | Fix |
| --- | --- |
| 8 game C++ objects | **new ingest stage `fnvoid`** (`tools/stages/fnvoid.py`, registered in `tools/ingest.py` after `dialect`): in `.cpp` files, a function designator (`Fn` / `&Fn`, Fn declared or defined in the file outside class bodies) passed to a parameter the nearest preceding declaration types exactly `void *`, or assigned to a name / member declared `void *`, gets `(void *)`. Ingest census: `fnvoid files_changed=8 sites=16` (the 11 `ConstructNewArray_100710` arguments, the 4 `v.fn = &ScriptFn..` assignments, the `Qsort_132d08` argument in the generated `CdDatArchiveOpen_183110.cpp`); a scratch ingest differed from `game/` in exactly those 8 files + MANIFEST/SNAPSHOT (applied). The override `overrides/src/main/file/CdDatArchiveOpen_183110.cpp` got the cast by hand and its `rg-override` hash (now `473bc0af..`). `ingest.py --check`: 0 problems, 219 overrides 0 problems. Windows objects: the cast is the MSVC target's implicit conversion (same code). Dry run / listing: `python tools/stages/fnvoid.py [files]` |
| `runtime.c` `timespec_get` | `rt_wall_ts()`: `timespec_get(TIME_UTC)` on Windows, `clock_gettime(CLOCK_REALTIME)` elsewhere (both uses) |
| `movie_game.h` `size_t` | `#include <stddef.h>` |
| `kernel_tests.c` `_putenv` | `setenv("RG_THREADS", mode, 1)` under `#ifndef _WIN32` (`_putenv` kept on Windows) |

(Fixed by 10-24, see the top status.) Still open for the Linux link then (renderer lane's files, not touched): `nr_scene.c` store-hook
code outside `RG_HAVE_GPU`, and `gs_async.c` `__atomic_*` on 4-aligned `uint64_t` (i386 SysV).
New since: `src/runtime/fstats_sys.c` ($RG_FIELD_STATS) has a POSIX branch
(`clock_gettime` process / thread CPU, `getrusage` faults; no per-thread list).

### Stage proposal: C++ function -> `void *` rule (2026-10-18) (DONE: see "Fixes 2026-10-18" above)

For tools/stages (protos or dialect; owner: ingest), C++ files only: where a function
designator (`Fn` or `&Fn`) is an argument whose parameter type is `void *`, or the
right side of an assignment to a `void *` lvalue, emit `(void *)Fn`. Sites today
(`out/ovu0/linux-build2.log`): `ConstructNewArray_100710` argument 2 in
CharaActInfoInit_215600, CharaTableSubRecCloneMaybe_22e880, WorldSubsysInit_411fb0 (5),
WorldSubsysInit_41e580 (2), MenuObjLoadFromCfg_387930, EffObjBuildEmitterRecMaybe_1a9890;
`v.fn = &ScriptFn...` (4) in ScriptEvalQueryOpMaybe_3daaf0; `Qsort_132d08` argument 4 in
the override CdDatArchiveOpen_183110.cpp (its owner adds the same cast by hand). The cast
is what clang does implicitly on the MSVC target, so the Windows objects do not change.
Alternative: declare those parameters as function pointers in game/PROTOS.tsv.
