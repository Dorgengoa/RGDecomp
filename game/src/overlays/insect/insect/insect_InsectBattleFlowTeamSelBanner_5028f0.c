/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowTeamSelBanner_5028f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x005028F0 -- 308 bytes, 77 instructions. */

typedef struct Sub {
    u8  pad00[4];
} Sub;

typedef struct Obj {
    u8  pad0000[0x4F90];
    Sub f4F90;                      /* +0x4F90 */
    u8  pad4F94[0x4FBC - 0x4F94];
    u8  f4FBC;                      /* +0x4FBC */
    u8  pad4FBD[0x5DA8 - 0x4FBD];
    s32 f5DA8;                      /* +0x5DA8 */
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleFlowTeamSelBanner_5028f0(Obj *a)
{
    s32 m;
    s32 k;

    switch (insect_InsectBattleGetStep_50d6a0(a, 0)) {
    case 1:
        insect_InsectCursorSetPushPage_511cf0(&a->f4F90, 0, 1);
        m = 2;
        k = 0x1D;
        if (a->f5DA8 != 3) {
            m = 5;
            k = 0;
        }
        insect_InsectBattleSetStep_50d7a0(a, m, 0, -1);
        insect_InsectBattleSetState_50d8c0(a, k, 2, -1);
        break;
    case 2:
        break;
    case 3:
        a->f4FBC = a->f4FBC & 0xFD;
        insect_InsectBattleSetStep_50d7a0(a, 4, 0, -1);
        break;
    case 4:
        if (insect_InsectCursorSetGetEventsExcept_5119b0(&a->f4F90, 0x4000) != 0) {
            insect_InsectBattleSetStep_50d7a0(a, 4, 2, -1);
            insect_InsectBattleSetStep_50d7a0(a, 2, 0, -1);
        }
        break;
    case 5:
        insect_InsectBattleSetState_50d8c0(a, 6, 0, -1);
        break;
    }
}
