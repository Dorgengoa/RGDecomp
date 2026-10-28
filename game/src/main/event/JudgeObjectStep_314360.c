/* rgp:protos */
#define RGP_SELF_JudgeObjectStep_314360 1
#include "port/game_protos.h"
#line 1
/* PARK: same length as retail, 27 bad words after 1 round. Not re-tried. */
#include "types.h"

typedef struct {
    u8 pad0[0x80];
    s32 unk80;
    u8 pad84[0x32];
    s16 unkB6;
    u8 padB8[0x2];
    s16 unkBA;
    s16 unkBC;
    u8 padBE[0x6];
    f32 unkC4;
    f32 unkC8;
    f32 unkCC;
} T314360_arg0;

s32 JudgeObjectStep_314360(T314360_arg0 *arg0, int rgp_a1, f32 fparg0)
{
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_3;
    s16 temp_3;
    s32 var_6;
    void *temp_5;

    if (arg0->unkB6 != 0) {
        return 0;
    }
    arg0->unk80 = 0;
    temp_f1 = arg0->unkC8 - fparg0;
    arg0->unkC8 = temp_f1;
    if (!(temp_f1 < 0.0f)) {
        return 0;
    }
    temp_3 = arg0->unkBC;
    if ((temp_3 > 0) && (temp_3 <= arg0->unkBA)) {
        arg0->unkB6 = 1;
        return 0;
    }
    temp_f1_2 = arg0->unkCC - fparg0;
    arg0->unkCC = temp_f1_2;
    if (temp_f1_2 < 0.0f) {
        arg0->unkCC = 0.0f;
    }
    temp_f1_3 = arg0->unkC4 - fparg0;
    arg0->unkC4 = temp_f1_3;
    if (temp_f1_3 < 0.0f) {
        arg0->unkB6 = 1;
        return 0;
    }
    var_6 = 0;
    do {
        temp_5 = (u8 *)arg0 + (var_6 * 2);
        var_6 += 1;
        *(s16 *)((u8 *)temp_5 + 0xD0) = (s16) (*(s16 *)((u8 *)temp_5 + 0xD0) + 1);
    } while (var_6 < 0x28);
    return 0;
}
