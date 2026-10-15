#include "types.h"

/* MAIN ShadowWorkTexRegister_2f6c90 -- four surface registrations on ids 0x320/0x321.
   Prototype for NameTableAddEntry_159b70 taken from src/s17q10/DofWorkTexRegister_2f6a30.c
   (10 integer arguments, the last two on the stack). */

extern void *GetDrawCtx_15de80(void);
extern void *GetDrawCtxNameTable_15de40(void);
extern s32 DrawEnvGetWidth_1451e0(void *);
extern s32 DrawEnvGetHeight_1451d0(void *);
extern void *NameTableAddEntry_159b70(void *, s32, void *, s32, s32, s32, s32, s32,
                          s32, s32);
extern u8 D_00461D48[];
extern u8 D_00461D58[];
extern u8 D_00461D68[];
extern u8 D_00461D80[];

void ShadowWorkTexRegister_2f6c90(void)
{
    void *v;
    void *w;
    s32 cx;
    s32 cy;

    v = GetDrawCtx_15de80();
    w = GetDrawCtxNameTable_15de40();
    cx = DrawEnvGetWidth_1451e0(v);
    cy = DrawEnvGetHeight_1451d0(v);
    NameTableAddEntry_159b70(w, 0x320, D_00461D48, 0, cx, cy, 0x20, 0, 0, 0);
    NameTableAddEntry_159b70(w, 0x320, D_00461D58, 0, 0xC0, 0xC0, 0x20, 0, 0, 0);
    NameTableAddEntry_159b70(w, 0x321, D_00461D68, 0, 0x40, 0x40, 0x20, 0, 0, 0);
    NameTableAddEntry_159b70(w, 0x321, D_00461D80, 0, 0x40, 0x40, 0x20, 0, 0, 0);
}
