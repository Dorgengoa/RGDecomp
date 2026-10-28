/* rgp:protos */
#define RGP_SELF_EventVoiceFindChanAndStop_24e910 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void EventVoiceFindChanAndStop_24e910(u8 *arg0, s32 arg1)
{
    s32 temp_2;
    s32 var_16;
    s32 var_4;
    u8 *temp_3;
    u8 *temp_3_2;
    u8 *var_6;

    temp_2 = EventVoiceCountPlayingChans_24fae0((void *)arg0);
    if (*(void **)(arg0 + 4) != NULL) {
        var_4 = -1;
    } else {
        var_4 = 0;
        *(void **)(arg0 + 4) = *(void **)(arg0 + 0);
        *(s32 *)(arg0 + 8) = 0;
    }
    if (var_4 != 0) {
        var_6 = NULL;
    } else {
        goto body;
    top:
        if (arg1 == var_16) {
            goto out;
        }
    body:
            temp_3 = *(u8 **)(arg0 + 4);
            if (temp_3 == NULL) {
                var_6 = NULL;
            } else {
                var_16 = *(s32 *)(temp_3 + 0xC);
                var_6 = temp_3 + 0x10;
                temp_3_2 = *(u8 **)temp_3;
                *(void **)(arg0 + 4) = temp_3_2;
                if (temp_3_2 == NULL) {
                    *(s32 *)(arg0 + 8) = 1;
                }
            }
        if (var_6 != NULL) {
            goto top;
        }
    out:
        *(void **)(arg0 + 4) = NULL;
        *(s32 *)(arg0 + 8) = 0;
    }
    if (var_6 != NULL) {
        EventVoiceChanStop_24e9e0(arg0, arg1, var_6, temp_2 - 1);
    }
}
