/* rgp:protos */
#define RGP_SELF_GetEnt 1
#define RGP_SELF_RowRangeIterInit_428750 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[2];
    s16 h2;
    u8 pad4[4];
    s16 hA;
    u8 padC[6];
    s32 w20;
    u8 pad24[0xC];
} Ent;

typedef struct {
    u8 pad0[0x7C];
    s16 count;
    u8 pad7E[0xE];
    Ent *ents;
} Obj;

typedef struct {
    u8 pad0[4];
    Obj *obj;
    s16 first;
    s16 last;
} Self;

/*rgp*/
/*rgp*/

static inline Ent *GetEnt(Obj *o, s32 i)
{
    Ent *e;
    if (i >= 0) {
        if (!(i < o->count)) {
            e = NULL;
        } else {
            e = &o->ents[i];
        }
    } else {
        e = NULL;
    }
    return e;
}

void RowRangeIterInit_428750(Self *self, Obj *obj, s32 arg5, s32 arg6)
{
    s32 cnt;
    s32 lo;
    s32 hi;
    s32 i;
    Ent *e;

    self->first = -1;
    self->last = -1;
    self->obj = obj;
    if (obj == NULL) {
        return;
    }
    cnt = obj->count;
    lo = -1;
    hi = -1;
    RowRangeLookup_428a10(self->obj,arg5,arg6,&lo,&hi);
    i = lo;
    if (i < 0) {
        return;
    }
    if (hi < 0) {
        return;
    }
    if (i > hi || hi > cnt - 1) {
        return;
    }
    for (; i <= hi; i++) {
        e = GetEnt(self->obj, i);
        if (ByteKeyCompare_428a70(e->hA, e->w20, arg5, arg6) == 0) {
            if (self->first < 0) {
                self->first = i;
            }
            self->last = i;
        } else if (self->last >= 0) {
            break;
        }
    }
}
