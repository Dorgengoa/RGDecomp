/* rgp:protos */
#define RGP_SELF_insect_InsectSeqInit_4ea550 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004EA550 -- 64 B / 16 words.
 * `sw $0, 0x0($4)` uses the INCOMING argument register, before
 * `daddu $16, $4, $0` lands in the first jal's delay slot -- so the clear is
 * the first statement and the ctor calls follow.  Both callees are one-arg
 * (the $4-in-place / copy-to-$16 shape). */

typedef struct Obj {
    s32 m00;                    /* +0x00 */
    u8  pad04[0x190 - 0x04];
    s32 m190;                   /* +0x190 */
    u8  pad194[0x1DC - 0x194];
    s32 m1DC;                   /* +0x1DC */
    s32 m1E0;                   /* +0x1E0 */
} Obj;

/*rgp*/
/*rgp*/

void insect_InsectSeqInit_4ea550(Obj *o)
{
    o->m00 = 0;
    insect_InsectSeqStateHistClear_4ea460(o);
    insect_InsectSeqSubStateHistClear_4ea430(o);
    o->m190 = 0;
    o->m1DC = 2;
    o->m1E0 = 0;
}
