/* Select a named, shared VU0 register context for the rest of this
 * translation unit (docs/NATIVE-CPU.md "Cross-file protocols").
 *
 *     #define RG_VU0_CTX_NAME xfbox
 *     #include "port/vu0_ctx.h"
 *
 * With RG_VU0_LOCAL every file has a private register file; the few
 * functions that hand values to each other in VU registers across files (the
 * census `cross` rows) name the same context, which src/sce/vu0/vu0_ctx.c
 * defines.  Under the global model this header does nothing.  Include it
 * before any code (and before vu0inline.h) of the file. */
#ifndef RG_VU0_CTX_NAME
#error "define RG_VU0_CTX_NAME before including port/vu0_ctx.h"
#endif
#include "port/vu0.h"
#if RG_VU0_IS_LOCAL
#define RG__VU0CTX2(n) rg_vu0_ctx_##n
#define RG__VU0CTX(n) RG__VU0CTX2(n)
#ifdef __cplusplus
extern "C" rg_vu0_state RG__VU0CTX(RG_VU0_CTX_NAME);
#else
extern rg_vu0_state RG__VU0CTX(RG_VU0_CTX_NAME);
#endif
#undef rg_vu0
#define rg_vu0 RG__VU0CTX(RG_VU0_CTX_NAME)
/* the whole file runs on the context: no function-local frames (vu0frame) */
#undef RG_VU0_FRAME
#define RG_VU0_FRAME ((void)0)
#endif
