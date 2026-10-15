#include "types.h"
typedef struct A3D45D0 {
    u8  pad000[0x16];
    u16 lo : 7;
    u16 f  : 5;
    u16 hi : 4;
} A3D45D0;
typedef struct P3D45D0 { u8 pad000[0x10]; A3D45D0 *m10; } P3D45D0;
s32 ItemGetInsectFoodId_3d45d0(P3D45D0 *p)
{
    A3D45D0 *q;

    /* `beql $2,$0,<exit>` with the zero in the likely slot is the NESTED
       form: payload in the THEN, one `return 0` at the bottom. */
    q = p->m10;
    if (q != 0) {
        return q->f;
    }
    return 0;
}
