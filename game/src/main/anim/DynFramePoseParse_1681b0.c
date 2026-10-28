/* rgp:protos */
#define RGP_SELF_DynFramePoseParse_1681b0 1
#define RGP_SELF_getEnt1681b0 1
#define RGP_SELF_valid1681b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E1681b0 {
    s32 w0;
    s32 w4;
    s32 *p8;
} E1681b0;

typedef struct G1681b0 {
    u8 pad0[0x90];
    s32 w90;
    s32 w94;
    u8 *p98;
    s32 w9C;
    s32 wA0;
} G1681b0;

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(s32, void *);
extern u8 D_00459090[];
extern u8 D_00459098[];
extern u8 D_004590A0[];
extern u8 D_004590A8[];
extern u8 D_004590B0[];
extern G1681b0 *D_00481154;
extern s32 D_00481158;

static inline E1681b0 *getEnt1681b0(s32 i)
{
    G1681b0 *g = D_00481154;
    E1681b0 *e;

    if (i < 0 || i >= g->w90) {
        e = 0;
    } else {
        e = (E1681b0 *)(g->p98 + i * 0x50);
    }
    return e;
}

static inline s32 valid1681b0(s32 x)
{
    G1681b0 *g = D_00481154;

    if (x < 0 || x >= g->wA0) {
        return 0;
    }
    return 1;
}

E1681b0 *DynFramePoseParse_1681b0(s64 *args, s32 argc)
{
    E1681b0 *e;
    s32 name;
    s32 i;

    e = getEnt1681b0(VariantGetInt_15f780((s32)args++));
    name = SlotGetInt_15f720((s32)args++);
    if (e == 0 || name == 0) {
        return 0;
    }
    e->w0 = 0;
    if (strcmp(name, D_00459090) == 0) {
        if (argc < 6) {
            return 0;
        }
        e->w0 = 1;
        e->w4 = 4;
    } else if (strcmp(name, D_00459098) == 0) {
        if (argc < 6) {
            return 0;
        }
        e->w0 = 5;
        e->w4 = 4;
    } else if (strcmp(name, D_004590A0) == 0) {
        if (argc < 6) {
            return 0;
        }
        e->w0 = 2;
        e->w4 = 4;
    } else if (strcmp(name, D_004590A8) == 0) {
        if (argc < 6) {
            return 0;
        }
        e->w0 = 6;
        e->w4 = 4;
    } else if (strcmp(name, D_004590B0) == 0) {
        if (argc < 6) {
            return 0;
        }
        e->w0 = 3;
        e->w4 = 4;
    } else {
        return 0;
    }
    e->p8 = ((s32 *)MemStackAllocQw_14d950(D_00481158, 1));
    for (i = 0; i < e->w4; i++) {
        e->p8[i] = VariantGetInt_15f780((s32)args++);
        if (!valid1681b0(e->p8[i])) {
            e->w0 = 0;
            return 0;
        }
    }
    return e;
}
