# Vulkan backend of the native renderer

The native-only renderer (`src/native/render/nr_dev.cpp`, docs/NATIVE-RENDER.md "Checkpoint 10")
drives its GPU through one abstract class, `GpuBackend` (`src/gpu/gpu_internal.h`). Until
2026-10-25 the only implementation was Direct3D 11 (`nr_d3d11.cpp`), which ties the port to
Windows. `nr_vulkan.cpp` is the second implementation: the backend a Linux build uses. It is
built and tested on Windows (RTX 3080); Direct3D 11 stays the default there.

## Decision: Vulkan, not SDL_GPU

What `nr_dev.cpp` needs from a backend (the native-only subset of `GpuBackend`; the GS-exact
`draw()` path is not used):

| Need | Where | Vulkan | SDL_GPU (SDL 3.4) |
| --- | --- | --- | --- |
| Ordered (rasterizer-ordered) colour access for immediate primitives the blender cannot express | `PS_nr_c` / `PS_nr_cz`, `GpuNrDraw.crov` | `VK_EXT_fragment_shader_interlock` (DXC maps `RasterizerOrderedTexture2D`) | not exposed: those primitives fall back to the CPU path |
| Depth tested / written in the pixel shader (`zrov`) | `PS_nr_z`, depth targets as R32F | interlock again | not exposed |
| Read-write storage images in fragment shaders | the two above | `fragmentStoresAndAtomics` | graphics shaders get read-only storage only |
| Dual-source blending (GS `(A - B) * C >> 7 + D` as fixed function) | `nr_blend` | `dualSrcBlend` | no dual-source blend factors |
| Typed (texel) buffers, raw buffers with atomics, compute | CLUT (`Buffer<uint>`), mirror (`RWByteAddressBuffer` + `InterlockedAnd/Or`), the swizzle passes | yes | storage buffers yes, texel buffers no |
| An RGBA8 image viewed as R32_UINT | ordered colour views, decoded textures | `MUTABLE_FORMAT` views | no format reinterpretation |
| Small synchronous read-backs, early copies | `snap_copy`, `clut_read`, `mirror_download` | fences + host-visible buffers | download transfer buffers (yes) |

SDL_GPU would cost the ordered paths (more CPU fallbacks, different pixels than D3D11) and needs
shader rewrites for texel buffers and dual-source blending. Vulkan maps every D3D11 feature
the backend uses one to one, and the HLSL compiles to SPIR-V unchanged (one
`#ifdef __spirv__` annotation, below). The cost is more code (memory, synchronisation).
Decision: **Vulkan 1.3**.

## Enabling it

| Way | Effect |
| --- | --- |
| `--set display.backend=vulkan` / settings file / menu (Display, "Graphics API") | Vulkan from the next start (restart setting); `d3d11` (default, also the Original preset) |
| `RG_GPU_API=vulkan` (or `vk`) / `RG_GPU_API=d3d11` | overrides the setting |
| `RG_VK_DEVICE=N` | physical device index (default: the first discrete GPU) |
| `RG_VK_VALIDATE=1` | the Khronos validation layer when it is installed (32-bit layer for the i686 exe; "Validation" below) |
| `RG_VK_LAYER_DLL=path` | with `RG_VK_VALIDATE=1`: the backend loads that layer library itself (an elevated process ignores every loader layer path variable) |
| `RG_VK_VALIDATE_SYNC=1` | with validation: synchronization validation too |
| `RG_VK_RING_MB=N` | size of the host-visible upload ring (default 96) |
| `RG_VK_PRESENT=0` | no zero-copy presentation (no surface extensions, one queue): frames are read back as before 2026-10-25 (evening) |
| `RG_GPU_READBACK_LAG=1` | pipelined read-back of presented frames (as D3D11; read-back path only) |
| `RG_GPU_PROFILE=1` | GPU time per kind of work at exit (timestamp queries; same table as D3D11) |
| `RG_PRESENT_LOG=path` | (runtime, both backends) one row per present: wall time, kind, field (`tools/native/present_pacing.py`) |

