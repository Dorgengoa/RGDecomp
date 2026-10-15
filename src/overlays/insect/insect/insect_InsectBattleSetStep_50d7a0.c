#include "types.h"
/* insect 0x0050D7A0 -- 216 bytes, 54 instructions, 1 call.
 * An 8-entry per-row queue at +0x5E34: append into the first free slot,
 * otherwise shift the row down by one and append at the end.
 */

typedef struct Obj {
    u8 pad00[0x5E34];
    s8 f5E34[64][8];                /* +0x5E34 */
} Obj;

extern s32 insect_InsectBattleGetStep_50d6a0(Obj *o, s32 idx);

void insect_InsectBattleSetStep_50d7a0(Obj *o, s32 v, s32 idx, s32 flag)
{
    s32 found;
    s32 i;
    s32 j;

    found = 0;
    if (v == -2) {
        flag = 0;
    }
    if (v == -1) {
        return;
    }
    if (flag != -1) {
        v = insect_InsectBattleGetStep_50d6a0(o, idx) + 1;
    }
    for (i = 0; i < 8; i++) {
        if (o->f5E34[idx][i] == -1) {
            found = 1;
            o->f5E34[idx][i] = v;
            break;
        }
    }
    if (found == 0) {
        for (j = 0; j < 7; j++) {
            o->f5E34[idx][j] = o->f5E34[idx][j + 1];
        }
        o->f5E34[idx][7] = v;
    }
}
