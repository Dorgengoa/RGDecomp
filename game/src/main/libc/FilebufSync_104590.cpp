/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_rebuildlogicals off

/* lane N4 family: FilebufSync_104590 / WFilebufSync_105090 (172 B each, byte-identical
   listings).  C++ `bool` unit (round-2 M1 lever: `daddiu $18,$0,0x1`);
   the virtual is slot 0x34 = 8 + 4*11 off a vptr at 0x00. */

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    s32 v11(s32 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0x34, a0, rgp_fwd2, rgp_fwd3); }
    u8 pad004[0xC];
    u32 f10;
    u32 f14;
    u8 pad018[4];
    void *f1C;
};

extern "C" s32 Fflush_12f590(void *);

extern "C" s32 FilebufSync_104590(VE *self, int rgp_a1, int rgp_a2, int rgp_a3)
{
    bool ret;
    bool okA;
    bool found;

    ret = true;
    okA = ret;
    if (self->f1C != 0) {
        found = false;
        if (self->f14 > self->f10) {
            if (self->v11(-1, (int)(long)(rgp_a2), (int)(long)(rgp_a3)) == -1) {
                found = true;
            }
        }
        if (!found) {
            okA = false;
        }
    }
    if (!okA) {
        if (Fflush_12f590(self->f1C) == 0) {
            ret = false;
        }
    }
    return -(s32)ret;
}
