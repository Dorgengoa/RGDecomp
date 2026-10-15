#include "types.h"
/* insect 0x512010 -- 16 B / 4 words.  `lw 0x28($4)` / `xori $2,$2,0x3` /
 * `sltiu $2,$2,1` is mwcc's `== <non-zero constant>`: the xori clears to zero on
 * equality and the sltiu turns that into a 0/1. */

typedef struct Obj {
    u8  pad00[0x28];
    s32 m28;                 /* +0x28 */
} Obj;

s32 insect_InsectFileSlotIsLoaded_512010(Obj *o)
{
    return o->m28 == 3;
}
