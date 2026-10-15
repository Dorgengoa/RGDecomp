#include "types.h"
/* insect 0x4E9F70 -- 16 B / 4 words.  `lw 0x1DC($4)` / `xori $2,$2,0x2` /
 * `sltiu $2,$2,1` is mwcc's `== <non-zero constant>`: the xori clears to zero on
 * equality and the sltiu turns that into a 0/1. */

typedef struct Obj {
    u8  pad00[0x1DC];
    s32 m1DC;                 /* +0x1DC */
} Obj;

s32 insect_InsectSeqIsLoadDone_4e9f70(Obj *o)
{
    return o->m1DC == 2;
}
