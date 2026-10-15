/* PARKED at triage (0 round trips): has an adda.s/madd.s M2C_ERROR site (see
 * ps2-float-accumulator lever) feeding an s128 local and several unresolved
 * "?" stack locals (sp70, sp60) passed by address -- would need a raw-asm
 * read to recover the exact accumulator constants and stack layout together.
 * Deferred to preserve lane throughput. See asm/matchings/main/InsectCageItemIconDraw_385d80.s. */
/* s49m: MATCH */
#include "types.h"
#include "vec.h"

typedef struct Sub2 {
    u8 pad0[0x2C];
    s16 m2C;
} Sub2;

typedef struct Sub1 {
    u8 pad0[0x10];
    Sub2 *m10;
} Sub1;

typedef struct Self {
    Vec4 pos;
    Sub1 *m10;
    f32 m14;
    s32 m18;
} Self;

extern void *GetDrawCtxNameTable_15de40(void);
extern s16 *NameTableFindByName_159fb0(void *, void *, s32);
extern s32 CameraProjectBillboardRect_15cde0(s32 *, s32 *, Vec4 *, s32, f32, f32);
extern void UiIconGetCellRect_288830(s32, s16 *, s16 *, s16 *, s16 *);
extern f32 Sinf_128fd0(f32);
extern void *GetDrawCtx_15de80(void);
extern void DrawListAddTexLoad_1418c0(void *, s32, f32);
extern void *DrawListBeginPrim_141b00(void *);
extern void GsPktSetup2DState_3892a0(void *);
extern void GsPktEnableZTest_13e460(void *, s32);
extern void GsPktOpenPrim_13f730(void *, s32);
extern void GsPktSetTexture_13ec00(void *, s16 *);
extern void GsPktSetRGBAQ_13ee40(void *, s32, s32, s32, s32);
extern void GsPktSetUV_13ed60(void *, s32, s32);
extern void GsPktSetXYZVecI_13eeb0(void *, s32 *);
extern void GsPktClose_13f5b0(void *);
extern void DrawListEndPrim_141a20(void *);
extern u8 D_00463F20[];
extern f32 D_0047D81C;

void InsectCageItemIconDraw_385d80(Self *self)
{
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    Vec4 pos;
    s32 a[4];
    s32 b[4];
    s32 n;
    s16 *r;
    s32 alpha;
    void *g;
    void *q;

    if (self->m10 == 0) {
        return;
    }
    n = self->m18;
    if (n <= 0) {
        return;
    }
    r = NameTableFindByName_159fb0(GetDrawCtxNameTable_15de40(), D_00463F20, -1);
    if (r == 0) {
        return;
    }
    *(u128 *)&pos = *(u128 *)&self->pos;
    if (CameraProjectBillboardRect_15cde0(a, b, &pos, 0, D_0047D81C, D_0047D81C) == 0) {
        return;
    }
    a[3] = 1;
    b[3] = 1;
    UiIconGetCellRect_288830(self->m10->m10->m2C, &x, &y, &w, &h);
    alpha = 128.0f + 64.0f * Sinf_128fd0(self->m14);
    g = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(g, *r, 1.0f);
    q = DrawListBeginPrim_141b00(g);
    GsPktSetup2DState_3892a0(q);
    GsPktEnableZTest_13e460(q, 1);
    GsPktOpenPrim_13f730(q, 6);
    GsPktSetTexture_13ec00(q, r);
    GsPktSetRGBAQ_13ee40(q, alpha, alpha, alpha, n);
    GsPktSetUV_13ed60(q, x, y);
    GsPktSetXYZVecI_13eeb0(q, a);
    GsPktSetUV_13ed60(q, x + w, y + h);
    GsPktSetXYZVecI_13eeb0(q, b);
    GsPktClose_13f5b0(q);
    DrawListEndPrim_141a20(g);
}
