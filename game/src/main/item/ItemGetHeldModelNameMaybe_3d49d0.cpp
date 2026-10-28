#include "types.h"
#pragma divbyzerocheck on
#pragma opt_propagation off

class Unit {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f5C() { return VCM0(s32, 0x5C); }
};

typedef struct {
    u8 pad0[0x10];
    u8 *p;
} A0;

extern "C" {
extern Unit *PartyGetLeaderChara_3c2820(s32);
extern s32 MainCharaIdToNumber_4016b0(s32);
extern void *memset(void *, s32, s32);
extern u8 *D_004838E8;
extern u8 D_00483900[16] __attribute__((section(".sdata")));
}
#define DD D_00483900

extern "C" void *ItemGetHeldModelNameMaybe_3d49d0(A0 *arg0, Unit *u)
{
    s64 c0;
    s64 c1;
    s64 c2;
    s32 n;
    u8 *p;
    u8 *q;
    void *ret;

    if (D_004838E8 == 0) {
        return 0;
    }
    if (arg0->p == 0) {
        return 0;
    }
    if (u == 0) {
        u = PartyGetLeaderChara_3c2820(*(s32 *)(D_004838E8 + 0x18));
    }
    memset(DD, 0, 0x10);
    c1 = 0;
    c2 = 0;
    n = 0;
    if (u != 0) {
        n = u->f5C();
    }
    c0 = 0x63;
    n = MainCharaIdToNumber_4016b0(n);
    if (n < 0) {
        c0 = 0;
        n = -1;
    }
    p = arg0->p;
    switch ((s8)p[2]) {
    case 4:
        switch (*(s16 *)(p + 4)) {
        case 0:
            c1 = 0x69;
            c2 = 0x74;
            break;
        default:
            c1 = 0;
            c2 = 0;
            break;
        }
        break;
    case 5:
        switch (*(s16 *)(p + 4)) {
        case 0x1F4: case 0x1F5:
            c1 = 0x69;
            c2 = 0x74;
            break;
        default:
            c1 = 0;
            c2 = 0;
            break;
        }
        break;
    }
    ret = 0;
    if ((s8)c0 != 0 && n >= 0 && (s8)c1 != 0 && (s8)c2 != 0) {
        DD[0] = c0;
        q = DD;
        q[1] = ((n / 100) % 10) + 0x30;
        q[2] = ((n / 10) % 10) + 0x30;
        q[4] = 0x5F;
        q[5] = c1;
        q[6] = c2;
        q[9] = 0;
        q[7] = 0x30;
        ret = DD;
        q[8] = 0x30;
        q[3] = (n % 10) + 0x30;
    }
    return ret;
}
