/* rg-override: replaces game/src/main/ui/ScreenMarkerSlotTick_31c190.c sha256 01e05afad07bf549043894a92a9da781d18aaf1b1548871e9178ed1811eea955
 * why: the C passes two uninitialised locals; retail's jal sees this function's own
 * untouched $a0/$a1 (listing 0x31C1D4). With zero-init locals the callee read address
 * 0x120 (fault at golden field ~22,000 once event keywords parse, docs/RENDER-BRINGUP.md) */
/* rgp:protos */
#define RGP_SELF_ScreenMarkerSlotTick_31c190 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma no_branch_likely on
#pragma opt_common_subs off
#pragma no_branch_likely off

typedef struct T31c190 {
    s16 unk0;
    u8 pad2[0x40 - 2];
    s16 unk40;
    u8 pad42[0xA0 - 0x42];
    s16 unkA0;
} T31c190;

/*rgp*/
/*rgp*/
/*rgp*/

void ScreenMarkerSlotTick_31c190(s32 arg0, s32 arg1)
{
    s32 dummy0,dummy1;
    s32 temp_17;
    T31c190 *temp_7;
    s16 temp_6;
    s16 *count;

    temp_17 = arg1 * 2;
    temp_7 = (T31c190 *)(arg0 + temp_17);
    if ((temp_6 = temp_7->unk0) != -1) {
        count = &temp_7->unk40;
        if ((*count > 0) && (ScreenMarkerGetPinned_31bf10(arg0, arg1) /* retail: $a0/$a1 untouched at the jal */ == 0)) {
            *count = *count - 1;
        }
        if (*count <= 0) {
            if (!(((T31c190 *)(temp_17 + arg0))->unkA0 == -1)) {
                ScreenMarkerSlotFadeOutTick_31c120(arg0, arg1);
            } else {
                ScreenMarkerSetFadeOut_31bf50(arg0, arg1, 0xF);
            }
        }
    }
}
