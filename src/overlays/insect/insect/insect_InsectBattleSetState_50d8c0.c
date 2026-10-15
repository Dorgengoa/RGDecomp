#include "types.h"
/* insect 0x0050D8C0 -- 248 bytes.  An 8-slot per-row history ring: fill the
 * first free (-1) slot, otherwise shift the row down one and append. */

typedef struct Own {
    u8 pad0000[0x5DD4];
    s8 f5DD4[8][8];                 /* +0x5DD4 */
} Own;

extern s32  insect_InsectBattleGetState_50d6f0(Own *o, s32 r);
extern void insect_InsectBattleSetStep_50d7a0(Own *o, s32 a, s32 r, s32 b);

void insect_InsectBattleSetState_50d8c0(Own *o, s32 v, s32 r, s32 d)
{
    s32 found;
    s32 i;
    s32 j;

    found = 0;
    if (v == -2) {
        d = 0;
    }
    if (v == -1) {
        return;
    }
    if (d != -1) {
        v = insect_InsectBattleGetState_50d6f0(o, r) + 1;
    }
    for (i = 0; i < 8; i++) {
        if (o->f5DD4[r][i] == -1) {
            found = 1;
            o->f5DD4[r][i] = v;
            break;
        }
    }
    if (found == 0) {
        for (j = 0; j < 7; j++) {
            o->f5DD4[r][j] = o->f5DD4[r][j + 1];
        }
        o->f5DD4[r][7] = v;
    }
    if (r < 6) {
        insect_InsectBattleSetStep_50d7a0(o, 1, r, -1);
    }
}
