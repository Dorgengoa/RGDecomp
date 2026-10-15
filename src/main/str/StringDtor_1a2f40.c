#include "types.h"

extern void OperatorDelete_100840(void *);

struct Obj_FUN_001a2f40 {
    s32 m00;
    u8 pad004[0x4];
    void *m08;
};

void *StringDtor_1a2f40(struct Obj_FUN_001a2f40 *o, s16 flag)
{
    if (o != 0) {
        if (o != 0) {
            if ((o->m00 & 1) != 0) {
                OperatorDelete_100840(o->m08);
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
