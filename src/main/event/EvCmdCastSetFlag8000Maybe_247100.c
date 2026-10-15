#include "types.h"

typedef struct Vec3w {
    f32 x, y, z, w;
} Vec3w;

typedef struct Ctx {
    s32 unk0;
    s32 unk4;
} Ctx;


void ModelSetPos_151110(s32, Vec3w *);
void ObjRecClearFlags_1c3dc0(s32, s32, s32, s32);
void ObjRecSetFlags_1c3e00(s32, s32, s32, s32);
s32 ObjRecGetLiveObject_1c4a90(s32, s32);
s32 ScriptGetCodeAddr_249050(void);
s32 ScriptGetInt_2490f0(s64 *);
s32 EventCastFindKeyByName_24bb50(s32, s32);
s32 EventCastGetObjId_24c160(s32, s32);
extern f32 D_0047E7D0;
extern f32 D_0047E7D4;
extern f32 D_0047E7D8;
extern f32 D_0047E7DC;
extern Ctx *gEventContext;

s32 EvCmdCastSetFlag8000Maybe_247100(s64 *arg0, s32 arg1)
{
    s32 id;
    s32 tbl;
    s32 flag;
    s32 ok;
    s32 obj;
    volatile Vec3w v;

    arg0++;
    tbl = gEventContext->unk4 + 0x60;
    id = EventCastFindKeyByName_24bb50(tbl, ScriptGetCodeAddr_249050());
    flag = ScriptGetInt_2490f0(arg0++);
    ok = EventCastGetObjId_24c160(tbl, id);
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
            obj = ObjRecGetLiveObject_1c4a90(gEventContext->unk0, EventCastGetObjId_24c160(tbl, id));
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
