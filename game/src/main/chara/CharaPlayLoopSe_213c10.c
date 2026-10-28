/* rgp:protos */
#define RGP_SELF_CharaPlayLoopSe_213c10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00213c10 {
    u8 pad0[0x3F4];
    s32 unk3F4;
    u8 pad3F8[0xA58 - 0x3F8];
    s16 unkA58;
    s16 unkA5A;
} S00213c10;

/*rgp*/

void CharaPlayLoopSe_213c10(S00213c10 *arg0, s32 arg1)
{
    if (arg1 < 0 || arg1 != arg0->unkA58) {
        if (arg0->unk3F4 != 0) {
            arg0->unkA58 = -1;
            arg0->unkA5A = -1;
        }
        if (arg1 >= 0 && arg0->unk3F4 != 0) {
            arg0->unkA58 = arg1;
            arg0->unkA5A = SoundNextPlayHandle_1b81c0();
        }
    }
}
