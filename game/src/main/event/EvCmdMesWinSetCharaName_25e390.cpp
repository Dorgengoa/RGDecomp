/* rgp:protos */
#line 1
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

CtxObj0025E390 * GetGameData_1fede0(void);                     /* extern */
s32 MesMgrGetSlotWin_266af0(s32);                              /* extern */
s32 ScriptGetInt_26a2a0(s32);                              /* extern */
void MesWinSetStrVar_276a00(s32, s32, s32);                   /* extern */
SObj0025E390 *CharaMgrPoolFindById_3a8c60(s32, s32);                /* extern */

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x60); }
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
