#include "types.h"
extern "C" {

class Obj {
public:
    u8 pad[0x190];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual s32 f();
};

s32 FrameGetWorldPos_148f30(s32, void *);
s32 ModelGetFrame_1511f0(s32, s32);
s32 ModelFindFrameIndexByName_151220(s32, s32);
s32 ScriptSlotStoreVec3_334790(s32, void *);
s32 ScriptSlotGetCodeAddr_334870(s32);
void ScriptSlotGetInt_3348b0(s32);
extern Obj *D_004826E0;

s32 ScriptCmdEffectGetNodePos_331bf0(s64 *arg0) {
    u8 sp40[0x10];
    s32 t17;
    s32 o;
    s32 r;

    ScriptSlotGetInt_3348b0((s32)arg0++);
    t17 = ScriptSlotGetCodeAddr_334870((s32)arg0++);
    if (D_004826E0 == NULL) {
        return 0;
    }
    o = D_004826E0->f();
    if (o == 0) {
        return 0;
    }
    r = ModelGetFrame_1511f0(o, ModelFindFrameIndexByName_151220(o, t17));
    if (r == 0) {
        return 0;
    }
    FrameGetWorldPos_148f30(r, &sp40);
    ScriptSlotStoreVec3_334790((s32)arg0, &sp40);
    return 1;
}

}
