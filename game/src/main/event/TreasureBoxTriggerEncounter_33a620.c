/* rgp:protos */
#define RGP_SELF_TreasureBoxTriggerEncounter_33a620 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct Bits { u8 bit:1; u8 rest:7; } Bits;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 TreasureBoxTriggerEncounter_33a620(void *arg0) {
    u8 temp_6;

    if (((s32)GetGameData_1fede0()) == 0) {
        return 0;
    }
    if (((s32)GetActionMgr_1fdb50()) == 0) {
        return 0;
    }
    if (GetCurrentScene_1f5be0() == 0) {
        return 0;
    }
    if (TreasureBoxIsEncounterBox_33aac0(arg0) == 0) return 1;
    if (TreasureBoxGetEncounterId_33aa40(arg0) < 0) {
        return 1;
    }
    temp_6 = *(u8 *)((u8 *)arg0 + 0x70);
    ((Bits *)((u8 *)arg0 + 0x70))->bit = 0;
    *(s16 *)((u8 *)arg0 + 0x26) = 0;
    GameReqQueuePushBack_1f5b50(7, 2);
    return 1;
}
