/* rgp:protos */
#define RGP_SELF_insect_InsectSeqFindHandler_4ea010 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EA010 -- 18 instructions.  A linear search over a 0x18-byte
 * record array; the cursor only advances on the non-matching path, which is
 * why the `beql` null test skips straight to the loop increment. */

typedef struct Entry {
    s32 m00;                        /* +0x00 */
    u8 pad04[0x18 - 0x04];
} Entry;

typedef struct Obj {
    u8 pad00[0x18C];
    Entry *m18C;                    /* +0x18C */
    Entry *m190;                    /* +0x190 */
    s32 m194;                       /* +0x194 */
} Obj;

void insect_InsectSeqFindHandler_4ea010(Obj *o, s32 key)
{
    Entry *e;
    s32 n;
    s32 i;

    o->m190 = 0;
    e = o->m18C;
    n = o->m194;
    for (i = 0; i < n; i++) {
        if (e != 0) {
            if (e->m00 == key) {
                o->m190 = e;
                return;
            }
            e++;
        }
    }
}
