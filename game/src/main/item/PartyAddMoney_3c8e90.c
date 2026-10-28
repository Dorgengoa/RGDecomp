/* rgp:protos */
#define RGP_SELF_PartyAddMoney_3c8e90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3
#pragma opt_common_subs off
#pragma opt_propagation off

/*rgp*/
extern s32 D_004659E0[4];
extern void *D_00483890;

s64 PartyAddMoney_3c8e90(void *arg0, s64 arg1) {
    s64 temp_3;
    s64 lim;
    u8 *temp_3_2;
    u8 *temp_4;

    *(s64 *)((u8 *)arg0 + 0x160) = *(s64 *)((u8 *)arg0 + 0x160) + arg1;
    temp_3 = *(s64 *)((u8 *)arg0 + 0x160);
    if (temp_3 < 0) {
        *(s64 *)((u8 *)arg0 + 0x160) = 0;
    } else {
        lim = D_004659E0[0];
        if (lim < temp_3) {
            *(s64 *)((u8 *)arg0 + 0x160) = lim;
        }
    }
    if (arg1 > 0) {
        temp_4 = (u8 *)&((s32 *)((u8 *)arg0 + 0x42D0))[StateGetChapterIndexMaybe_3cd500(*(s32 *)((u8 *)D_00483890 + 0x10))] - 0x42D0;
        *(s32 *)(temp_4 + 0x42D0) = *(s32 *)(temp_4 + 0x42D0) + (s32) arg1;
        *(s32 *)(temp_4 + 0x4350) = (s32) * (s64 *)((u8 *)arg0 + 0x160);
    } else {
        s64 m;
        s32 t;
        s32 n;
        s32 idx = StateGetChapterIndexMaybe_3cd500(*(s32 *)((u8 *)D_00483890 + 0x10));
        t = idx << 2;
        m = 0 - arg1;
        n = (s32)m;
        temp_3_2 = (u8 *)(t + (s32)arg0);
        *(s32 *)(temp_3_2 + 0x4310) = *(s32 *)(temp_3_2 + 0x4310) + n;
        *(s32 *)(temp_3_2 + 0x4350) = (s32) * (s64 *)((u8 *)arg0 + 0x160);
    }
    return *(s64 *)((u8 *)arg0 + 0x160);
}
