#include "types.h"

typedef unsigned __int128 u128;

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

extern u8 *MemStackNew_14e230(s32 size, s32 owner);
extern u8 *EffectParamCtorPos_19da60(u8 *p);
extern u8 *EffectParamCtorRot_19da10(u8 *p);
extern u8 *EffectParamCtorScl_19d9c0(u8 *p);
extern u8 *EffectParamCtorCol_19d950(u8 *p);
extern u8 *EffectParamCtorAlpha_19d900(u8 *p);
extern u8 *EffectParamCtorTexUv_19d8b0(u8 *p);
extern u8 *EffectParamCtorRgba_19d840(u8 *p);
extern void VariantReadVec3_15f6c0(void *dst, s32 src);

s32 EffDefCmdObjPos_19ed70(s32 a0, s32 a1, Ctx **pp)
{
    u128 v;
    u8 *p;
    u8 *obj;
    Ctx *c;

    c = *pp;
    c->state = 1;
    VariantReadVec3_15f6c0(&v, a0);
    if (c->obj != 0) {
        obj = c->obj;
    } else {
        switch (c->state) {
        case 1:
            p = MemStackNew_14e230(0x40, c->f20);
            if (p != 0) {
                p = EffectParamCtorPos_19da60(p);
            }
            c->obj = p;
            break;
        case 2:
            p = MemStackNew_14e230(0x40, c->f20);
            if (p != 0) {
                p = EffectParamCtorRot_19da10(p);
            }
            c->obj = p;
            break;
        case 3:
            p = MemStackNew_14e230(0x40, c->f20);
            if (p != 0) {
                p = EffectParamCtorScl_19d9c0(p);
            }
            c->obj = p;
            break;
        case 4:
            p = MemStackNew_14e230(0x40, c->f20);
            if (p != 0) {
                p = EffectParamCtorCol_19d950(p);
            }
            c->obj = p;
            break;
        case 5:
            p = MemStackNew_14e230(0x40, c->f20);
            if (p != 0) {
                p = EffectParamCtorAlpha_19d900(p);
            }
            c->obj = p;
            break;
        case 6:
            p = MemStackNew_14e230(0x40, c->f20);
            if (p != 0) {
                p = EffectParamCtorTexUv_19d8b0(p);
            }
            c->obj = p;
            break;
        case 7:
            p = MemStackNew_14e230(0x40, c->f20);
            if (p != 0) {
                p = EffectParamCtorRgba_19d840(p);
            }
            c->obj = p;
            break;
        }
        obj = c->obj;
    }
    if (obj == 0) {
        return 0;
    }
    *(u128 *)(obj + 0x20) = v;
    return 1;
}
