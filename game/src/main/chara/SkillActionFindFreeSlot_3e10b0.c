/* rgp:protos */
#define RGP_SELF_SkillActionFindFreeSlot_3e10b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern u8 D_004E9770[0x400];

s32 SkillActionFindFreeSlot_3e10b0(void)
{
    s32 r;
    s32 bv;
    s32 i;
    u8 *e;

    r = -1;
    bv = -1;
    for (i = 0; i < 2; i++) {
        e = D_004E9770 + i * 0x48;
        if (*(s16 *)e >= 0 && !(*(u8 *)(e + 0x40) & 1)) {
            if (bv == -1 || *(s16 *)(e + 0x28) < bv) {
                bv = *(s16 *)(e + 0x28);
                r = i;
            }
        } else {
            r = i;
            break;
        }
    }
    return r;
}
