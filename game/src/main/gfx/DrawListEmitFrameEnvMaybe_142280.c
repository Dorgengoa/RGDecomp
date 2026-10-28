/* rgp:hwaccess */ #include "port/hwaccess.h"
#line 1
/* rgp:protos */
#define RGP_SELF_DrawListEmitFrameEnvMaybe_142280 1
#define RGP_SELF_emit 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The four-store block that appears twice is a `static inline` helper
   (mwcc's C mode honours static inline).  The dsll32/dsrl32 pair is the
   28-bit DMA address mask. */

typedef rg_u128 u128;

struct Node {
    u8 pad000[0x28];
    u8 *m28;   /* 0x28 */
    s32 m2C;   /* 0x2C */
};

struct Ctx {
    s32 m00;              /* 0x00 */
    u128 *m04;            /* 0x04 write pointer */
    void *m08[6];         /* 0x08 */
    u8 pad020[0x110];
    u8 m130[0x140];       /* 0x130 */
    void *m270;           /* 0x270 */
};

/* `lq %gp_rel(D_0047DE40)($28)`: declare it AT the small-data threshold or
   it leaves small data and costs a %hi/%lo pair. */
extern u64 D_0047DE40;

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

void DrawListEmitFrameEnvMaybe_142280(struct Ctx *a)
{
    void *e;
    void *sub;
    struct Node *nd;
    void *q;
    void *r;
    void *ctx;
    void *arg;

    ctx = a->m270;
    e = a->m08[a->m00];
    arg = e ? (void *)((u8 *)e + 8) : 0;
    GsPktInit_13f7f0(&a->m130, arg, ctx);
    GsPktBegin_13f7e0(&a->m130);
    sub = &a->m130;
    GsPktOpenPrim_13f730(sub, 6);
    GsPktSetTexa_13eca0(sub, 0x0000008000000080);
    GsPktClose_13f5b0(sub);
    r = GsPktEnd_13f790(sub);
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
