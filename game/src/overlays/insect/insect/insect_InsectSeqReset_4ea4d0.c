/* rgp:protos */
#define RGP_SELF_insect_InsectSeqReset_4ea4d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EA4D0 -- 88 bytes.  Tear-down: the optional handle at +0x00 is
 * released, the two arrays are reset and three state words are written. */

typedef struct Obj {
    s32 m00;                        /* +0x0000 */
    u8  pad04[0x190 - 0x04];
    s32 m190;                       /* +0x0190 */
    u8  pad194[0x1DC - 0x194];
    s32 m1DC;                       /* +0x01DC */
    s32 m1E0;                       /* +0x01E0 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectSeqReset_4ea4d0(Obj *o)
{
    if (o->m00 != 0) {
        MemStackHeapReinit_14de90(o->m00);
    }
    insect_InsectSeqStateHistClear_4ea460(o);
    insect_InsectSeqSubStateHistClear_4ea430(o);
    o->m190 = 0;
    o->m1DC = 2;
    o->m1E0 = 0;
}
