/* rgp:protos */
#define RGP_SELF_AiCollectIdsByGroup_2cd1a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x18E];
    s16 unk18E;
} Obj0018;

typedef struct {
    u8 pad0[0x18];
    Obj0018 *unk18;
} Obj001fede0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 AiCollectIdsByGroup_2cd1a0(s32 arg0, s32 arg1, s32 *arg2, s32 arg3)
{
    s32 var_5;

    var_5 = arg1;
    if (var_5 == 0x102) {
        if ((arg0 >= 0) && (arg0 < 0xC)) {
            var_5 = 0x100;
        }
        if ((arg0 >= 0x80) && (arg0 < 0x9C)) {
            var_5 = 0x101;
        }
    } else if (var_5 == 0x103) {
        if ((arg0 >= 0) && (arg0 < 0xC)) {
            var_5 = 0x101;
        }
        if ((arg0 >= 0x80) && (arg0 < 0x9C)) {
            var_5 = 0x100;
        }
    }
    switch (var_5) {
    case 0xFF:
        return AiCollectAllIds_2cd4d0(arg2, arg3);
    case 0x100:
        return PartyCollectLiveMemberIds_2cd6e0(arg2);
    case 0x101:
        return AiCollectTargetIds_2cd530(arg2);
    case 0x104:
        *arg2 = ((Obj001fede0 *)GetGameData_1fede0())->unk18->unk18E;
        return 1;
    default:
        *arg2 = var_5;
        return 1;
    }
}
