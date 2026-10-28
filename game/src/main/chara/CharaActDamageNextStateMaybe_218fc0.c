/* rgp:protos */
#define RGP_SELF_CharaActDamageNextStateMaybe_218fc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad0[0x424];
    s16 unk424;
    u8 pad426[0xA34 - 0x426];
    s16 unkA34;
    u8 padA36[0xAD0 - 0xA36];
    f32 unkAD0;
} Obj218fc0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 CharaActDamageNextStateMaybe_218fc0(Obj218fc0 *arg0)
{
    f32 f;
    u8 *r;

    switch (arg0->unkA34) {
    case 1:
        f = arg0->unkAD0;
        if (f >= 30.0f) {
            return 2;
        }
        if (f >= 5.0f) {
            if (((unsigned char)CharaIsHeadUnderwaterMaybe_238250(arg0)) != 0) {
                return 2;
            }
            if (arg0->unk424 < 0x80 || arg0->unk424 > 0x9B) {
                if (CharaIsMovingXZMaybe_20f9c0(arg0) == 0) {
                    return 2;
                }
            } else {
                r = ((u8 *)CharaGetModelObj_2386f0(arg0));
                if (r != NULL && MotionListIsFinished_171d90(r + 0x1F0, -1) != 0) {
                    return 2;
                }
            }
        }
        break;
    case 2:
        return arg0->unkA34;
    }
    return 1;
}
