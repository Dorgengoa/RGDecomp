/* rgp:protos */
#define RGP_SELF_EffInstStopEmitters_19ab10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

void EffInstStopEmitters_19ab10(u8 *arg0, u8 *arg1) {
    u8 **var_11;
    s32 temp_5;
    u8 *var_10;
    s32 var_9;
    u8 *var_8;
    u8 *temp_3;
    s32 var_7;
    u8 *obj;

    var_10 = *(u8 **)(arg1 + 0xC4);
    var_11 = *(u8 ***)(arg0 + 0xA0);
    if (var_10 != NULL) {
        var_9 = 0;
        while (var_9 < *(s32 *)(arg0 + 0x9C)) {
            obj = *var_11;
            temp_3 = *(u8 **)(obj + 0xC);
            if (temp_3 != NULL) {
                var_8 = *(u8 **)(temp_3 + 0x44);
                var_7 = 0;
                while ((((var_8 != NULL) ^ 1) == 0) && (var_7 < *(s32 *)(var_10 + 0xC0))) {
                    *(s32 *)(*(u8 **)(var_10 + 0xC4) + var_7 * 0x110 + 0x10C) = 1;
                    var_7 += 1;
                    var_8 = *(u8 **)var_8;
                }
            }
            var_9 += 1;
            var_11 += 1;
            var_10 += 0x120;
        }
    }
}
