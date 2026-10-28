/* rgp:protos */
#define RGP_SELF_AiCmdCharaCloneObjSpawn_2c1f60 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

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
    CharaCloneObjSpawn_2ccf00(x, y, ScriptSlotGetInt_2cc9c0((s32)arg0), a, b);
    return 1;
}