When Vulkan is selected but unavailable (no loader, no Vulkan 1.3 device, a required feature
missing), stderr says `rg gpu: Vulkan backend unavailable (...); using Direct3D 11` and the
run continues on D3D11. A successful start prints `rg gpu: Vulkan <device> (API x.y.z, interlock)`.
The exe has no link-time Vulkan dependency: volk opens `vulkan-1.dll` / `libvulkan.so.1` at
run time.

## Build

- `src/native/render/nr_vulkan.cmake` (included from the render CMakeLists' native-device
  block): option `RG_GPU_VULKAN` (default ON), finds a SPIR-V capable DXC (`RG_DXC`; default
  search `../tools/dxc/bin/x64`, `$VULKAN_SDK/Bin`; each candidate is probed, the Windows
  SDK's dxc has no SPIR-V code generation), compiles the 24 shader entries into
  `<build>/src/native/render/spv/*.h` and adds `nr_vulkan.cpp`, `nr_vk_vma.cpp`,
  `third_party/volk/volk.c` to `rg_native_render` with `RG_HAVE_VULKAN=1`. Without DXC the
  backend is left out with a warning (the build stays as before).
- `python tools/native/fetch_dxc.py` fetches the pinned DXC release (v1.9.2609, SHA-256
  checked) to `../tools/dxc` (`--linux` for the Linux archive). Build tool only.
- `python tools/native/fetch_vulkan_deps.py [--check]` vendors / verifies the third-party
  headers (pins in `third_party/VENDORED.txt`).

Third party (THIRD_PARTY_NOTICES.md): Khronos Vulkan-Headers (Apache-2.0 OR MIT,
`third_party/vulkan`), volk (MIT, `third_party/volk`), Vulkan Memory Allocator (MIT,
`third_party/vma`). DXC (NCSA / Apache-2.0 with LLVM exception) only runs at build time.

## Shaders

The HLSL of `src/gpu/shaders` (`gs_util.hlsl`, `gs_draw.hlsl` (`CS_decode` only),
`gs_post.hlsl`, `nr_draw.hlsl`) is compiled by DXC with
`-spirv -fspv-target-env=vulkan1.3 -fvk-use-dx-layout`, vertex shaders with `-fvk-invert-y`
(so the framebuffer has D3D's orientation: no other flip anywhere), and the register classes
shifted into one descriptor set: binding = register + 0 (`b`), 16 (`t`), 32 (`s`), 48 (`u`).
`RasterizerOrderedTexture2D` becomes `OpBeginInvocationInterlockEXT` / `End` (pixel interlock,
ordered). The only source change: `nr_draw.hlsl`'s `PSOut` gives the dual-source output
`[[vk::location(0), vk::index(1)]]` under `#ifdef __spirv__` (fxc never sees it; its outputs
were checked byte-identical).

## Design (`nr_vulkan.cpp`)

- **Bindings**: each pipeline's descriptor-set layout comes from reflecting its SPIR-V
  (binding, descriptor type) at start; a slot table indexed by binding plays the role of
  D3D11's `*SetShaderResources` / `*SetUnorderedAccessViews` / `*SetConstantBuffers`; each draw
  or dispatch pushes the bound slots (`VK_KHR_push_descriptor`), unbound ones get dummies.
- **Pipelines**: created on first use from a key (program, attachment formats, vertex layout,
  blend, cull, depth state, bias, clamp); viewport and scissor are dynamic. Rendering uses
  dynamic rendering (no render-pass objects).
- **Synchronisation**: every image lives in `VK_IMAGE_LAYOUT_GENERAL`. A dirty flag tracks
  writes; the next operation that is not a draw into the same attachments first records one
  global memory barrier (all commands -> all commands). Consecutive draws into the same
  attachments share one rendering instance (ordered by the rasteriser; ordered views by the
  interlock). Transfers, compute and any change of attachments end the instance.
- **Uploads**: a host-visible ring (96 MB): constants, immediate vertices, mirror uploads,
  merges, transfer batches, mesh data; requests over a quarter of the ring get a staging buffer
  of their own. Wrapping waits for the GPU (rare).
- **Read-backs** (display, `rt_read`, `mirror_download`, `clut_read`, `snap_map`): submit and
  wait for that submission's fence.  `readback_lag` (`gpu_config.readback_lag`,
  `RG_GPU_READBACK_LAG=1`): the display copy goes into one of two host buffers and the call returns
  the previous call's frame (the first call, or a new size, returns its own frame and keeps it
  queued), exactly D3D11's `readback_lag`.  Checked with dumps at fields 9,000 / 9,030 / 9,060:
  the lagged dump of each field equals the unlagged dump of the field before.
