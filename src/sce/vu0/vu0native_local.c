/* SPDX-License-Identifier: CC0-1.0 */
/* rg-vu0native-tests `local`: compiled twice with RG_VU0_LOCAL (VNL_SIDE = a,
 * b); VNL_CTX selects the named context `vntest` instead (port/vu0_ctx.h).
 *
 * Function-local register files (vu0frame, docs/NATIVE-CPU.md section 4;
 * port/vu0.h has no file-scope fallback any more): every function below
 * opens its own frame, so a value set in one call is not seen by another
 * (get5 after set5 reads the reset value 0), a frame helper runs on its
 * caller's file (roundtrip), and under a named context RG_VU0_FRAME is a
 * no-op, so set5 in one file is read by get5 in another. */
#ifdef VNL_CTX
#define RG_VU0_CTX_NAME vntest
#include "port/vu0_ctx.h"
#endif
#include "port/vu0.h"

#define VNL_CAT2(a, b) a##b
#define VNL_CAT(a, b) VNL_CAT2(a, b)
#define VNL_FN(n) VNL_CAT(VNL_CAT(vnl_, VNL_SIDE), n)

void VNL_FN(_set5)(float x)
{ RG_VU0_FRAME;
    float v[4] __attribute__((aligned(16))) = {x, x, x, x};
    rg_vu0_lqc2(5, v);
}

float VNL_FN(_get5)(void)
{ RG_VU0_FRAME;
    return rg_vu0_getf(5, 0);
}

/* a frame helper as tools/stages/vu0frame.py writes it */
static void vnl_load5(rg_vu0_state *rg_vu0_p_, float x)
{
#pragma push_macro("rg_vu0")
#define rg_vu0 (*rg_vu0_p_)
    float v[4] __attribute__((aligned(16))) = {x, x, x, x};
    rg_vu0_lqc2(5, v);
#undef rg_vu0
#pragma pop_macro("rg_vu0")
}

/* set through the helper, read in the caller's frame */
float VNL_FN(_roundtrip)(float x)
{ RG_VU0_FRAME;
    vnl_load5(&rg_vu0, x);
    return rg_vu0_getf(5, 0);
}

#if !RG_VU0_IS_LOCAL
#error "vu0native_local.c must be built with RG_VU0_LOCAL"
#endif
