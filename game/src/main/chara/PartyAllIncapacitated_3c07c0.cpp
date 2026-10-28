#include "types.h"

class C {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f45() { return VCM0(s32, 0xBC); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f216() { return VCM0(s32, 0x368); }
};

struct O {
    u8 pad0[0x4B4];
    u8 x4B4;
};

extern "C" {
s32 PartyCountReserve_3c1c20(u8 *, s32, s32);
s32 PartyCountMembers_3c2010(u8 *, s32, s32);
C *CharaMgrPoolFindById_3a8c60(s32, s32);
extern u8 *D_00483890;
}

extern "C" s32 PartyAllIncapacitated_3c07c0(u8 *arg0, s32 arg1) {
    s32 n;
    s32 id;
    s32 i;
    C *o;
    s32 k;

    if (arg1 != 0) {
        n = PartyCountMembers_3c2010(arg0, 1, 1);
    } else {
        k = PartyCountMembers_3c2010(arg0, 1, 1);
        n = k + PartyCountReserve_3c1c20(arg0, 1, 1);
    }
    for (i = 0; i < n; i++) {
        if (D_00483890 == 0) {
            o = 0;
        } else {
            if (i < 0 || i >= 10) {
                id = -1;
            } else {
                k = PartyCountMembers_3c2010(arg0, 1, 1);
                if (i < k) {
                    id = *(s16 *)(arg0 + 0x190 + i * 2);
                } else if (i < k + 7) {
                    id = *(s16 *)(arg0 + 0x196 + (i - k) * 2);
                } else {
                    id = -1;
                }
            }
            if (id < 0) {
                o = 0;
            } else {
                o = CharaMgrPoolFindById_3a8c60(*(s32 *)(D_00483890 + 0x14), id);
            }
        }
        if (o != 0 && o->f216() == 0 && !(((O *)o)->x4B4 & 1) && o->f45() != 0) {
            return 0;
        }
    }
    return 1;
}
