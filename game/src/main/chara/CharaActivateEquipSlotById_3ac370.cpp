/* rgp:protos */
#line 1
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {
typedef s32 (*FN)();


s32 EquipSlotSetGaugeClamped_39ffa0(s32, s32, int, int);                             /* extern */
s32 EquipSlotGetAbilityType_3a0720(s32);                              /* extern */
s32 EquipSlotGetRecId_3a0760(s32);                              /* extern */
extern s32 D_00483824;

extern "C++" { class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template <class... VcA> s32 f(VcA... vc_va) { return VCM_FN(s32, (void *, ...), 0x47C)((void *)this, vc_va...); }
}; }
s32 CharaActivateEquipSlotById_3ac370(void *arg0, s32 arg1) {
    s32 p;
    s32 found;
    s32 i;

    if (arg1 < 0) {
        return 0;
    }
    if (D_00483824 == 0) {
        return 0;
    }
    found = 0;
    for (i = 0; i < 0xA; i++) {
        p = (s32)((u8 *)arg0 + (i * 0x28) + 0x308);
        if (arg1 == EquipSlotGetRecId_3a0760(p)) {
            found = p;
            break;
        }
    }
    if (found == 0) {
        return 0;
    }
    if (((unsigned char)EquipSlotGetAbilityType_3a0720(found)) == 2) {
        ((VC_0 *)(arg0))->f();
        (*(s32 *)((u8 *)(arg0) + 0x498)) = found;
        EquipSlotSetGaugeClamped_39ffa0(found, -1, 0, 0);
        return 1;
    }
    return 0;
}

}
