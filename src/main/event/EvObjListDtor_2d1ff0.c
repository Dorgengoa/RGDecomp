#include "types.h"

extern const u8 D_00471518[];
extern const u8 D_00471528[];
extern const u8 D_00471538[];
extern void DListClear_42ea80(void *);
extern void OperatorDelete_100840(void *);

struct Obj_FUN_002d1ff0 {
    u8 pad000[0xC];
    const u8 *m0C;
};

void *EvObjListDtor_2d1ff0(struct Obj_FUN_002d1ff0 *o, s16 flag)
{
    if (o != 0) {
        o->m0C = D_00471538;
        DListClear_42ea80(o);
        if (o != 0) {
            o->m0C = D_00471528;
            DListClear_42ea80(o);
            if (o != 0) {
                o->m0C = D_00471518;
                DListClear_42ea80(o);
                if (o != 0) {
                    DListClear_42ea80(o);
                }
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
