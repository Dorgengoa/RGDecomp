#include "types.h"

extern void OperatorDelete_100840(void *);

struct Obj_FUN_001a1380 {
    u8 pad000[0x8];
    void *m08;
};

void *BufHolderDtor_1a1380(struct Obj_FUN_001a1380 *o, s16 flag)
{
    if (o != 0) {
        if (o != 0) {
            if (o != 0) {
                if (o->m08 != 0) {
                    OperatorDelete_100840(o->m08);
                }
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
