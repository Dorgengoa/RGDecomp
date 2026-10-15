#include "types.h"
/* insect 0x0050DB00 -- 40 bytes, 10 instructions.  sd $0 = an s64 element. */

typedef struct Obj {
    u8  pad00[0x5DB8];
    s64 a[3];                       /* +0x5DB8 */
} Obj;

void insect_InsectBattleClearFlags_50db00(Obj *o)
{
    s32 i;

    for (i = 0; i < 3; i++) {
        o->a[i] = 0;
    }
}
