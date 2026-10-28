/* rgp:protos */
#define RGP_SELF_OverlayLocateFiles_1c3300 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
extern s8 *strcpy(s8 *dst, s8 *src);

extern s32 D_0044AF90[][7];
extern s32 D_0048155C;
extern s32 D_004A6F80[7];

void OverlayLocateFiles_1c3300(void)
{
    s32 sp90[0xC] __attribute__((aligned(16)));
    s8 sp30[0x60] __attribute__((aligned(16)));
    s32 temp_2;
    s32 var_17;

    var_17 = 0;
    do {
        temp_2 = ((s32)Strchr_1347c0(D_0044AF90[D_0048155C][var_17], 0x3A));
        if (temp_2 != 0) {
            strcpy(sp30, (s8 *) (temp_2 + 1));
        }
        FileCdSearchLocked_180360(sp90, sp30);
        D_004A6F80[var_17] = sp90[0];
        var_17 += 1;
    } while (var_17 < 7);
}
