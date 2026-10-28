/* rgp:protos */
#define RGP_SELF_HelpBoardDebugUnlockAll_34f060 1
#include "port/game_protos.h"
#line 1
#pragma opt_propagation off
#include "types.h"

typedef struct {
    s16 f0;
    s16 f2;
} Pair16;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern Pair16 D_00453BD0[0x15];
extern u8 D_004B2570[0x100];

void HelpBoardDebugUnlockAll_34f060(void)
{
    Pair16 sp30[0x15] __attribute__((aligned(16)));
    Pair16 *var_7;
    Pair16 *var_6;
    s32 temp_4;
    s32 var_17;
    s32 var_5;
    void *temp_16;

    temp_16 = GetGameData_1fede0();
    if ((ReturnZero_207fe0() != 0) && (PadIsHeld_183a20(D_004B2570, 8) != 0) && (PadIsTriggered_1839f0(D_004B2570, 0x100) != 0)) {
        var_6 = sp30;
        var_7 = D_00453BD0;
        var_5 = 0x15;
        do {
            var_5 -= 1;
            var_6->f0 = var_7->f0;
            var_6->f2 = var_7->f2;
            var_7 += 1;
            var_6 += 1;
        } while (var_5 > 0);
        var_17 = 0;
        while (((s16 *)sp30)[var_17] != -1) {
            StateFlagSet_3ccb70(*(s32 *)((u8 *)temp_16 + 0x10), (int)(((s16 *)sp30)[var_17]), 1, 0);
            var_17 += 1;
        }
    }
}
