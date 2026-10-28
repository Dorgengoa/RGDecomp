/* rgp:protos */
#define RGP_SELF_insect_InsectSeqSetState_4ea3c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EA3C0 -- 100 bytes.  A four-entry queue at +0x04: the first free
 * (-1) slot takes the value, otherwise the queue shifts down one and the value
 * goes in the last slot.  The first loop STORES through a materialised pointer
 * (`addu $3,$4,$3` then `addiu $7,$3,0x4`), which is the left-associative
 * pointer sum of ixa07 lever 2; the second loop is plain array indexing and
 * addresses both cells off one base with displacements 0x4 / 0x8. */

typedef struct Obj {
    s32 m00;                        /* +0x00 */
    s32 m04[4];                     /* +0x04 */
    u8  pad14[0x24 - 0x14];
    s32 m24;                        /* +0x24 */
} Obj;

void insect_InsectSeqSetState_4ea3c0(Obj *o, s32 v)
{
    s32 i;
    s32 *p;

    o->m24 = v;
    for (i = 0; i < 4; i++) {
        p = (s32 *)o + i + 1;
        if (*p == -1) {
            *p = v;
            return;
        }
    }
    for (i = 0; i < 3; i++) {
        o->m04[i] = o->m04[i + 1];
    }
    o->m04[3] = v;
}
