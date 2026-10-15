#include "types.h"

extern const u8 D_00471380[];
extern const u8 D_00471390[];
extern void DListClear_42ea80(void *);
extern void OperatorDelete_100840(void *);

struct Obj_FUN_00201ac0 {
    u8 pad000[0xC];
    const u8 *m0C;
    u8 pad010[0xC];
    const u8 *m1C;
};

void *MapSequencerDtor_201ac0(struct Obj_FUN_00201ac0 *o, s16 flag)
{
    if (o != 0) {
        if ((u8 *)o + 0x10 != 0) {
            o->m1C = D_00471380;
            DListClear_42ea80((u8 *)o + 0x10);
            if ((void *)((s32)o + 0x10) != 0) {
                DListClear_42ea80((void *)((s32)o + 0x10));
            }
        }
        if (o != 0) {
            o->m0C = D_00471390;
            DListClear_42ea80(o);
            if (o != 0) {
                DListClear_42ea80(o);
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
