#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct SObj0025E390 SObj0025E390;
typedef struct SVtbl0025E390 SVtbl0025E390;

struct SVtbl0025E390 {
    u8 pad0[0x60];
    s32 (*unk60)(SObj0025E390 *);
};

struct SObj0025E390 {
    SVtbl0025E390 *vtbl;
};

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
} CtxObj0025E390;

CtxObj0025E390 *GetGameData_1fede0(...);                     /* extern */
s32 MesMgrGetSlotWin_266af0(s32);                              /* extern */
s32 ScriptGetInt_26a2a0(s32);                              /* extern */
void MesWinSetStrVar_276a00(s32, s32, s32);                   /* extern */
SObj0025E390 *CharaMgrPoolFindById_3a8c60(s32, s32);                /* extern */

class VC_0 {
public:
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual s32 f();
};
s32 EvCmdMesWinSetCharaName_25e390(s64 *arg0) {
    s32 temp_2;
    s32 temp_16_2;
    s32 temp_17;
    SObj0025E390 *temp_2_2;

    temp_2 = MesMgrGetSlotWin_266af0(ScriptGetInt_26a2a0((s32)arg0++));
    if (temp_2 == 0) {
        return 0;
    }
    temp_16_2 = ScriptGetInt_26a2a0((s32)arg0++);
    temp_17 = ScriptGetInt_26a2a0((s32)arg0);
    temp_2_2 = CharaMgrPoolFindById_3a8c60(GetGameData_1fede0()->unk14, temp_17);
    if (temp_2_2 == NULL) {
        return 0;
    }
    MesWinSetStrVar_276a00(temp_2, temp_16_2 - 1, ((VC_0 *)(temp_2_2))->f());
    return 1;
}

}
