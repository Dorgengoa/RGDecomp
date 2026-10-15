#include "types.h"
/* insect 0x005232E0 -- 76 bytes, 19 instructions.  A free-slot scan over a
 * 0x200-entry s32 table at +0x4 with a count at +0x804 (= 4 + 0x200*4). */

typedef struct Obj {
    u8  pad00[0x4];
    s32 m04[0x200];                 /* +0x004 */
    s32 m804;                       /* +0x804 */
} Obj;

void insect_InsectAiActionListAdd_5232e0(Obj *o, s32 v)
{
    s32 i;

    if (v == 0) {
        return;
    }
    for (i = 0; i < 0x200; i++) {
        if (o->m04[i] == 0) {
            o->m04[i] = v;
            o->m804 = o->m804 + 1;
            return;
        }
    }
}
