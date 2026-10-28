/* rgp:protos */
#define RGP_SELF_FrameTreeOrFlags_149530 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/

void FrameTreeOrFlags_149530(void *arg0, s32 arg1)
{
    s16 temp_3;
    s16 temp_3_2;
    s16 temp_3_3;
    void *var_18;
    void *var_17;
    void *var_16;
    void *var_21;
    void *var_20;

    temp_3 = *(s16 *)((u8 *)arg0 + 0x26) | arg1;
    *(s16 *)((u8 *)arg0 + 0x26) = temp_3;
    if (temp_3 & 0x10) {
        *(u8 *)((u8 *)arg0 + 0x2D) = 1;
    }
    var_18 = *(void **)((u8 *)arg0 + 0x8);
    while (var_18 != NULL) {
        temp_3_2 = *(s16 *)((u8 *)var_18 + 0x26) | arg1;
        *(s16 *)((u8 *)var_18 + 0x26) = temp_3_2;
        if (temp_3_2 & 0x10) {
            *(u8 *)((u8 *)var_18 + 0x2D) = 1;
        }
        var_17 = *(void **)((u8 *)var_18 + 0x8);
        while (var_17 != NULL) {
            temp_3_3 = *(s16 *)((u8 *)var_17 + 0x26) | arg1;
            *(s16 *)((u8 *)var_17 + 0x26) = temp_3_3;
            if (temp_3_3 & 0x10) {
                *(u8 *)((u8 *)var_17 + 0x2D) = 1;
            }
            var_16 = *(void **)((u8 *)var_17 + 0x8);
            while (var_16 != NULL) {
                ModelFrameSetFlags_14a760(var_16, *(s16 *)((u8 *)var_16 + 0x26) | arg1);
                var_21 = *(void **)((u8 *)var_16 + 0x8);
                while (var_21 != NULL) {
                    ModelFrameOrFlags_14a730(var_21, arg1);
                    var_20 = *(void **)((u8 *)var_21 + 0x8);
                    while (var_20 != NULL) {
                        FrameTreeOrFlags_149530(var_20, arg1);
                        var_20 = *(void **)((u8 *)var_20 + 0xC);
                    }
                    var_21 = *(void **)((u8 *)var_21 + 0xC);
                }
                var_16 = *(void **)((u8 *)var_16 + 0xC);
            }
            var_17 = *(void **)((u8 *)var_17 + 0xC);
        }
        var_18 = *(void **)((u8 *)var_18 + 0xC);
    }
}
