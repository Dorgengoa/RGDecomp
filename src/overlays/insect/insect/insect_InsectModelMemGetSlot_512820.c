#include "types.h"
/* insect 0x00512820 -- 80 bytes, 20 instructions.  0x5C-byte slots at +0x64. */

typedef struct Ent {
    u8 pad00[0x5C];
} Ent;

typedef struct Obj {
    u8  pad00[0x64];
    Ent a[1];                       /* +0x64 */
} Obj;

extern s32 insect_InsectModelMemFindIndex_512870(Obj *o);

Ent *insect_InsectModelMemGetSlot_512820(Obj *o)
{
    s32 i;

    i = insect_InsectModelMemFindIndex_512870(o);
    if (i == -1) {
        return 0;
    }
    return &o->a[i];
}
