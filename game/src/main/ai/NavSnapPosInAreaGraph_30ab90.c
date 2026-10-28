/* rgp:protos */
#define RGP_SELF_NavSnapPosInAreaGraph_30ab90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_repositioncode on

typedef struct {
    u8 pad0[0x18];
    s16 *unk18;
} Obj0036;

typedef struct {
    u8 pad0[0x238];
    Obj0036 *unk238;
} Sub20;

typedef struct {
    u8 pad0[0x20];
    Sub20 *unk20;
} Obj001fede0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 NavSnapPosInAreaGraph_30ab90(s32 arg0, s32 arg1, s32 arg2)
{
    f32 var_f12;
    s16 *var_2;
    s32 temp_2;
    s32 temp_2_2;
    u16 var_16;
    Obj0036 *temp_2_3;

    temp_2_2 = MapFindBlockAtPos_1e3a00(((s32)GetMapMgr_201a90()), arg2, 0);
    if (temp_2_2 == 0) {
        return 0;
    }
    temp_2 = NavMgrFindGraphById_30cae0(arg0, MapBlockGetNavGraphId_1e0050(temp_2_2));
    if (temp_2 != 0) {
        var_16 = 1;
        if (GetGameMode_1f59c0() == 0xA) {
            temp_2_3 = ((Obj001fede0 *)GetGameData_1fede0())->unk20->unk238;
            if (temp_2_3 != NULL) {
                var_2 = temp_2_3->unk18;
            } else {
                var_2 = NULL;
            }
            if ((var_2 != NULL) && (*var_2 == 0x40A)) {
                var_16 = 0;
            }
        }
        if (var_16) {
            var_f12 = 100.0f;
        } else {
            var_f12 = (f32) 0x2710;
        }
        return NavSnapPointToCenterNet_30faa0(temp_2, arg1, arg2, 0, var_f12);
    }
    return 0;
    return 0;
}
