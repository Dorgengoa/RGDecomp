#include "types.h"
/* insect 0x004EFD40 -- 56 bytes, 14 instructions. */

typedef struct Obj {
    void *f00;                      /* +0x00 */
    s32   f04;                      /* +0x04 */
} Obj;

extern void func_14DE90(void *p);

void insect_InsectCmdMenuClear_4efd40(Obj *o)
{
    if (o->f00 != 0) {
        func_14DE90(o->f00);
        o->f04 = 0;
    }
}
