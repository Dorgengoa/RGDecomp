/* rgp:protos */
#line 1
#include "types.h"

/* retail's indirect call is `lw $25,0xDC($16) / lw $25,0x14($25) / jalr $25`
   -- a jalr on $25/$t9 is C++ virtual dispatch (see jalr-is-cpp-virtual lever).
   vptr offset K=0xDC, slot 0x14 = 8 + 4*3 -> the 4th declared virtual (0-based
   N=3), returning bool (the `andi $2,$2,0xFF` at the call site). */

class VE_002f9320 {
public:
    u8 pad000[0xD0];
    u32 unkD0;
    u8 padD4[0xDC - 0xD4];
    VC_VPTR_MEMBER;
    
    
    bool v3() { return (vc_u8)VCM0(vc_u32, 0x14) != 0; }
};

extern "C" void TargetRefResolve_2e5ed0(void *, int);

extern "C" s32 EvTargetPointObjResolveTarget_2f9320(VE_002f9320 *arg0, int rgp_a1)
{
    u32 val;

    TargetRefResolve_2e5ed0((u8 *)arg0 + 0xA0, (int)rgp_a1);
    if (arg0->v3() != 0) {
        val = arg0->unkD0 | 0x02000000;
    } else {
        val = arg0->unkD0 & 0xFDFFFFFF;
    }
    arg0->unkD0 = val;
    return 1;
}
