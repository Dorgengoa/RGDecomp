/* rgp:protos */
#define RGP_SELF_CharaDataReleaseById_1ed850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                             /* extern */
/*rgp*/                           /* extern */
/*rgp*/                               /* extern */
/*rgp*/                             /* extern */

void CharaDataReleaseById_1ed850(u8 *arg0, s32 arg1) {
    s16 temp_16;
    s32 temp_4;
    s32 var_17;
    s32 var_17_2;
    u8 *temp_2;
    u8 *temp_3;

    temp_2 = ((u8 *)CharaDataFindById_1ed990((int)arg0, (int)arg1));
    if (temp_2 != 0) {
        temp_16 = (*(s16 *)((u8 *)temp_2 + 0x64));
        if (temp_16 == 1) {
            var_17 = (*(s32 *)((u8 *)temp_2 + 0x30));
        }
        CharaDataRecRelease_1ee190(temp_2);
        if (temp_16 == 0) {
            var_17_2 = 0;
            do {
                temp_3 = arg0 + (var_17_2 * 2);
                if ((*(s16 *)((u8 *)temp_3 + 0xF88)) == arg1) {
                    MemStackReset_14d830(arg0 + (var_17_2 * 0x58) + 0xE80);
                    (*(s16 *)((u8 *)temp_3 + 0xF88)) = -1;
                }
                var_17_2 += 1;
            } while (var_17_2 < 3);
            return;
        }
        if (temp_16 == 1) {
            temp_4 = (*(s32 *)((u8 *)arg0 + 0xF94));
            if (temp_4 != 0) {
                MemStackHeapFree_14dcb0(temp_4, var_17);
            }
        }
    }
}
