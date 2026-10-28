/* rgp:protos */
#define RGP_SELF_HatenaMarkListDraw_344e60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

void HatenaMarkListDraw_344e60(u8 *arg0)
{
    u8 *temp_3;
    u8 *temp_3_2;
    u8 *var_4;

    if (*(void **)(arg0 + 4) == NULL) {
        *(void **)(arg0 + 4) = *(void **)(arg0 + 0);
        *(s32 *)(arg0 + 8) = 0;
    }
    for (;;) {
        temp_3 = *(u8 **)(arg0 + 4);
        if (temp_3 == NULL) {
            var_4 = NULL;
        } else {
            var_4 = temp_3 + 0x10;
            temp_3_2 = *(u8 **)temp_3;
            *(u8 **)(arg0 + 4) = temp_3_2;
            if (temp_3_2 == NULL) {
                *(s32 *)(arg0 + 8) = 1;
            }
        }
        if (var_4 != NULL) {
            HatenaMarkDraw_3453d0(var_4);
            continue;
        }
        break;
    }
    *(void **)(arg0 + 4) = NULL;
    *(s32 *)(arg0 + 8) = 0;
}
