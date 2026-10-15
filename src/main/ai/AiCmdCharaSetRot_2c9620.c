#include "types.h"
typedef struct { s32 a; f32 b; s32 c; s32 d; } V;
extern void CharaSetRotFromVec_2387b0(s32, V *);
extern void CharaGetRot_2388b0(s32, V *);
extern void ScriptSlotsToVec4_2cc920(V *, s32);
extern f32 ScriptSlotGetFloat_2cc9a0(s32);
extern s32 D_004DB92C[4];

s32 AiCmdCharaSetRot_2c9620(s32 arg0, s32 arg1)
{
    V v;
    if (D_004DB92C[0] == 0) {
        return 0;
    }
    switch (arg1) {
    case 1:
        CharaGetRot_2388b0(D_004DB92C[0], &v);
        v.b = ScriptSlotGetFloat_2cc9a0(arg0);
        CharaSetRotFromVec_2387b0(D_004DB92C[0], &v);
        break;
    case 3:
        ScriptSlotsToVec4_2cc920(&v, arg0);
        v.d = 0;
        CharaSetRotFromVec_2387b0(D_004DB92C[0], &v);
        break;
    default:
        return 0;
    }
    return 1;
}

