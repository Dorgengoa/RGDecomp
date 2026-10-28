/* rgp:protos */
#define RGP_SELF_CharaReqClimbOrFallByHeight_2bd140 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 D_0045B080[0x400];

void CharaReqClimbOrFallByHeight_2bd140(s32 pad0, s32 arg1, void *arg2) {
    u8 sp30[0x10] __attribute__((aligned(16)));
    f32 t;
    f32 temp_f1;

    if (arg1 != 0) {
        CharaGetPos_2388a0(arg1, sp30);
        t = *(f32 *)(sp30 + 4);
        temp_f1 = *(f32 *)((u8 *)arg2 + 4);
        if (!(temp_f1 < t)) {
            CharaAddFlags_212460(arg1, (long long)(0x20000));
            CharaRemoveFlags_212480(arg1, (unsigned long long)(3));
        } else {
            if (temp_f1 < (t - *(f32 *)D_0045B080)) {
                CharaAddFlags_212460(arg1, (long long)(0x40000));
                CharaRemoveFlags_212480(arg1, (unsigned long long)(3));
            }
        }
    }
}
