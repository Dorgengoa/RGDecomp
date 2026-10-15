/* PARKED (round 1): length 0xB0 vs retail 0xB4 (4 bytes short). Close --
   possibly the always-return-1 tail (both D_00482868 branches) needs an
   explicit shared epilogue/goto instead of duplicated `return 1`. */
#include "types.h"

typedef struct Var5f740 { s32 tag; union { s32 i; f32 f; } v; } Var5f740;
typedef struct Var5f780 { s32 tag; union { s32 i; f32 f; } v; } Var5f780;

extern f32 ScriptArgGetFloat_301a20(Var5f740 *);
extern s32 ScriptArgGetInt_301a60(Var5f780 *);
extern void EvMapObjSetParams_366b10(void *, f32, s32, f32, s32);
extern s32 D_00482868;
extern s32 D_0048286C;
extern u8 D_004E6B80[];

s32 EvScriptCmdMapObjSetParams_2ff970(Var5f740 *arg0, s32 arg1)
{
    f32 temp_f20;
    f32 temp_f21;
    s32 temp_16;

    if (arg1 < 4) {
        return 0;
    }
    if ((D_00482868 == 0) || (D_0048286C >= 0x20)) return 1;
    temp_f21 = ScriptArgGetFloat_301a20(arg0);
    temp_f20 = ScriptArgGetFloat_301a20((Var5f740 *)((u8 *)arg0 + 8));
    temp_16 = ScriptArgGetInt_301a60((Var5f780 *)((u8 *)arg0 + 0x10));
    EvMapObjSetParams_366b10(D_004E6B80, temp_f21, temp_16, temp_f20, ScriptArgGetInt_301a60((Var5f780 *)((u8 *)arg0 + 0x18)));
    return 1;
    return 1;
}
