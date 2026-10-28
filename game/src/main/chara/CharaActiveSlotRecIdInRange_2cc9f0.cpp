#include "types.h"
extern "C" {
class VC {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x470); }
};

extern s32 GetGameData_1fede0(void);
extern s32 EquipSlotGetRecId_3a0760(s32);
extern VC *CharaMgrPoolFindById_3a8c60(s32, s32);

s32 CharaActiveSlotRecIdInRange_2cc9f0(s32 arg0, s32 arg1) {
    VC *obj;
    s32 p;
    s32 i;
    s32 t;

    obj = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)GetGameData_1fede0() + 0x14), arg0);
    if (obj == 0) {
        return 0;
    }
    p = obj->f();
    if (p == 0) {
        return 0;
    }
    for (i = 0; i < 3; i++) {
        if (arg1 + i == EquipSlotGetRecId_3a0760(p)) {
            return 1;
        }
    }
    return 0;
}

}
