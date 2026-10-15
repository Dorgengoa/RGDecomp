#include "types.h"

extern f32 ScriptSlotGetFloat_2cc9a0(s32);
extern s32 ScriptSlotGetInt_2cc9c0(s32);
extern void CharaCloneObjSpawn_2ccf00(s32, s32, f32, s32, f32);

extern s32 D_004DB920[0x100];
extern s32 D_004DB928[0x100];

s32 AiCmdCharaCloneObjSpawn_2c1f60(s64 *arg0)
{
    f32 a;
    f32 b;
    s32 x;
    s32 y;

    x = *D_004DB920;
    y = *D_004DB928;
    a = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    b = ScriptSlotGetFloat_2cc9a0((s32)arg0++);
    CharaCloneObjSpawn_2ccf00(x, y, a, ScriptSlotGetInt_2cc9c0((s32)arg0), b);
    return 1;
}
