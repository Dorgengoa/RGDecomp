#include "types.h"

extern "C" {
struct Base351 { u8 pad0[0xD0]; s32 unkD0; u8 padd4[0xDC - 0xD4]; };
class Obj00351CC0 : public Base351 {
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual s32 v3();
    u8 pade0[0xE8 - 0xE0];
    s32 unkE8;
    s32 unkEC;
    u8 padf0[0x13C - 0xF0];
    s32 unk13C;
    u8 pad140[0x148 - 0x140];
    u8 unk148;
    u8 pad149[0x158 - 0x149];
    s16 unk158;
    s16 unk15A;
};

s32 NodeObjFindChildByName_195040(s32, s32);
s32 TargetRefGetMapObj_2e7050(s32);
void EvObjResolveTarget_2f9a60();
void EvM05ChangePlayStart_351de0(Obj00351CC0 *);
s32 EvM05ChangeGetPlayState_352020(Obj00351CC0 *);
s32 EvM05ChangeGetModelName_352040(Obj00351CC0 *);
void EvTargetBindNode_3526d0(s32, s32);

s32 EvM05ChangeResolveTarget_351cc0(Obj00351CC0 *arg0) {
    s32 temp_2;
    s32 var_18;
    s32 var_17;
    s32 var_3;

    EvObjResolveTarget_2f9a60();
    arg0->unk13C = 0;
    temp_2 = TargetRefGetMapObj_2e7050((s32) arg0 + 0xA0);
    if (temp_2 != 0) {
        arg0->unk13C = NodeObjFindChildByName_195040(temp_2, EvM05ChangeGetModelName_352040(arg0));
    }
    var_18 = arg0->unkE8;
    var_17 = 0;
    while (var_17 < arg0->unkEC) {
        EvTargetBindNode_3526d0(var_18, arg0->unk13C);
        var_17 += 1;
        var_18 += 0x140;
    }
    if (!(arg0->v3() & 0xFF)) {
        var_3 = arg0->unkD0 & 0xFDFFFFFF;
    } else {
        var_3 = arg0->unkD0 | 0x02000000;
    }
    arg0->unkD0 = var_3;
    if ((var_3 & 0x02000000)) {
        if (EvM05ChangeGetPlayState_352020(arg0) == -1) {
            EvM05ChangePlayStart_351de0(arg0);
        }
    } else {
        arg0->unk158 = -1;
        arg0->unk15A = 0;
        arg0->unk148 = 0;
    }
    return 1;
}

}
