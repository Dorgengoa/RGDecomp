/* rgp:protos */
#define RGP_SELF_Get 1
#define RGP_SELF_ModelObjRemoveAttachById_1ae2b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s32 id;
    s32 idx;
} Slot;

typedef struct {
    u8 pad0[0x214];
    s32 count;
    u8 *base;
    u8 pad21C[0x228 - 0x21C];
    Slot a[4];
    Slot b[4];
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/

static inline u8 *Get(Obj *o, s32 idx) {
    if (o->base == NULL) {
        return NULL;
    }
    if (idx < 0 || idx >= o->count) {
        return NULL;
    }
    return o->base + idx * 0x50;
}

void ModelObjRemoveAttachById_1ae2b0(Obj *arg0, s32 arg1)
{
    s32 i;
    Slot *e;
    u8 *p;

    for (i = 0; i < 4; i++) {
        e = &arg0->a[i];
        if (e->id == arg1) {
            p = Get(arg0, e->idx);
            if (p != NULL) {
                ModelPartClear_152810(p);
            }
            e->idx = -1;
            e->id = -1;
        }
    }
    for (i = 0; i < 4; i++) {
        e = &arg0->b[i];
        if (e->id == arg1) {
            p = Get(arg0, e->idx);
            if (p != NULL) {
                ModelPartClear_152810(p);
            }
            e->idx = -1;
            e->id = -1;
        }
    }
    ModelObjTexAnimRemoveById_1ac610(arg0, arg1);
    MotionListRemoveById_1724c0((u8 *)arg0 + 0x1F0, arg1);
}
