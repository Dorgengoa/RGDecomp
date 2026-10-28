/* rgp:protos */
#define RGP_SELF_CharaEventLogReset_3a6960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Arg0_003a6960 {
    u8 pad0[0x44];
    u8 bit0 : 1;
    u8 restbits : 7;
} Arg0_003a6960;

/*rgp*/
/*rgp*/
/*rgp*/

void CharaEventLogReset_3a6960(void *arg0) {
    u8 *var_18;
    u8 *var_18_2;
    u8 *var_18_3;
    s32 var_17;
    s32 var_17_2;
    s32 var_17_3;

    var_17 = 0;
    *(s16 *) arg0 = 0;
    var_18 = (u8 *) arg0 + 2;
    do {
        CharaEventLogKeyReset_3a6c20(var_18);
        var_17 += 1;
        var_18 += 4;
    } while (var_17 < 0x10);
    *(s16 *) ((u8 *) arg0 + 0x42) = 0;
    var_18_2 = (u8 *) arg0 + 0x46;
    var_17_2 = 0;
    do {
        CharaEventLogEntryReset_3a6bf0(var_18_2);
        var_17_2 += 1;
        var_18_2 += 8;
    } while (var_17_2 < 0x40);
    var_18_3 = (u8 *) arg0 + 0x248;
    var_17_3 = 0;
    do {
        CharaEventLogTimerReset_3a6940(var_18_3);
        var_17_3 += 1;
        var_18_3 += 8;
    } while (var_17_3 < 0x10);
    ((Arg0_003a6960 *) arg0)->bit0 = 0;
}