- **GPU profile** (`RG_GPU_PROFILE=1`): a timestamp query pool per submission, a pair of
  bottom-of-pipe stamps around each native draw, decode, load, write-back and display (+ copy),
  read when that submission's fence is waited; the exit table has D3D11's format and categories
  (first 3,000 route fields: 845 decodes, 35 write-backs, 30 loads, 59,352 native draws on both
  backends; GPU total 109 ms Vulkan, 125 ms D3D11).
- **Memory**: VMA (Windows drivers cap the number of allocations at 4096; the texture and mesh
  caches alone can exceed that).
- **Meshes**: device-local vertex / index buffers; `nr_mesh_prewarm` (other threads) fills a
  staging buffer, the render thread records the copy at the first lookup.
- **Ordered views are made coherent**: DXC emits the `RasterizerOrderedTexture2D` storage
  images without the `Coherent` decoration; D3D11 ROVs are coherent between the ordered
  invocations. `shader_make` adds `OpDecorate %var Coherent` to every storage image of a fragment
  shader before creating the module (`RG_VK_NO_COHERENT=1` = DXC's SPIR-V as is, a control).
  Without it, interlocked reads in later draws saw stale values: dark speckles on the town
  ground, PSNR 25-36 dB on the route (first run, 2026-10-25).
- **Depth bias** (`nr_draw` meshes, D3D11 `DepthBias = -2`, `$RG_NR_ZBIAS`): with a D32
  depth attachment as D3D11. With depth in an ordered view (`zrov`, the default with interlock)
  there is no depth attachment; NVIDIA's Vulkan then biases `FragCoord.z` as for a 24-bit UNORM
  buffer, which put the town sky glare behind the far geometry (fields 26,930 / 28,900: 25.7 dB,
  2.3 % bad). D3D11 without a DSV biases `SV_Position.z` by an amount none of the Vulkan
  representations reproduces (measured on the route, D3D11 the reference, PSNR min of the first
  9-14 fields: no bias 45.6 dB, float representation via an unused D32 attachment 45.6, UNORM24
  -2 units 41.8, UNORM24 -4 units 40.2). Default: no rasterizer bias for ordered-depth draws
  (the shader's own 2 units, `nr_draw.hlsl` NR_ZROV, still apply); `$RG_VK_ZROV_BIAS=float|d32|d24|d16`
  and `$RG_VK_ZROV_BIAS_UNITS` keep the alternatives for measurement. With `RG_NR_ZBIAS=0` (both
  backends) or `RG_GPU_NO_ZROV=1` the route is pixel-identical to D3D11.
- **Counters**: `RG_VK_STATS=1` prints submits, fence waits, ring wraps, barriers, rendering
  instances, draws, dispatches and pipelines at exit.
- **Zero-copy presentation**: section "Presentation" below (since 2026-10-25 evening; before, Vulkan
  read every frame back and the interpolated presentation was off with Vulkan).

## Presentation (zero-copy, interpolation)

D3D11 presents without a read-back by copying the frame into a DXGI shared texture that the SDL
window's Direct3D 11 renderer opens (`rg_host_present_shared`, keyed mutex).  Vulkan does the
same on **one device**: the window's renderer becomes **SDL's Vulkan renderer created on the
backend's own `VkInstance` / `VkDevice`** (`SDL_PROP_RENDERER_CREATE_VULKAN_*`), and frames are
backend images wrapped as SDL textures (`SDL_PROP_TEXTURE_CREATE_VULKAN_TEXTURE_NUMBER`).  Nothing
Windows-specific: the surface comes from `SDL_Vulkan_CreateSurface`, the instance extensions are
looked up by name (`VK_KHR_surface` + whichever of win32 / xlib / xcb / wayland the loader has),
so the same code is the Linux presentation path.  Chosen over the alternatives: a swapchain owned
by the backend would leave the settings overlay (drawn by the SDL renderer) without a renderer on
that window; an external-memory export to the D3D11 renderer is Windows-only.

- **Device sharing** (`nr_vulkan.cpp` init): with the surface extensions, `VK_KHR_swapchain` and
  timeline semaphores available and a graphics queue family with at least 2 queues, the device gets
  2 queues of that family; the **backend submits on queue 1**, the presenter (SDL, which always takes
  queue 0) on queue 0 (a `VkQueue` is externally synchronised and the two submit from different
  threads).  Otherwise (`RG_VK_PRESENT=0`, a family with one queue, e.g. RADV's graphics family)
  `gpu_vk_present_device` returns -1 and frames are read back as before.
- **Hand-off**: `gpu_start` (runtime.c) asks `gpu_vk_present_device` and calls `rg_host_use_vulkan`,
  which checks `SDL_Vulkan_GetPresentationSupport` for that family, destroys the window's renderer
  (D3D11 by default) and creates the Vulkan one on the device (failure: the default renderer again
  and the read-back path).  `gpu_stop` calls `rg_host_drop_vulkan` before the device is destroyed.
- **Frames**: `display` / `display_post` with `out == NULL` copy the composed frame into one of two
  images (RGBA8; they only grow, the frame is their top-left w x h, presented with a source
  rectangle, so a window resize does not reallocate every frame) and leave it in
  `SHADER_READ_ONLY_OPTIMAL` (what SDL assumes for a wrapped image); `shared_out()` returns a
  `gpu_vk_frame` (gpu.h; host.h `rg_host_vk_frame`, same layout, static assert in runtime.c).
- **Synchronisation**: every backend submission signals a timeline semaphore with its serial.  The
  presenter's `acquire()` marks the slot busy and waits on the CPU for the serial of the submission
  that wrote it (normally long done: the overlapped present shows the previous field's frame);
  SDL's `SDL_FlushRenderer` (in `present_tex`) submits the draw that samples it and waits for its
  queue, then `release()` frees the slot.  The backend reuses a slot only when it is not busy (a
  handed frame the presenter never took is taken back; a busy one is waited for, 500 ms as D3D11's
  keyed mutex).  SDL's binary-semaphore hooks (`SDL_AddVulkanRenderSemaphores`) were not used: a
  minimised window sends no commands, so their waits would pile up.
- **Interpolated presentation** (`display.interpolation`) needs nothing else: it was off with
  Vulkan only because there was no zero-copy present.
- **Fix on the way (both backends)**: zero-copy presentation had been switched off for the whole
  run whenever the first present found the display off (no size: the first fields after power-on),
  so every windowed run presented through the read-back path (D3D11 too, and so no windowed
  interpolation from power-on).  A frame with no size now presents nothing and keeps zero-copy
  (runtime.c `ov_present_pending` and the synchronous path); a real failure prints
  `zero-copy presentation failed, reading frames back`.

## Verification

`tools/native/backend_compare.sh NATIVE_EXE TAG [SCALE] [route|boot:FIXTURE]`: the same exe
twice (`RG_GPU_API=d3d11`, `=vulkan`), display dumps at the same fields, per-frame PSNR / bad% /
SSIM of Vulkan against D3D11 (`render_imgcmp.py`, D3D11 the reference) and both run hashes
(must be identical: the backend must not change game logic). The renderer gate with Vulkan:
`RG_GPU_API=vulkan tools/native/render_gate.sh ORACLE NATIVE TAG` (the oracle twin has no
native device and ignores the variable).

## Results (2026-10-25, exe `out/vk/b8/rg-game.exe`, build `build/vk-i686`, RTX 3080, driver 610.62)

Device line: `rg gpu: Vulkan NVIDIA GeForce RTX 3080 (API 1.4.341, interlock)` (32-bit process,
`SysWOW64/vulkan-1.dll`).

**Vulkan vs D3D11, golden route** (`backend_compare.sh ... final 1 route`, 24 milestone fields,
`out/nrender/runs/bc_final*`): run hash identical (`ab389a3d1d0232e0`, both backends and the
1025b play-test build); 6 fields pixel-identical (title, transporter menu), the rest 45.6-63.5 dB,
0.00 % bad pixels, SSIM >= 0.999, no failing field. The remaining differences are single-pixel
depth-test outcomes of ordered-depth mesh draws (the bias, above): with `RG_NR_ZBIAS=0` or
`RG_GPU_NO_ZROV=1` or `RG_GPU_NO_ROV=1` on both, every compared field is identical.
ms/field (headless, wall, fields >= 7,400, machine shared): D3D11 9.02, Vulkan 8.85.

**D3D11 unchanged**: the D3D11 run of the same exe is pixel-identical to the 1025b play-test
gate's native dumps at all 24 route fields (`rt_g_pt1025b_nat` vs `bc_final_d3d11`); the fxc
headers of `nr_draw.hlsl` are byte-identical before / after the `__spirv__` annotation.

**Renderer gate with Vulkan** (`RG_GPU_API=vulkan render_gate.sh out/vk/b8/rg-game-oracle.exe
out/vk/b8/rg-game.exe vk1_* 1`, oracle twin = emulated GS; D3D11 numbers of the 1025b gate in
brackets):

| Part | Vulkan | D3D11 (1025b) |
| --- | --- | --- |
| route x1, 24 fields | PSNR min 31.45, bad max 0.88 %, 0 failing; run hash = oracle | 31.31, 0.91 %, 0 failing |
| save2 | 34.61 dB, 0.02 %, PASS | 34.40, 0.03 % |
| factory | 34.59 dB, 0.02 %, PASS | 34.39, 0.03 % |
| insectron | 38.25 dB, 0.00 %, PASS | 38.25, 0.00 % |
| save2_battle2 | 38.16 dB, 0.00 %, PASS | 37.81, 0.01 % |
| ch06_vedan / ch09_labyrinth / ch12_mariglenn / ch13_mariglenn | 36.20 / 35.35 / 45.20 / 39.53 dB, all PASS | 36.19 / 35.29 / 45.22 / 39.52 |
| mapcheck | 5 DRAWN, 0 MISSING | 5 / 0 |
| save2 close-up x3 (3,790 / 3,850) | 38.93 / 38.96 dB, 0.01 / 0.02 % | 38.25 / 38.33 dB |

Every boot fixture's run hash equals the oracle's (and the D3D11 gate's). A windowed run
(`out/vk/win1`) presents through the read-back path. Static gates on the same exe:
`link_audit.py check --forbid all --extra rg_ps2_hwbus` PASS, `addr_census.py --check` PASS
(0 arith, 0 marker); ctest `settings.*` / `input.*` (the built ones) pass with the new
`display.backend` setting.

## Validation

The Vulkan SDK ships 64-bit layers only on Windows; the i686 exe needs a 32-bit
`VK_LAYER_KHRONOS_validation`.  `tools/native/build_vvl_x86.ps1` builds it from source:
Vulkan-ValidationLayers `vulkan-sdk-1.4.363.0` (the vendored headers' version) and the
dependencies its `update_deps.py` pins (Vulkan-Headers, Vulkan-Utility-Libraries, SPIRV-Headers,
SPIRV-Tools, mimalloc: Apache-2.0 / MIT), clang-cl `-m32` + lld-link + Ninja with the MSVC x86
libraries (`tools/native/vvl_x86_toolchain.cmake`; no `CMAKE_SYSTEM_NAME`: a cross-compiling
configuration makes the dependencies search `CMAKE_FIND_ROOT_PATH` only and they do not find each
other), output `../tools/vvl-x86/bin`.  A development tool: not vendored,
not shipped (THIRD_PARTY_NOTICES.md).

**Loading it**: this machine runs the game elevated, and the loader then ignores
`VK_ADD_LAYER_PATH` / `VK_LAYER_PATH` (it reads only the system registry, which this lane did not
change).  So with `RG_VK_LAYER_DLL=path` the backend puts the layer in front of the loader itself
(`nr_vulkan.cpp` `vkl`): the layer library's `vkGetInstanceProcAddr` (from
`vkNegotiateLoaderLayerInterfaceVersion`) creates the instance and the device with the loader's
`VK_STRUCTURE_TYPE_LOADER_{INSTANCE,DEVICE}_CREATE_INFO` link structures pointing at the loader,
and volk loads every other function through the layer.  Handle wrapping is disabled
(`VK_VALIDATION_FEATURE_DISABLE_UNIQUE_HANDLES_EXT`): the window's renderer calls the driver
directly with the backend's images (a wrapped handle crashed in SDL's `vkCreateImageView`), so
the presenter's own calls are not validated; the backend's are.  Debug-only code (a `dlopen`
branch for Linux).

`tools/native/vk_validate.sh EXE TAG [FIELDS] [ARGS]` (`WINDOWED=1`, `RG_VK_VALIDATE_SYNC=1` pass
through) runs the golden route from power-on and groups the messages by id.

## Results 2 (2026-10-25 evening: presentation, readback_lag, profile, validation)

Build `build/vk2-i686`; gate exes `out/vk2/b6` (Vulkan gate) and `out/vk2/b7` (D3D11 gate; b6 +
the two runtime message tweaks and the x64 lane's i686-neutral header edits).  Logs `out/vk2/`,
`out/nrender/runs/{bc_vk2*,gate_vk2*,vkval_*}`, `out/interp/pose/vk2{d,v}*`, `out/pace/`.

- **Rendering unchanged**: `backend_compare.sh b6 vk2 1 route`: run hash ab389a3d1d0232e0 both;
  Vulkan vs D3D11 24 fields, 6 identical, PSNR min 45.60, 0.00 % bad, as before; the new exe's
  D3D11 dumps are identical to the previous lane's (`bc_final_d3d11`) at all 24 fields, and its
  Vulkan dumps to `bc_final_vulkan` at all 24.  fxc headers: 37, byte-identical to `build/vk-i686`.
- **Gates**: `RG_GPU_API=vulkan render_gate.sh` (b6): route 24 fields PSNR min 31.45, bad max
  0.88 %, failing 0, run hash = oracle; 8 boot fixtures PASS with oracle run hashes (34.61 / 34.59 /
  38.25 / 38.16 / 36.20 / 35.35 / 45.20 / 39.53 dB); mapcheck 5 / 5; close-up x3 38.93 / 38.96 dB.
  Default (D3D11, b7): route 31.31 / 0.91 % / 0 failing, run hash = oracle; mapcheck 5 / 5;
  close-up 38.25 / 38.33 dB; boot fixtures: save2 PASS (34.40 dB), the rest **not run** (stopped
  at the wrap-up).  `link_audit.py check --forbid all --extra rg_ps2_hwbus` PASS, `addr_census.py
  --check` PASS (0 / 0) (b4 exe, same code paths).  ctest -j2 in `build/vk2-i686`: 748 / 748
  (7 skipped as usual).
- **Pose interpolation** (`interp_pose.sh` ch07_rosa battle, simulated 144 Hz, ZSCALE 0 / 2 / 4,
  same battle state for both backends): run hash 88081d075183d936 both; groups posed 7,752 of
  10,302 both; step judder (real image) 1.46 / 0.53 / 0.33 D3D11 vs 1.46 / 0.54 / 0.34 Vulkan;
  isolated step judder 1.96 / 0.64 / 0.34 vs 1.97 / 0.64 / 0.34.  Switch ratio with D3D11's
  switch list for both: isolated 2.03 / **1.18** (D3D11) vs 2.04 / **1.18** (Vulkan), real image
  2.32 / 1.52 vs 2.28 / 1.51 (checkpoint 13: 2.03 / 1.18, 2.32 / 1.52).  Each backend's own
  switch list differs (45 vs 38 switches): D3D11's mode-0 isolated run has 0.05-0.08 crop
  changes inside a game frame at 8 presents (just above the 0.05 threshold), Vulkan's stay below.
- **Windowed, zero-copy + interpolation**: Vulkan presents through the shared device
  (`window presents from the Vulkan device (zero-copy)`), interpolated presents on Vulkan
  (title, 1,500 fields, 144 cap, vsync off: 3,361 interpolated presents, 143.8 presents/s vs
  D3D11 141.0; interval cv 0.17 vs 0.26, within +-25 % of 6.94 ms 88.6 % vs 83.5 %).  Run hash
  unchanged by presentation (ac5613cfc25c920d both).
- **Pacing at 144 Hz on the field route** (`present_pace.sh ... field 9800 144`): measured while
  two gate runs and other lanes' games loaded the machine, so the absolute rates are not
  representative (D3D11 interpolated 11-19 presents/s, Vulkan 21-30; no-interpolation 60 cap:
  48.9 vs 51.8/s; Vulkan read-back control `RG_VK_PRESENT=0` 30/s).  To redo on a quiet machine.
- **FPS counter capture** (2026-10-26, rpkt): GDI screen grabs and PrintWindow return black for
  the zero-copy window; `tools/native/wincap.py --dd` grabs through DXGI Desktop Duplication
  (`tools/native/ddcap.cpp`, x64, built by `ddcap_build.cmd` into `out/tools/ddcap.exe` on first
  use; the window is raised topmost for the grab and a grab is refused when another window covers
  it).  1025c, 1280x960 window, `--set display.fps_counter=detailed`: D3D11 at 20 / 26 s shows the
  detailed line; Vulkan `RG_VK_PRESENT=0` too ("49 FPS 20.5 ms ... logic 30/s"); Vulkan zero-copy:
  of 6 grabs (10, 14 s; 20, 26 s; 20, 26 s again) 5 were black over the whole client area
  and one (26 s, opening movie) showed the picture with **"32 FPS"** only -- the counter is drawn,
  but in the short form and the grabs are mostly black.  Open: whether the window really shows
  black frames under zero-copy (flicker) or Desktop Duplication misses that swapchain's flips;
  next `wincap.py --dd --burst 12` on a quiet, unattended desktop.
- **FPS counter / black grabs, answered from in-process read-back** (2026-10-26, interp3; no
  screen capture): `RG_WINDOW_SHOT=FIELD:PNG` + new `RG_WINDOW_SHOT_HOST=1` (host_sdl.c
  present_tex: the window shot taken after the FPS counter, i.e. `SDL_RenderReadPixels` of the
  swapchain image about to be presented), `tools/native/vkshot.sh TAG EXE API FIELD...`
  (power-on, one windowed run per field, `display.fps_counter=detailed`).  Vulkan zero-copy at
  fields 600 / 840 / 1,200 / 1,560 / 1,800 / 2,400: every image has the **detailed** line
  ("30 FPS 33.5 ms (max 45.3) logic 30/s" form, text to x = 579 in all) and is **pixel-identical
  to D3D11** below the counter (mean difference 0.0 at all six fields); fields 600 / 840 are
  98.5 / 94.8 % black in both APIs (power-on logo fades), the other four 2.6-5.1 % in both.  Battle (windowed from a state, 144 Hz panel, interpolation on): Vulkan and D3D11 back
  buffers both carry the picture and the detailed line.  Code: the frame image is released only
  after `SDL_FlushRenderer`, whose `InvalidateCachedState` submits and waits for the queue
  (SDL_render_vulkan.c `VULKAN_IssueBatch` + `VULKAN_WaitForGPU`), and the overlay / counter go
  into a LOAD render pass on the same swapchain image: no ordering bug.  So **no port bug found**: what
  the window presents is right; the black / short-line grabs are most likely Desktop
  Duplication's view of a Vulkan flip-model swapchain (independent flip), partly the logo fades.  Not tested: what a human sees on the monitor.
- **Validation** (32-bit layer, backend-loaded): golden route 9,000 fields headless, windowed
  2,400 fields with interpolation at 144, and both again with synchronization validation: **no
  errors**; one warning id, `Undefined-Value-ShaderOutputNotConsumed-DynamicRendering` (the
  ordered-colour draws `PS_nr_c` / `PS_nr_cz` write `SV_Target` / `SV_Target1` with no colour
  attachment bound; harmless, the writes are discarded by design).  Run hash under validation =
  without (fead30e28c5f5a6a at 3,000 fields).

Next steps: (1) pacing matrix on a quiet machine (`present_pace.sh` configs d3d11 / vulkan x
144 / 120 / uncapped x vsync on / off, interpolation on; a 60 no-interpolation baseline); (2) the
remaining D3D11 boot-fixture gate parts on the final exe (`render_gate.sh ... boot`); (3) Linux
run of the presentation path once the x64 / Linux CMake wiring lands; (4) optional: drop the
unused `SV_Target` outputs of the ordered-colour pixel shaders under `__spirv__` to silence the
validation warning.

## Linux: what remains

Done here (checked with the Debian 12 i386 sysroot, `clang++ --target=i686-linux-gnu -fsyntax-only`):
`nr_vulkan.cpp`, `nr_vk_vma.cpp`, `volk.c` and `nr_dev.cpp` / `nr_iprec.cpp` compile for
Linux; the backend uses no Windows API (volk `dlopen`s `libvulkan.so.1`; `nr_vulkan.cmake` links
`${CMAKE_DL_LIBS}` on UNIX); `nr_dev.cpp` calls `gpu_backend_d3d11_create` only on `_WIN32` and
selects Vulkan unconditionally elsewhere; the shader step is plain DXC (Linux: the distribution's
`directx-shader-compiler`, the Vulkan SDK's `dxc`, or `fetch_dxc.py --linux`).

Not done (needs CMake changes in files other lanes own, and cannot be run here):

1. **CMake wiring of the native device without `rg_gpu`.** Today the native device block of
   `src/native/render/CMakeLists.txt`, `RG_HAVE_GPU` of `rg_runtime` (`src/runtime/CMakeLists.txt`)
   and the drop of `rg_gpu rg_ps2_gs` from rg-game (`cmake/native_only.cmake`) all key on
   `if(TARGET rg_gpu)`, and `src/gpu/CMakeLists.txt` returns on non-WIN32 (fxc, D3D11). On Linux
   with `RG_NATIVE_ONLY` and `RG_GPU_VULKAN`: build the device block without `nr_d3d11.cpp` and
   without the `rg_gpu_shaders` dependency; define `RG_HAVE_GPU` for the **native-only clones**
   only (`rg_runtime_nonly`, `rg_native_render_nonly`: the default-config `rg_runtime` still
   has no `gpu_core.cpp` on Linux, so tests linking it must not see `RG_HAVE_GPU`); drop
   `rg_ps2_gs` from rg-game so the clones get `RG_NATIVE_GS=1`. Then `gpu_start` runs the
   native device instead of the headless renderer.
2. **Presentation.** Done portably (section "Presentation": SDL's Vulkan renderer on the backend's
   device, surface from `SDL_Vulkan_CreateSurface`); untested on Linux.  A driver whose graphics
   family has one queue (RADV) falls back to the read-back path; sharing one queue would need a
   lock around SDL's submissions.
3. **Run-time packaging:** `libvulkan1:i386` and a 32-bit ICD (Mesa RADV / ANV, NVIDIA's i386
   driver). 32-bit Vulkan drivers are the least tested combination; the x64 build (PLAN.md P7,
   the x64 lane) is the better Linux GPU target. Features needed: Vulkan 1.3,
   `VK_KHR_push_descriptor`, `dualSrcBlend`, `depthClamp`; optional
   `VK_EXT_fragment_shader_interlock` + `fragmentStoresAndAtomics` (without them `rov()` and
   `zrov()` are false and the core uses its non-ordered paths, as D3D11 without ROVs).
4. **Gates on Linux:** save states are Windows-only (docs/LINUX.md), so the fixture tools need
   power-on runs; `backend_compare.sh` / `render_gate.sh` assume `rg-game.exe` and Git bash paths.
