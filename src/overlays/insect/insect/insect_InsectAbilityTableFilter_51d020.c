#include "types.h"
/* insect 0x0051D020 -- 136 bytes, 34 instructions, no calls.
 * Collect matching 0x80-byte entries into a caller-supplied array.
 * Fifth integer parameter arrives in $8 under the PS2 EABI.
 */

typedef struct Ent {
    u8  pad00[0x60];
    s8  f60;                        /* +0x60 */
    s8  f61;                        /* +0x61 */
    u8  pad62[0x70 - 0x62];
    u8  f70;                        /* +0x70 */
    u8  pad71[0x80 - 0x71];
} Ent;

typedef struct Obj {
    u8   pad00[0x58];
    Ent *f58;                       /* +0x58 */
    u8   pad5C[4];
    s32  f60;                       /* +0x60 */
} Obj;

s32 insect_InsectAbilityTableFilter_51d020(Obj *o, s32 kind, s32 bit, s32 lim, Ent **out)
{
    Ent *e;
    s32 cnt;
    s32 n;
    s32 i;
    s32 mask;

    if (out == 0) {
        return 0;
    }
    cnt = o->f60;
    n = 0;
    i = 0;
    mask = 1 << bit;
    for (; i < cnt; i++) {
        e = &o->f58[i];
        if (e == 0) {
            continue;
        }
        if (kind == e->f60 && (mask & e->f70) != 0 && e->f61 <= lim) {
            out[n] = e;
            n++;
        }
    }
    return n;
}
