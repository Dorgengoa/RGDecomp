/* rgp:protos */
#line 1
#include "types.h"
#pragma optimization_level 3

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f(s16 x0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s16, int, int), 0x70, x0, rgp_fwd2, rgp_fwd3); }
};

extern "C" {
extern s32 Fprintf_12f9a0(s32, void *);
extern void Abort_12de80(void);
extern s16 *AbilityListFindById_3f5780(s32, s32);
extern s32 AbilityDataMatchesKind_3f57f0(s32,s32), AbilityDataMatchesType_3f57d0(s32,s32);
extern u8 *D_00449858[0x100];
extern u8 D_00465ED0[];
extern u8 *D_0048381C;
}

class Bit3AD940 {
public:
    s64 *p;
    u32 n;
    Bit3AD940(s64 *pp, u32 nn) : p(pp), n(nn) {}
    s64 Get()
    {
        s64 *q = p;
        u32 k = n;
        if (k >= 0x40) {
            Fprintf_12f9a0(*(s32 *)(D_00449858[0] + 0xC), D_00465ED0);
            Abort_12de80();
        }
        return *q & (1LL << k);
    }
};

extern "C" s32 CharaCountAbilitiesFilteredMaybe_3add30(u8 *arg0, s32 arg2, s32 arg3, s32 arg4)
{
s16 *p3;
s32 t2;
s32 cnt;
s32 j;
s32 val;
s16 *node;
u32 idx;
    if (D_0048381C == 0 || (p3 = *(s16 **)(arg0 + 0x230)) == 0) {
        return 0;
    }
    if ((t2 = (*(VC_0 **)(*(u8 **)(D_0048381C + 0x44) + 0xC))->f(*p3, (int)(long)(arg3), (int)(long)(arg4))) == 0) {
        return 0;
    }
    idx = arg4 & 0xFF;
    cnt = 0;
    if (arg2 < 0 && arg3 < 0) {
        u64 v = ((u64 *)(arg0 + 0x2E0))[idx];
        while (v != 0) {
            s32 k;
            switch (v & 0xF) {
            case 1: case 2: case 4: case 8:
                k = 1; break;
            case 3: case 5: case 6: case 9: case 10: case 12:
                k = 2; break;
            case 7: case 11: case 13: case 14:
                k = 3; break;
            case 15:
                k = 4; break;
            case 0:
            default:
                k = 0; break;
            }
            cnt += k;
            v >>= 4;
        }
        return cnt;
    }
    arg0 += idx * 8;
    for(j=0;j<64;j++) {
      if(Bit3AD940((s64 *)(arg0+0x2E0),j).Get()) {
        node=AbilityListFindById_3f5780(t2,j+1);
        if(node!=0 && (val=*(s32 *)(node+2))!=0 && AbilityDataMatchesKind_3f57f0(val,arg2)!=0 && AbilityDataMatchesType_3f57d0(val,arg3)!=0){
          cnt++;
        }
      }
    }
    return cnt;
}
