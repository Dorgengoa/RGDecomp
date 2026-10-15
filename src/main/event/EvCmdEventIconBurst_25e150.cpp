#include "types.h"
#include "vec.h"

class Obj {
public:
    u8 pad[0xC0];
    virtual void d8();
    virtual void dC();
    virtual void d10();
    virtual void d14();
    virtual void v18(Mtx4 *);
};

extern "C" {
void VecNormalize_13bd90(Vec4 *, Vec4 *);
void VecScale_13be00(Vec4 *, Vec4 *, f32);
void MtxMulVec4_13c900(Vec4 *, Mtx4 *, Vec4 *);
Obj *ObjRecGetLiveObject_1c3bc0(void *, s32);
f32 TaggedGetFloat_26a280(s64 *);
s32 ScriptGetInt_26a2a0(s64 *);
void EventIconSpawnGlobal_278ba0(s32, Vec4 *, Vec4 *, s32);
extern u8 *D_00481F78;
}

extern "C" s32 EvCmdEventIconBurst_25e150(s64 *arg0, s32 arg1)
{
    Vec4 pos;
    Vec4 dir;
    Mtx4 m;
    s32 r;
    s32 id;
    s32 n;
    s32 k;
    s32 i;
    Obj *o;

    id = ScriptGetInt_26a2a0(arg0++);
    n = ScriptGetInt_26a2a0(arg0++);
    pos.x = TaggedGetFloat_26a280(arg0++);
    pos.y = TaggedGetFloat_26a280(arg0++);
    pos.z = TaggedGetFloat_26a280(arg0++);
    *(s32 *)&pos.w = 0;
    o = ObjRecGetLiveObject_1c3bc0(D_00481F78, *(s32 *)(D_00481F78 + 0x4344));
    o->v18(&m);
    if (n > 5) {
        n = 5;
    }
    k = 0;
    if (arg1 >= 6) {
        k = ScriptGetInt_26a2a0(arg0);
    }
    for (i = 0; i < n; i++) {
        r = i % 3;
        if (r == 0) {
            dir.x = 0.0f;
            dir.y = 0.0f;
            dir.z = 0.0f;
            dir.w = 0.0f;
        } else if (r == 1) {
            dir.y = 0.0f;
            dir.x = 1.0f;
            dir.z = 0.0f;
            dir.w = 0.0f;
        } else if (r == 2) {
            dir.y = 0.0f;
            dir.x = -1.0f;
            dir.z = 0.0f;
            dir.w = 0.0f;
        }
        MtxMulVec4_13c900(&dir, &m, &dir);
        dir.y = 0.0f;
        VecNormalize_13bd90(&dir, &dir);
        VecScale_13be00(&dir, &dir, 0.5f);
        dir.y = 5.0f;
        EventIconSpawnGlobal_278ba0(id, &pos, &dir, k);
        k += 10;
    }
    return 1;
}
