/* rgp:protos */
#define RGP_SELF_ModelUpdateFrameWorlds_1502b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj104 {
    s32 unk0;
    u8 pad4[4];
    s32 *unk8;
} Obj104;

typedef struct T001502b0 {
    s32 unk0;
    s32 unk4;
    u8 pad8[0x104 - 8];
    Obj104 *unk104;
    u8 pad108[0x10C - 0x108];
    s32 unk10C;
    s32 *unk110;
} T001502b0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 ModelUpdateFrameWorlds_1502b0(T001502b0 *arg0, s32 arg1)
{
    u8 sp40[0x40] __attribute__((aligned(16)));
    u8 sp30[0x10] __attribute__((aligned(16)));
    s32 *var_3;
    s32 temp_4;
    s32 var_16;
    s32 var_2;
    Obj104 *temp_2;

    if (((s32)DrawListGetCurBuf_142790(arg1)) == 0) {
        return 0;
    }
    if (arg0->unk0 == 0) {
        return 0;
    }
    temp_4 = arg0->unk4;
    if (temp_4 != 0) {
        FrameCalcWorldMatrix_148ff0(temp_4, sp40);
    }
    CameraGetEyePos_13fce0(arg1, sp30);
    for (var_16 = 0; var_16 < arg0->unk10C; var_16++) {
        FrameUpdateWorldWithEye_149af0(ArrayGetChecked_152fd0(arg0->unk104, arg0->unk110[var_16]), sp30, -1);
    }
    temp_2 = arg0->unk104;
    var_3 = temp_2->unk8;
    var_2 = temp_2->unk0;
    while (var_2 > 0) {
        *var_3 = 0;
        var_2 -= 1;
        var_3 += 1;
    }
    return 1;
}
