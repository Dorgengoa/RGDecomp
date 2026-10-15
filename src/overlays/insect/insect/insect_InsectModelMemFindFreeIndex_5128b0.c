#include "types.h"
/* insect 0x005128B0 -- 15 instructions.  Linear scan of a 28-entry s16 table
 * for the first free (-1) slot; the `bnel` past the body is the if/else shape
 * of insect-dispatch-branch-polarity. */

typedef struct Obj {
    u8 pad00[0x400];
    s16 m400[28];                   /* +0x400 */
} Obj;

s32 insect_InsectModelMemFindFreeIndex_5128b0(Obj *o)
{
    s32 i;

    for (i = 0; i < 28; i++) {
        if (o->m400[i] == -1) {
            return i;
        }
    }
    return -1;
}
