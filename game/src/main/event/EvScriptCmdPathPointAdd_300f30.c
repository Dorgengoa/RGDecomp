/* rgp:protos */
#define RGP_SELF_EvScriptCmdPathPointAdd_300f30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

#define F32(o) (*(f32 *)(buf + (o) - 0x50))

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvScriptCmdPathPointAdd_300f30(s32 arg0, s32 arg1)
{
    u8 buf[0x30] __attribute__((aligned(16)));
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f20_3;
    f32 temp_f21;
    f32 temp_f21_2;
    f32 temp_f21_3;

    if ((arg1 != 0) && (arg1 != 3) && (arg1 != 6) && (arg1 != 9)) {
        return 0;
    }
    SrtCtor48_1c7510((f32 *)buf);
    if (arg1 >= 3) {
        temp_f21 = ScriptArgGetFloat_301a20(arg0);
        temp_f20 = ScriptArgGetFloat_301a20(arg0 + 8);
        SrtSetPos_1c73b0((f32 *)buf, temp_f21, temp_f20, ScriptArgGetFloat_301a20(arg0 + 0x10));
    }
    if (arg1 >= 6) {
        temp_f21_2 = ScriptArgGetFloat_301a20(arg0 + 0x18);
        temp_f20_2 = ScriptArgGetFloat_301a20(arg0 + 0x20);
        SrtSetRot_1c73d0((f32 *)buf, temp_f21_2, temp_f20_2, ScriptArgGetFloat_301a20(arg0 + 0x28));
    }
    if (arg1 >= 9) {
        temp_f21_3 = ScriptArgGetFloat_301a20(arg0 + 0x30);
        temp_f20_3 = ScriptArgGetFloat_301a20(arg0 + 0x38);
        SrtSetScale_1c73f0((f32 *)buf, temp_f21_3, temp_f20_3, ScriptArgGetFloat_301a20(arg0 + 0x40));
    }
    return EventPathRecPointPush_3010a0(F32(0x70), F32(0x74), F32(0x78), F32(0x60), F32(0x64), F32(0x68),
                         F32(0x50), F32(0x54), F32(0x58));
}
