#include "types.h"
/* insect 0x004EA490 -- 60 bytes.  The back edge is an unconditional `b` with
 * the test at the TOP, i.e. a `for (;;)` with an explicit `break`, not a
 * `while` (which mwcc lays out test-at-bottom with an entry branch). */

typedef struct Ent {
    s32 f00;                        /* +0x00 */
    u8  pad04[0x18 - 0x04];
} Ent;

typedef struct Obj {
    u8   pad000[0x18C];
    Ent *f18C;                      /* +0x18C */
    u8   pad190[0x194 - 0x190];
    s32  f194;                      /* +0x194 */
} Obj;

void insect_InsectSeqSetHandlerTable_4ea490(Obj *o, Ent *e)
{
    if (e != 0) {
        o->f18C = e;
        o->f194 = 0;
        for (;;) {
            if (e->f00 == -1) {
                break;
            }
            e++;
            o->f194++;
        }
    }
}
