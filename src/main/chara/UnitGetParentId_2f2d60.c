#include "types.h"

typedef struct Sub_func_002F2D60 {
    u8 pad000[0xC];
    s32 val;
} Sub_func_002F2D60;

typedef struct Obj_func_002F2D60 {
    u8 pad000[0x3E0];
    Sub_func_002F2D60 *p;
} Obj_func_002F2D60;

s32 UnitGetParentId_2f2d60(Obj_func_002F2D60 *o)
{
    Sub_func_002F2D60 *p;

    p = o->p;
    if (p != 0) {
        return p->val;
    }
    return -1;
}
