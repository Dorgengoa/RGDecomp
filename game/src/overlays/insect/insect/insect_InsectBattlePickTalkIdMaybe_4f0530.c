/* rgp:protos */
#define RGP_SELF_insect_InsectBattlePickTalkIdMaybe_4f0530 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F0530 -- 752 bytes, 188 instructions, 15 calls, 29 branches.
 * A three-arm `switch` picking a battle-formation id.  Every divide is `%`
 * (mfhi), so none of them carries retail's divide-by-zero trap and the file
 * needs no `#pragma divbyzerocheck`.  `% 2` is the signed and-1/subtract-2
 * idiom, not a divide at all.
 */

typedef struct Ctx {
    u8  pad0000[0x35F8];
    u8  f35F8[0x5DA8 - 0x35F8];     /* +0x35F8 */
    s32 f5DA8;                      /* +0x5DA8 */
    u8  pad5DAC[0x5DD2 - 0x5DAC];
    s16 f5DD2;                      /* +0x5DD2 */
} Ctx;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 insect_InsectBattlePickTalkIdMaybe_4f0530(Ctx *o, s32 which)
{
    u8 *p2;
    s32 ret;
    s32 sw;
    s32 big;
    s32 ok;
    s32 a;
    s32 flag;
    s32 b;
    s32 lo;
    s32 hi;
    s32 j;
    s32 ok2;
    s32 v;
    u8 *p;
    s32 i;
    void *q;

    ret = -1;
    switch (which) {
    case 0:
        if (o->f5DA8 == 5) {
            a = insect_InsectBattleTeamPower_4f02e0(o, 0, 0);
            b = insect_InsectBattleTeamPower_4f02e0(o, 1, 0);
            if (a < b) {
                lo = a;
            } else {
                lo = b;
            }
            if (b < a) {
                hi = a;
            } else {
                hi = b;
            }
            if ((hi >> 1) >= lo) {
                return Rand_133710() % 2 + 5;
            }
        }
        return Rand_133710() % 5;

    case 1:
        return Rand_133710() % 5;

    case 2:
        sw = 0;
        big = 0;
        ok = 1;
        flag = insect_InsectBattleTestFlag_50da40(o, 0x3F);
        a = insect_InsectBattleTeamPower_4f02e0(o, 0, 1);
        b = insect_InsectBattleTeamPower_4f02e0(o, 1, 1);
        if (a < b) {
            lo = a;
        } else {
            lo = b;
        }
        if (b < a) {
            hi = a;
        } else {
            hi = b;
        }
        if (b < a) {
            sw = 1;
        }
        if ((hi >> 1) >= lo) {
            big = 1;
        }
        if (big != 0) {
            if (flag != 0) {
                if (sw == 0) {
                    return 7;
                }
            } else {
                if (sw != 0) {
                    return 7;
                }
            }
        }
        v = o->f5DD2;
        if (v >= 0x1E) {
            return 6;
        }
        if (v < 9) {
            return 5;
        }
        p = o->f35F8;
        if (flag == 0) {
            p += 0x994;
        }
        i = 0;
        while (i < 5) {
            if (insect_InsectPieceTestStatus_513280(insect_InsectTeamGetPiece_5138d0(p, i), 0x1B) == 0) {
                ok = 0;
                break;
            }
            i++;
        }
        if (ok != 0) {
            return 4;
        }
        ok2 = 1;
        if (insect_InsectBattleTestFlag_50da40(o, 0x38) != 0) {
            p2 = o->f35F8;
            if (flag != 0) {
                p2 += 0x994;
            }
            j = 0;
            while (j < 5) {
                q = insect_InsectTeamGetPiece_5138d0(p2, j);
                if (insect_InsectPieceTestStatus_513280(q, 0x1B) == 0 &&
                    insect_InsectPieceTestStatus_513280(q, 0x1A) == 0) {
                    ok2 = 0;
                    break;
                }
                j++;
            }
            if (ok2 != 0) {
                return 3;
            }
        }
        ret = Rand_133710() % 3;
        break;

    default:
        break;
    }
    return ret;
}
