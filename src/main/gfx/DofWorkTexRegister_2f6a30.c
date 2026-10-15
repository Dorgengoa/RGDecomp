#include "types.h"

/* MAIN DofWorkTexRegister_2f6a30 -- one 0x31B surface sized from the current
   render target's DrawEnvGetWidth_1451e0 / DrawEnvGetHeight_1451d0. */

extern void GameSceneDofSetOverridePreset_2f6ab0(void);
extern void *GetDrawCtx_15de80(void);
extern void *GetDrawCtxNameTable_15de40(void);
extern s32 DrawEnvGetWidth_1451e0(void *);
extern s32 DrawEnvGetHeight_1451d0(void *);
extern void *NameTableAddEntry_159b70(void *, s32, void *, s32, s32, s32, s32, s32,
                          s32, s32);
extern u8 D_00461D18[];

void DofWorkTexRegister_2f6a30(void)
{
    void *v;
    void *w;
    s32 cx;
    s32 cy;

    GameSceneDofSetOverridePreset_2f6ab0();
    v = GetDrawCtx_15de80();
    w = GetDrawCtxNameTable_15de40();
    cx = DrawEnvGetWidth_1451e0(v);
    cy = DrawEnvGetHeight_1451d0(v);
    NameTableAddEntry_159b70(w, 0x31B, D_00461D18, 0, cx, cy, 0x20, 0, 0, 0);
}
