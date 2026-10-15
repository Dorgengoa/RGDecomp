#include "types.h"

/* Same TU as DrawListEmitFrameEnvMaybe_142280: the four-store packet block is the same
   `static inline` helper, D_0047DE40 is read with `lq %gp_rel` so it must be
   declared AT the small-data threshold, and the `e ? e+8 : 0` ternary comes
   out as a plain beqz/b pair because the 0x270 load fills the delay slot. */

typedef unsigned __int128 u128;

struct Node {
    u8 pad000[0x28];
    u8 *m28;   /* 0x28 */
    s32 m2C;   /* 0x2C */
};

struct Elem {
    s32 m00;
    u8 pad004[4];
    u8 m08[1];   /* retail RECOMPUTES `el + 8` at each use: a member address,
                    not a common subexpression in a local */
};

struct Cam {
    u8 pad000[0x160];
    f32 m160;
    f32 m164;
    f32 m168;
    f32 m16C;
};

struct Ctx {
    s32 m00;              /* 0x0000 */
    u128 *m04;            /* 0x0004 */
    void *m08[6];         /* 0x0008 */
    u8 pad020[0xB0];
    u8 mD0[0x1A0];        /* 0x00D0 */
    struct Cam *m270;     /* 0x0270 */
    u8 pad274[0xCA4];
    s32 m0F18;            /* 0x0F18 */
    u8 pad0F1C[0x2D24];
    s32 m3C40;            /* 0x3C40 */
    s32 m3C44;            /* 0x3C44 */
    s32 m3C48[0x20];      /* 0x3C48 */
    u8 pad3CC8[0x48];
    s32 m3D10;            /* 0x3D10 */
    s32 m3D14;
    s32 m3D18;
    s32 m3D1C;
    s32 m3D20;
};

extern u64 D_0047DE40;

extern void func_00436980(void);
extern void MemStackReset_14d830(void *a);
extern void MemStackAllocAligned64_14da10(void *a, s32 b);
extern void MemStackHeapReinit_14de90(void *a);
extern void DrawListClearScreen_1423c0(struct Ctx *a, s32 x, s32 y, s32 z, f32 w);
extern void *DrawEnvWritePacket_157460(void *a, void *b);
extern void MemStackAllocQw_14d950(void *a, void *b);
extern void DrawListEmitFrameEnvMaybe_142280(struct Ctx *a);

static inline void emit(struct Ctx *a, u32 addr)
{
    *a->m04 = *(u128 *)&D_0047DE40;
    ((u32 *)a->m04)[1] = addr;
    a->m04 = (u128 *)((u8 *)a->m04 + 0x10);
}

void DrawListFrameBegin_1425d0(struct Ctx *a, s32 flag)
{
    struct Elem *el;
    void *e;
    struct Node *nd;
    void *q;
    struct Cam *c;
    struct Cam *ctx;
    s32 i;

    if (a->m0F18 != 0) {
        return;
    }
    el = (struct Elem *)a->m08[a->m00];
    a->m04 = 0;
    if (el == 0) {
        return;
    }
    a->m0F18 = 1;
    a->m04 = (u128 *)el->m00;
    MemStackReset_14d830(el->m08);
    MemStackAllocAligned64_14da10(el->m08, 0x400);
    if (func_00436980 != 0) {
        emit(a, (u32)func_00436980 & 0x0FFFFFFF);
    }
    MemStackHeapReinit_14de90(&a->mD0);
    c = a->m270;
    if (flag != 0) {
        DrawListClearScreen_1423c0(a, (s32)c->m160, (s32)c->m168, (s32)c->m16C, c->m164);
    }
    a->m3C40 = 0;
    a->m3C44 = 0;
    for (i = 0; i < 0x20; i++) {
        a->m3C48[i] = 0;
    }
    ctx = a->m270;
    e = a->m08[a->m00];
    nd = e ? (struct Node *)((u8 *)e + 8) : 0;
    if (nd != 0) {
        q = nd->m28 + nd->m2C * 16;
        MemStackAllocQw_14d950(nd, DrawEnvWritePacket_157460(ctx, q));
        emit(a, (u32)q & 0x0FFFFFFF);
    }
    DrawListEmitFrameEnvMaybe_142280(a);
    /* the five clears come out in SOURCE order, high address first */
    a->m3D20 = 0;
    a->m3D1C = 0;
    a->m3D18 = 0;
    a->m3D14 = 0;
    a->m3D10 = 0;
}
