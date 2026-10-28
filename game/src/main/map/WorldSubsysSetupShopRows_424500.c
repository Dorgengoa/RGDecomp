/* rgp:protos */
#define RGP_SELF_WorldSubsysSetupShopRows_424500 1
#define RGP_SELF_get 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent { u8 pad0[0xA]; s16 unkA; u8 padC[4]; } Ent;
typedef struct Tbl { u8 pad0[0x7C]; s16 count; u8 pad7e[0x8C - 0x7C - sizeof(s16)]; Ent *arr; } Tbl;
typedef struct Obj { u8 pad0[4]; s32 heap; u8 pad8[4]; Tbl *tbl; s16 total; u8 pad12[2]; s32 unk14; } Obj;

/*rgp*/
/*rgp*/
/*rgp*/

static inline Ent *get(Tbl *t, s32 i)
{
    return (i >= 0 && i < t->count) ? &t->arr[i] : 0;
}

s32 WorldSubsysSetupShopRows_424500(Obj *o)
{
    s32 i;
    s32 n;
    s32 t;
    Ent *e;
    o->total = 0;
    n = o->tbl->count;
    for (i = 0; i < n; i++) {
        e = get(o->tbl, i);
        if (e) {
            o->total += e->unkA;
        }
    }
    t = o->total;
    o->unk14 = ((s32)ConstructNewArray_100710(((s32)MemStackNew_14e0b0(t * 0xC + 0x10, o->heap)), ShopRowCtor_4245e0, 0, 0xC, t));
    return 1;
}
