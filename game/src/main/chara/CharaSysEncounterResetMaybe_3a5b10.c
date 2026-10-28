/* rgp:protos */
#define RGP_SELF_CharaSysEncounterResetMaybe_3a5b10 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S {
    u8 pad0[4];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 rest : 5;
    u8 pad5;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    f64 unk20;
    u8 pad28[0x238 - 0x28];
    s32 unk238;
} S;

/*rgp*/

void CharaSysEncounterResetMaybe_3a5b10(S *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if (arg1 != 0) {
        arg0->b0 = 1;
        arg0->b1 = 1;
        arg0->b2 = 1;
    }
    arg0->unk6 = -1;
    arg0->unk8 = -1;
    arg0->unkA = -1;
    arg0->unkC = -1;
    arg0->unkE = -1;
    arg0->unk10 = -1;
    arg0->unk14 = 0;
    arg0->unk18 = 0;
    arg0->unk1C = -1;
    if (arg0->unk238 != 0) {
        CharaStateReset_3a79b0(arg0->unk238, 1, arg2, arg2, arg2);
    }
    if (arg3 != 0) {
        arg0->unk20 = -1.0;
    }
}
