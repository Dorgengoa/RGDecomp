/* rgp:protos */
#define RGP_SELF_Character2DrawWithOwnLightMaybe_1ae720 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#include "vec.h"
#pragma opt_propagation off

/*rgp*/                           /* extern */
/*rgp*/                    /* extern */
/*rgp*/                                /* extern */
/*rgp*/                              /* extern */
/*rgp*/                             /* extern */
/*rgp*/                           /* extern */
/*rgp*/                                 /* extern */
/*rgp*/                              /* extern */
/*rgp*/          /* extern */

s32 Character2DrawWithOwnLightMaybe_1ae720(s32 arg0) {
    s32 arg_h1;

    s8 sp200[0x10] __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(u128)]; char m1[0x10 + sizeof(u8[0x190])]; char m2[0xe0]; char m3[0x100]; })]; typedef char rgp_blk1_chk0[(0x0) + sizeof(u128) <= (0x10) && (0x0) >= 0 ? 1 : -1];
    
    Vec4 sp50 __attribute__((aligned(16)));
    Vec4 sp40 __attribute__((aligned(16)));
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
    ((s32 *)&(*(u128 *)(rgp_blk1 + 0x0)))[1] = 0;
    ((s32 *)&(*(u128 *)(rgp_blk1 + 0x0)))[0] = -1;
    LightStateInit_156b50((s32 *)&(*(u128 *)(rgp_blk1 + 0x0)));
    temp_17 = ((s32)LightStatePush_1429f0(temp_18, (s32 *)&(*(u128 *)(rgp_blk1 + 0x0)), 1));
    LightStateSetMatrices_15cc00(arg0 + 0x630, arg0 + 0x6F0);
    sceVu0InterVector(&sp50, (Vec4 *)(sp200), (Vec4 *)((u8 *)arg0 + 0x5D0), 0.0f);
    sceVu0InterVector(&sp40, (Vec4 *)(sp200), (Vec4 *)((u8 *)arg0 + 0x5A0), 0.0f);
    *(Vec4 *)((*(u8 (*)[0x190])(rgp_blk1 + 0x10)) + 0xC0) = sp50;
    LightStateSetAmbient_15cb30(&sp40);
    DrawListAddLightPacket_148120(temp_18);
    temp_16 = ModelObjExDraw_1ad7a0(arg0, 0, 0, 0);
    LightStateSetCurrent_142920(temp_18, temp_17);
    return temp_16;
}
