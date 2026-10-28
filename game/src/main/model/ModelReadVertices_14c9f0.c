/* rgp:protos */
#define RGP_SELF_ModelReadVertices_14c9f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"

/*rgp*/
/*rgp*/
/*rgp*/

s32 ModelReadVertices_14c9f0(void **arg0, s32 arg1, s32 arg2, s32 arg3)
{
    u128 sp60;
    s32 temp_19;
        s32 var_20;
    u16 var_3;
    u32 temp_3;
    s32 var_3_2;
    void *temp_2;
    void *temp_6;
    void *var_5;

    var_3 = 0;
    temp_6 = *arg0;
    if (temp_6 != NULL && *(u16 *)((u8 *)temp_6 + 0x6C) == 0) {
        var_3 = 1;
    }
    if (!(var_3 & 0xFF)) {
        return 0;
    }
    if (temp_6 != NULL) {
        var_5 = *(void **)((u8 *)temp_6 + 0x60);
    } else {
        var_5 = NULL;
    }
    temp_3 = *(u32 *)((u8 *)var_5 + 0x0);
    if ((u32)(arg3 + arg2) >= temp_3) {
        arg2 = temp_3 - arg3;
    }
    if (arg2 <= 0) {
        return 0;
    }
    temp_19 = *(s32 *)((u8 *)var_5 + 0x4);
    sp60 = *(u128 *)((u8 *)temp_6 + 0x20);
    temp_2 = *arg0;
    if (temp_2 != NULL) {
        var_3_2 = *(u8 *)((u8 *)temp_2 + 0x10);
    } else {
        var_3_2 = 0x20;
    }
    switch (var_3_2) {
    case 32:
        for (var_20 = 0; var_20 < arg2; var_20++) {
            VertexDecodeF32_14b4a0(arg1 + (var_20 * 0x10), temp_19 + ((arg3 + var_20) * 0xC));
        }
        break;
    case 16:
        for (var_20 = 0; var_20 < arg2; var_20++) {
            VertexDecodeS16_14b410(arg1 + (var_20 * 0x10), temp_19 + ((arg3 + var_20) * 6), &sp60);
        }
        break;
    case 8:
        for (var_20 = 0; var_20 < arg2; var_20++) {
            VertexDecodeS8_14b3a0(arg1 + (var_20 * 0x10), temp_19 + ((arg3 + var_20) * 3), &sp60);
        }
        break;
    }
    return arg2;
}
