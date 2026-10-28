/* SPDX-License-Identifier: CC0-1.0 */
/* The graphics settings as renderer parameters (src/gpu/gpu_gfx.c, no GS model in it) for the
 * native-only device (docs/NATIVE-RENDER.md "Checkpoint 10"); default builds take it from rg_gpu. */
#if defined(RG_NATIVE_ONLY) && RG_NATIVE_ONLY
#include "gpu_gfx.c"
#endif
