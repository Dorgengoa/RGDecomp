#include "types.h"
/* insect 0x00514740 -- 80 bytes.  The same 0x20-byte element array at +0xE8
 * that insect_InsectPieceMotionQueueClear_514320 walks, preceded by one bare call. */

typedef struct Slot {
    u8 pad00[0x20];
} Slot;

typedef struct Obj {
    u8   pad000[0xE8];
    Slot f0E8[8];                   /* +0x00E8 */
} Obj;

extern void insect_InsectPieceResetState_516620(void);
extern void insect_InsectPieceMotionSlotClear_514810(Slot *s);

void insect_InsectPieceReset_514740(Obj *o)
{
    s32 i;

    insect_InsectPieceResetState_516620();
    for (i = 0; i < 8; i++) {
        insect_InsectPieceMotionSlotClear_514810(&o->f0E8[i]);
    }
}
