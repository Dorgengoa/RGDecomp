/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_DrawListClearScreen_1423c0 1
#define RGP_SELF_emit 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same TU as DrawListEmitFrameEnvMaybe_142280 / DrawListFrameBegin_1425d0: same `static inline` packet
   helper, same `lq %gp_rel(D_0047DE40)` (so the global must be declared AT
   the small-data threshold), same `e ? e + 8 : 0` slot adjust.
   GsPktSetRGBAQ_13ee40 takes FIVE integer arguments -- $8 is the fifth; the float
   parameter arrives in $f12 (independent FPR pool) and is saved in $f20
   because it has to live across the call run. */

typedef rg_u128 u128;

struct Node {
    u8 pad000[0x28];
    u8 *m28;   /* 0x28 */
    s32 m2C;   /* 0x2C */
};

struct Cfg {
    s32 m00;
    s32 m04;   /* 0x04 loop bound */
    s32 m08;   /* 0x08 */
};

struct Ctx {
    s32 m00;              /* 0x00 */
    u128 *m04;            /* 0x04 */
    void *m08[6];         /* 0x08 */
    u8 pad020[0x110];
    u8 m130[0x140];       /* 0x130 */
    struct Cfg *m270;     /* 0x270 */
};

extern u64 D_0047DE40;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

static inline void emit(struct Ctx *a, u32 addr)
{
    *a->m04 = *(u128 *)&D_0047DE40;
    ((u32 *)a->m04)[1] = addr;
    a->m04 = (u128 *)((u8 *)a->m04 + 0x10);
}

void DrawListClearScreen_1423c0(struct Ctx *a, s32 p1, s32 p2, s32 p3, f32 fv)
{
    void *e;
    void *sub;
    struct Node *nd;
    void *q;
    void *r;
    struct Cfg *ctx;
    struct Cfg *cfg;
    s32 step;
    s32 bound;
    s32 i;

    ctx = a->m270;
    e = a->m08[a->m00];
    GsPktInit_13f7f0(&a->m130, e ? (void *)((u8 *)e + 8) : 0, ctx);
    GsPktBegin_13f7e0(&a->m130);
    cfg = a->m270;
    sub = &a->m130;
    step = cfg->m08;
    bound = cfg->m04;
    GsPktEnableZTest_13e460(sub, 0);
    GsPktSetZTest_13e450(sub, 0);
    GsPktSetTextured_13e400(sub, 0);
    GsPktSetAlphaBlend_13e500(sub, 0);
    GsPktSetZWriteMask_13e430(sub, 0);
    GsPktOpenPrim_13f730(sub, 6);
    GsPktSetRGBAQ_13ee40(sub, p1, (s32)fv, p2, p3);
    for (i = 0; i < bound; i += 0x20) {
        GsPktSetXYZPixel_13f110(sub, i, 0, 0);
        GsPktSetXYZPixel_13f110(sub, i + 0x20, step, 0);
    }
    GsPktClose_13f5b0(sub);
    r = GsPktEnd_13f790(&a->m130);
    if (r != 0) {
        emit(a, ((u32)r));
    }
    ctx = a->m270;
    e = a->m08[a->m00];
    nd = e ? (struct Node *)((u8 *)e + 8) : 0;
    if (nd != 0) {
        q = nd->m28 + nd->m2C * 16;
        MemStackAllocQw_14d950(nd, DrawEnvWritePacket_157460(ctx, q));
        emit(a, ((u32)q));
    }
}
