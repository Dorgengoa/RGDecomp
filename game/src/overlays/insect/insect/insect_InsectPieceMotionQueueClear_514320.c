/* rgp:protos */
#define RGP_SELF_insect_InsectPieceMotionQueueClear_514320 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00514320 -- 76 bytes, 19 instructions.  `sll 5` + `addiu 0xE8` is an
 * array of 0x20-byte elements based at +0xE8; the element ADDRESS is handed to
 * the callee, so the `addiu` is the member offset and not a hoisted base. */

typedef struct Slot {
    u8 pad00[0x20];
} Slot;

typedef struct Obj {
    u8   pad000[0xE8];
    Slot f0E8[8];                   /* +0x00E8 */
} Obj;

/*rgp*/

void insect_InsectPieceMotionQueueClear_514320(Obj *o)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        insect_InsectPieceMotionSlotClear_514810(&o->f0E8[i]);
    }
}
