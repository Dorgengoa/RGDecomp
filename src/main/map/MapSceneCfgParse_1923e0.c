#include "types.h"

typedef struct S001923e0 {
    s32 n0;
    s32 a[16];
    s32 n44;
    s32 b[16];
    void *p88;
    u32 x8C;
    u8 pad90[0xC];
    s32 x9C;
    s32 xA0;
} S001923e0;

typedef struct Ctx {
    u8 d[0xED0];
} Ctx;

extern s32 ConstructNewArray_100710(s32 arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern void *MemStackAllocQw_14d950(s32 arg0, u32 arg1);
extern s32 MemStackNew_14e1b0(s32 arg0, s32 arg1);
extern void TextReaderCtor_15f140(Ctx *arg0);
extern void TextReaderOpen_15f1b0(Ctx *arg0, void *arg1, u32 arg2);
extern void BuildKeywordHashTable_15f270(Ctx *arg0, void *arg1);
extern void TextReaderParseAll_15f3f0(Ctx *arg0);
extern void *memcpy(void *dst, const void *src, u32 n);
extern u8 D_0044A880[0x400];
extern s32 D_004812F4;
extern s32 D_004812F8;
extern s32 D_004812FC;
extern s32 D_00481300;
extern s32 D_00481304;
extern s32 D_00481308;
extern void MapLightSetCtor_1923a0(void);

#pragma opt_propagation off
void MapSceneCfgParse_1923e0(S001923e0 *arg0, void *arg1, u32 arg2, s32 arg3, s32 arg4)
{
    Ctx ctx;
    s32 i;
    s32 k;
    s32 t;
    u16 m;
    u32 n;

    D_00481308 = -1;
    D_004812F8 = arg3;
    D_004812FC = 0;
    D_004812F4 = (s32)arg0;
    D_00481300 = 0;
    D_00481304 = 0;
    TextReaderCtor_15f140(&ctx);
    BuildKeywordHashTable_15f270(&ctx, D_0044A880);
    TextReaderOpen_15f1b0(&ctx, arg1, arg2);
    arg0->n0 = 16;
    for (i = 0; i < arg0->n0; i++) {
        arg0->a[i] = 0;
    }
    arg0->n44 = 16;
    for (i = 0; i < arg0->n0; i++) {
        arg0->b[i] = 0;
    }
    if (arg4 != 0) {
        if (arg2 & 0xF) {
            n = (arg2 >> 4) + 1;
        } else {
            n = arg2 >> 4;
        }
        arg0->p88 = MemStackAllocQw_14d950(arg3, n);
        memcpy(arg0->p88, arg1, arg2);
    } else {
        arg0->p88 = arg1;
    }
    k = 16;
    m = 0x80;
    arg0->x8C = arg2;
    arg0->x9C = k;
    t = (m - k) * 4;
    t = t + k;
    arg0->xA0 = ConstructNewArray_100710(MemStackNew_14e1b0(t * 16 + 16, arg3), MapLightSetCtor_1923a0, 0, 0x1D0, k);
    TextReaderOpen_15f1b0(&ctx, arg1, arg2);
    TextReaderParseAll_15f3f0(&ctx);
    arg0->n44 = D_00481300;
}
