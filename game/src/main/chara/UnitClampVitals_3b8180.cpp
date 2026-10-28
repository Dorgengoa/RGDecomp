/* rgp:protos */
#line 1
/* MATCH (s41m). Stale pre-match note follows -- PARK 1/3: length-wrong (69w vs retail 72w). Fixed an 'empty array must be last member' struct layout bug (zero-size pad field) that blocked compilation. */
#include "types.h"
#undef NULL
#define NULL 0
extern "C" {

typedef struct VT1A4 {
    u8 pad19C[0x19C];
    s32 (*unk19C)(void *, s32);
    s32 (*unk1A0)(void *, s32, s32, s32);
    s32 (*unk1A4)(void *, s32);
} VT1A4;

s32 UnitClampVitalsGate_3b8a00(void);
extern u8 *D_00483818;

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x1A4, x0); }
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0, s32 x1, s32 x2) { return VCM(s32, (void *, s32, s32, s32), 0x1A0, x0, x1, x2); }
};
class VC_2 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x1A4, x0); }
};
class VC_3 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s32 x0) { return VCM(s32, (void *, s32), 0x19C, x0); }
};
s32 UnitClampVitals_3b8180(u8 *arg0) {
    u8 var_3;
    u16 temp_2;
    u16 temp_3_2;
    u32 temp_3;

    if (!(UnitClampVitalsGate_3b8a00() & 0xFF)) {
        return 0;
    }
    if (!(*(s32 *)(arg0 + 0x14) != 0)) {
        var_3 = 0;
        if ((D_00483818 != NULL) && (*(u8 *)(*(u8 **)(D_00483818 + 0x20) + 0x24C) & 1)) {
            var_3 = 1;
        }
        if (var_3) {
            *(u32 *)(arg0 + 0x14) = 0;
            ((VC_1 *)(arg0))->f(1, 1, 1);
        } else {
            *(u32 *)(arg0 + 0x14) = 1;
            ((VC_0 *)(arg0))->f(1);
        }
    } else {
        ((VC_2 *)(arg0))->f(1);
    }
    temp_3 = *(u32 *)(arg0 + 0x20);
    if (temp_3 < (u32) *(s32 *)(arg0 + 0x14)) {
        *(u32 *)(arg0 + 0x14) = temp_3;
    }
    if (((VC_3 *)(arg0))->f(1) != 0) {
        *(u32 *)(arg0 + 0x14) = 0;
    }
    temp_3_2 = *(u16 *)(arg0 + 0x18);
    if (!((s32) temp_3_2 >= 0)) {
        *(u16 *)(arg0 + 0x18) = 0;
    } else {
        temp_2 = *(u16 *)(arg0 + 0x26);
        if ((s32) temp_2 < (s32) temp_3_2) {
            *(u16 *)(arg0 + 0x18) = temp_2;
        }
    }
    return 1;
    return 0;
}

}
