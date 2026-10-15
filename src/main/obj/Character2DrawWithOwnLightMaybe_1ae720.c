#include "types.h"
#include "vec.h"
#pragma opt_propagation off

s32 LightStateSetCurrent_142920(s32, s32);                           /* extern */
s32 LightStatePush_1429f0(s32, s32 *, s32);                    /* extern */
s32 DrawListAddLightPacket_148120(s32);                                /* extern */
s32 LightStateInit_156b50(s32 *);                              /* extern */
s32 LightStateSetAmbient_15cb30(Vec4 *);                             /* extern */
s32 LightStateSetMatrices_15cc00(s32, s32);                           /* extern */
s32 GetDrawCtx_15de80();                                 /* extern */
s32 ModelObjExDraw_1ad7a0(s32);                              /* extern */
void sceVu0InterVector(Vec4 *, const Vec4 *, const Vec4 *, f32);          /* extern */

s32 Character2DrawWithOwnLightMaybe_1ae720(s32 arg0) {
    s32 arg_h1;

    s8 sp200[0x10];
    u8 sp70[0x190];
    u128 sp60q;
    Vec4 sp50;
    Vec4 sp40;
    s32 temp_16;
    s32 temp_18;
    s32 temp_17;
    s8 *var_3;
    u32 var_2;

    var_2 = 0x10;
    var_3 = sp200;
    if (var_3 != 0) {
        do {
            *var_3 = 0;
            var_2 -= 1;
            var_3 += 1;
        } while (var_2 != 0);
    }
    temp_18 = GetDrawCtx_15de80();
    ((s32 *)&sp60q)[1] = 0;
    ((s32 *)&sp60q)[0] = -1;
    LightStateInit_156b50((s32 *)&sp60q);
    temp_17 = LightStatePush_1429f0(temp_18, (s32 *)&sp60q, 1);
    LightStateSetMatrices_15cc00(arg0 + 0x630, arg0 + 0x6F0);
    sceVu0InterVector(&sp50, (Vec4 *)(sp200), (Vec4 *)((u8 *)arg0 + 0x5D0), 0.0f);
    sceVu0InterVector(&sp40, (Vec4 *)(sp200), (Vec4 *)((u8 *)arg0 + 0x5A0), 0.0f);
    *(Vec4 *)(sp70 + 0xC0) = sp50;
    LightStateSetAmbient_15cb30(&sp40);
    DrawListAddLightPacket_148120(temp_18);
    temp_16 = ModelObjExDraw_1ad7a0(arg0);
    LightStateSetCurrent_142920(temp_18, temp_17);
    return temp_16;
}
