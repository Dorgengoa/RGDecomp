/* rgp:protos */
#define RGP_SELF_insect_InsectBattleLoadWorldData_4f9900 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x004F9900 -- 212 bytes, 53 instructions. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void insect_InsectBattleLoadWorldData_4f9900(void *a)
{
    void *p;

    p = GetWorldDataMgr_1fedf0();
    if (p != 0) {
        switch (insect_InsectBattleGetStep_50d6a0(a, 1)) {
        case 1:
            WorldDataRequestKind_3f0960(p, 6);
            insect_InsectBattleSetStep_50d7a0(a, 0xA, 1, -1);
            break;
        case 0xA:
            if (WorldDataMgrNoRequestPending_3eef10(p) != 0) {
                insect_InsectBattleSetStep_50d7a0(a, 0, 1, -1);
                if (insect_InsectBattleTestFlag_50da40(a, 5) != 0) {
                    insect_InsectBattleSetState_50d8c0(a, 0, 1, -1);
                }
            }
            break;
        }
    }
}
