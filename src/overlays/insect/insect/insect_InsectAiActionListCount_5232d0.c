#include "types.h"
/* insect 0x5232D0 -- 8 B / 2 words.  `jr $31 / lw $2, 0x804($4)`:
 * a bare word accessor.  The load WIDTH (lw) fixes the member at s32. */

typedef struct Obj {
    u8  pad00[0x804];
    s32 m804;                 /* +0x804 */
} Obj;

s32 insect_InsectAiActionListCount_5232d0(Obj *o)
{
    return o->m804;
}
