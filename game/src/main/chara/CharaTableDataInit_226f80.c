/* rgp:protos */
#define RGP_SELF_CharaTableDataInit_226f80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S00226f80 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s16 unk24;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
} S00226f80;

/*rgp*/

void CharaTableDataInit_226f80(S00226f80 *arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4, s16 arg5,
                   s32 arg6, s16 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11,
                   s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16, s32 arg17)
{
    CharaTableDataClear_227090((void *)arg0);
    if (arg1 != 0) {
        arg0->unk0 = arg1;
        arg0->unk4 = arg2;
        if (arg2 != 0) {
            arg0->unk24 = arg3;
        }
        arg0->unk8 = arg4;
        if (arg4 != 0) {
            arg0->unk26 = arg5;
        }
        arg0->unkC = arg6;
        if (arg6 != 0) {
            arg0->unk28 = arg7;
        }
        arg0->unk10 = arg8;
        if (arg8 != 0) {
            arg0->unk2A = (s16)arg9;
        }
        arg0->unk14 = arg10;
        if (arg10 != 0) {
            arg0->unk2C = (s16)arg11;
        }
        arg0->unk18 = arg12;
        if (arg12 != 0) {
            arg0->unk2E = (s16)arg13;
        }
        arg0->unk1C = arg14;
        if (arg14 != 0) {
            arg0->unk30 = (s16)arg15;
        }
        arg0->unk20 = arg16;
        if (arg16 != 0) {
            arg0->unk32 = (s16)arg17;
        }
    }
}
