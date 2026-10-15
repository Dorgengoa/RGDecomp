#include "types.h"
extern "C" {
#pragma peephole off

extern void FrameGetWorldPos_148f30(s32, f32 *);
extern s32 ModelGetRootFrame_1511a0(s32);
extern void ScriptSlotStoreVec3_334790(s32, f32 *);
extern s32 ScriptSlotGetInt_3348b0(s32);
extern f32 D_0047F510;
extern f32 D_0047F514;
extern f32 D_0047F518;
extern f32 D_0047F51C;
}
class C331 {
public:
    u8 pad[0x190];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual s32 f();
};
extern "C" C331 *D_004826E0;

extern "C" s32 ScriptCmdEffectGetRootPos_331f90(s64 *arg0, s32 arg1)
{
    f32 sp[4];
    s32 temp_2;

    if (arg1 != 4) {
        return 0;
    }
    ScriptSlotGetInt_3348b0((s32)arg0++);
    sp[0] = D_0047F510;
    sp[1] = D_0047F514;
    sp[2] = D_0047F518;
    sp[3] = D_0047F51C;
    if (D_004826E0 != NULL) {
        temp_2 = D_004826E0->f();
        if (temp_2 != 0) {
            FrameGetWorldPos_148f30(ModelGetRootFrame_1511a0(temp_2), sp);
        }
    }
    ScriptSlotStoreVec3_334790((s32)arg0, sp);
    return 1;
}
