/* rgp:protos */
#define RGP_SELF_EffDefCmdObjScl_19e8f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef rg_u128 u128;

/* One translation unit's worth of state-machine constructors.  Every member of
   the family shares the same 7-arm switch over ctx->state (jump table base 0,
   case 0 falling to the switch exit) and the same allocate-then-init arm body.
   The `beql` with the store in its delay slot is mwcc duplicating the join
   block's `c->obj = p` -- one source store, two emitted. */

typedef struct Ctx {
    u8   pad00[0x20];
    s32  f20;                   /* 0x20 heap/owner passed to the allocator   */
    u8   pad24[0x1C];
    s32  state;                 /* 0x40 */
    u8  *obj;                   /* 0x44 */
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EffDefCmdObjScl_19e8f0(s32 a0, s32 a1, Ctx **pp)
{
    u128 v;
    u8 *p;
    u8 *obj;
    Ctx *c;

    c = *pp;
    c->state = 3;
    VariantReadVec3_15f6c0(&v, a0);
    if (c->obj != 0) {
        obj = c->obj;
    } else {
        switch (c->state) {
        case 1:
            p = ((u8 *)MemStackNew_14e230(0x40, c->f20));
            if (p != 0) {
                p = ((u8 *)EffectParamCtorPos_19da60(p));
            }
            c->obj = p;
            break;
        case 2:
            p = ((u8 *)MemStackNew_14e230(0x40, c->f20));
            if (p != 0) {
                p = ((u8 *)EffectParamCtorRot_19da10(p));
            }
            c->obj = p;
            break;
        case 3:
            p = ((u8 *)MemStackNew_14e230(0x40, c->f20));
            if (p != 0) {
                p = ((u8 *)EffectParamCtorScl_19d9c0(p));
            }
            c->obj = p;
            break;
        case 4:
            p = ((u8 *)MemStackNew_14e230(0x40, c->f20));
            if (p != 0) {
                p = ((u8 *)EffectParamCtorCol_19d950(p));
            }
            c->obj = p;
            break;
        case 5:
            p = ((u8 *)MemStackNew_14e230(0x40, c->f20));
            if (p != 0) {
                p = ((u8 *)EffectParamCtorAlpha_19d900(p));
            }
            c->obj = p;
            break;
        case 6:
            p = ((u8 *)MemStackNew_14e230(0x40, c->f20));
            if (p != 0) {
                p = ((u8 *)EffectParamCtorTexUv_19d8b0(p));
            }
            c->obj = p;
            break;
        case 7:
            p = ((u8 *)MemStackNew_14e230(0x40, c->f20));
            if (p != 0) {
                p = ((u8 *)EffectParamCtorRgba_19d840(p));
            }
            c->obj = p;
            break;
        }
        obj = c->obj;
    }
    /* Retail stores the staged qword UNCONDITIONALLY -- the `sq` sits in the
       `bnez`'s delay slot, which only happens when the store is not guarded.
       The null test after it is what picks the return value. */
    *(u128 *)(obj + 0x20) = v;
    if (obj == 0) {
        return 0;
    }
    return 1;
}
