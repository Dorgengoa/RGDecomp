/* rgp:hwaccess */ #include "port/hwaccess.h"
/* rgp:hwaccess */ extern unsigned char D_00527020[];
#line 1
/* rgp:protos */
#define RGP_SELF_CharaGetControlStateMaybe_2f5320 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaGetControlStateMaybe_2f5320(s32 arg0)
{
    s32 temp_2;

    if ((((unsigned char)IsInBattle_288420()) != 0) && ((*(s16 *)((unsigned char *)D_00527020 + 0x3A2)) == 4)) {
        return 1;
    }
    if (!(GameReqQueueContainsId_1f5b90(0xB) == 0)) {
        return 1;
    }
    if (GameReqQueueContainsId_1f5b90(7) != 0) {
        return 1;
    }
    if (GameReqQueueContainsId_1f5b90(9) != 0) {
        return 1;
    }
    if (GameReqQueueContainsId_1f5b90(0xA) != 0) {
        return 1;
    }
    temp_2 = ((s32)ActionMgrFindById_233b50(((s32)GetActionMgr_1fdb50()), arg0));
    if (temp_2 == 0) goto r0;
    if (CharaEvObjContactFlag1Related_214920(temp_2) != 0) {
        return 2;
    }
    if (CharaEvObjContactFlag2Related_2148e0(temp_2) != 0) {
        return 2;
    }
    if (CharaIsControllableMaybe_20ff00(temp_2) != 0) goto r0;
    return 3;
r0:
    return 0;
}
