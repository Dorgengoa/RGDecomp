/* rgp:protos */
#define RGP_SELF_EvCmdCastSetFlag8000Maybe_247100 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec3w {
    f32 x, y, z, w;
} Vec3w;

typedef struct Ctx {
    s32 unk0;
    s32 unk4;
} Ctx;


/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern f32 D_0047E7D0;
extern f32 D_0047E7D4;
extern f32 D_0047E7D8;
extern f32 D_0047E7DC;
extern Ctx *gEventContext;

s32 EvCmdCastSetFlag8000Maybe_247100(s64 *arg0, s32 arg1)
{ __typeof__(arg0) rgp_entry_arg0 = arg0;
    s32 id;
    s32 tbl;
    s32 flag;
    s32 ok;
    s32 obj;
    volatile Vec3w v __attribute__((aligned(16)));

    arg0++;
    tbl = gEventContext->unk4 + 0x60;
    id = EventCastFindKeyByName_24bb50(tbl, ScriptGetCodeAddr_249050((void *)rgp_entry_arg0));
    flag = ScriptGetInt_2490f0(arg0++);
    ok = EventCastGetObjId_24c160(tbl, id, 0);
    if (flag != 0) {
        ObjRecSetFlags_1c3e00(gEventContext->unk0, 1, ok, 0x8000);
    } else {
        ObjRecClearFlags_1c3dc0(gEventContext->unk0, 1, ok, 0x8000);
    }
    if (flag == 0) {
        ok = 1;
        if (arg1 >= 3) {
            ok = ScriptGetInt_2490f0(arg0);
        }
        if (ok != 0) {
            obj = ((s32)ObjRecGetLiveObject_1c4a90(gEventContext->unk0, EventCastGetObjId_24c160(tbl, id, 0)));
            if (obj != 0) {
                v.x = D_0047E7D0;
                v.y = D_0047E7D4;
                v.z = D_0047E7D8;
                v.w = D_0047E7DC;
                v.x = 0.0f;
                v.y = 0.0f;
                v.z = 0.0f;
                ModelSetPos_151110(obj, (Vec3w *)&v);
            }
        }
    }
    return 1;
}
