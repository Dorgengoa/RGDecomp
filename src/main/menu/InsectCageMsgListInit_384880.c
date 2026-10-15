#include "types.h"

typedef struct Obj_FUN_00384880 {
    void *f00;
} Obj_FUN_00384880;

extern void *MemStackNew_14e1b0(s32 n);
extern void *ConstructNewArray_100710(void *m, s32 a, s32 b, s32 c, s32 d);
extern void InsectCageMsgListReset_384820(Obj_FUN_00384880 *o);

void InsectCageMsgListInit_384880(Obj_FUN_00384880 *o)
{
    o->f00 = ConstructNewArray_100710(MemStackNew_14e1b0(0x4210), 0, 0, 0x108, 0x40);
    InsectCageMsgListReset_384820(o);
}
