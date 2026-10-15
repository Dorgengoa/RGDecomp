#include "types.h"

/* MAIN LensWorkTexRegister_2f7620 -- two 0x31D surfaces, the second at half size.
   The `sra 1` + `bgez` fixup pairs are signed `/ 2`, written inline at
   the call so the halving is not CSEd into its own register. */

extern void *GetDrawCtx_15de80(void);
extern void *GetDrawCtxNameTable_15de40(void);
extern s32 DrawEnvGetWidth_1451e0(void *);
extern s32 DrawEnvGetHeight_1451d0(void *);
extern void *NameTableAddEntry_159b70(void *, s32, void *, s32, s32, s32, s32, s32,
                          s32, s32);
extern u8 D_00461DA0[];
extern u8 D_00461DB0[];

void LensWorkTexRegister_2f7620(void)
{
    void *v;
    void *w;
    s32 cx;
    s32 cy;

    v = GetDrawCtx_15de80();
    w = GetDrawCtxNameTable_15de40();
    cx = DrawEnvGetWidth_1451e0(v);
    cy = DrawEnvGetHeight_1451d0(v);
    NameTableAddEntry_159b70(w, 0x31D, D_00461DA0, 0, cx, cy, 0x20, 0, 0, 0);
    NameTableAddEntry_159b70(w, 0x31D, D_00461DB0, 0, cx / 2, cy / 2, 0x20, 0, 0, 0);
}
