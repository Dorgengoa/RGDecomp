/* rgp:protos */
#line 1
#pragma optimize_for_size on
#pragma optimization_level 3
#include "types.h"
class Obj0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    s32 get34(s32 a0) { return VCM(s32, (void *, s32), 0x34, a0); }
    
    
    u8 * get40() { return VCM0(u8 *, 0x40); }
    
    
    
    void set50(u8 * a0, s32 a1, int rgp_fwd3 = 0) { VCM(void, (void *, u8 *, s32, int), 0x50, a0, a1, rgp_fwd3); }
    s32 prio54(s32 a0) { return VCM(s32, (void *, s32), 0x54, a0); }
    u8 pad4[0x7A - 4];
    u8 flags7A;
    u8 pad7B;
    s16 unk7C;
    u8 pad7E[4];
    s16 unk82;
    u8 *unk84;
};

static inline bool isz(s32 x)
{
    return !(x != 0);
}

extern "C" s32 DataTableBuildHashIndex_3686c0(Obj0 *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    s32 n;
    s32 cnt;
    u8 *bp;
    s32 mask;
    s32 i;
    s32 total;
    s32 j;
    s32 item;
    s32 prio;
    s32 rem;
    s32 *slot;
    s32 k;
    s32 *q;
    s32 m;

    if (((u64)((u64)arg0->flags7A << 0x3D) >> 0x3F) == 0) {
        return 0;
    }
    n = arg0->unk7C;
    cnt = 0;
    bp = arg0->unk84;
    mask = 1;
    for (i = 0; i < n;) {
        if (!(*bp & mask)) {
            cnt++;
        }
        i++;
        if (i % 8 == 0) {
            bp++;
            mask = 1;
        } else {
            mask <<= 1;
        }
    }
    total = n + cnt;
    arg0->unk82 = total;
    arg0->set50(bp, cnt, (int)(long)(rgp_a3));
    for (j = 0; j < n; j++) {
        item = arg0->get34(j);
        prio = arg0->prio54(item);
        prio &= 0xFFFF;
        rem = total - prio;
        slot = (s32 *)(arg0->get40() + ((u32)prio & 0xFFFF) * 4);
        while (!isz(*slot) && rem > 0) {
            if (prio < (arg0->prio54(*slot) & 0xFFFF)) {
                k = 0;
                q = slot;
                while (!isz(*q) && rem > 0) {
                    q++;
                    rem--;
                    k++;
                }
                for (m = 0; m < k; m++) {
                    *q = q[-1];
                    q--;
                }
                break;
            }
            slot++;
            rem--;
        }
        *slot = item;
    }
    return total != 0;
}
