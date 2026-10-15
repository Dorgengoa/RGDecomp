#include "types.h"

extern void OperatorDeleteArray_100820(void *);
extern void OperatorDelete_100840(void *);

struct Rep_FUN_00102ab0 {
    s32 m00;
};

struct Obj_FUN_00102ab0 {
    void *m00;
    struct Rep_FUN_00102ab0 *m04;
};

void *SharedArrayPtrDtor_102ab0(struct Obj_FUN_00102ab0 *o, s16 flag)
{
    struct Rep_FUN_00102ab0 *r;

    if (o != 0) {
        r = o->m04;
        if (r != 0) {
            if (--r->m00 == 0) {
                OperatorDeleteArray_100820(o->m00);
                OperatorDelete_100840(o->m04);
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
