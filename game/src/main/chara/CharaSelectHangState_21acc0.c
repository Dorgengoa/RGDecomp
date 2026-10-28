/* rgp:protos */
#define RGP_SELF_CharaSelectHangState_21acc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S0021acc0 {
    u8 pad0[0x570];
    s64 unk570;
    u8 pad578[0xA30 - 0x578];
    s16 unkA30;
    s16 unkA32;
    s16 unkA34;
    u8 padA36[0xE];
    s32 unkA44;
} S0021acc0;

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045CE20[];

s16 CharaSelectHangState_21acc0(S0021acc0 *arg0)
{
    s16 st;
    s32 f;
    s64 m;

    st = arg0->unkA34;
    switch (st) {
    case 0xC8:
        arg0->unkA30 = 4;
        return 0;
    case 0xC9:
        arg0->unkA30 = 5;
        return 1;
    case 1:
        f = arg0->unkA44;
        if ((f & 0x01000000) && !(f & 0x800000) && ((unsigned char)IsInBattle_288420()) != 0) {
            return 5;
        }
        if (CharaIsCurMotion_238540(arg0, D_0045CE20) == 0) {
            return arg0->unkA34;
        }
        break;
    default:
        return 1;
    case 2:
    case 3:
    case 0:
        break;
    case 4:
        return st;
    }
    m = arg0->unk570;
    if (m & 0x20000) {
        return 4;
    }
    if (m & 0x40000) {
        return 5;
    }
    if (m & 3) {
        switch (CharaActFlagsDirBitsMaybe_20a5a0((int)(m))) {
        case 8:
            arg0->unkA34 = -1;
            return 2;
        case 16:
            arg0->unkA34 = -1;
            return 3;
        }
    }
    return arg0->unkA34;
}
