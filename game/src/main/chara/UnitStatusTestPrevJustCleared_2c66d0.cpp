#include "types.h"

struct Bits48 {
    u64 w;
};

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    Bits48 v127() { Bits48 vc_r; VCM_FN(void, (Bits48 *, void *), 0x204)(&vc_r, (void *)this); return vc_r; }
};

struct BitRef {
    Bits48 *p;
    s32 pos;
};

struct Reent {
    u8 pad00[0xC];
    void *stderr_;
};

extern "C" Reent *const D_00449858;
extern "C" char D_0045CB40[];
extern "C" void Fprintf_12f9a0(void *stream, const char *fmt);
extern "C" void Abort_12de80(void);

extern "C" s32 UnitStatusTestPrevJustCleared_2c66d0(Obj *self, s32 n)
{
    BitRef r __attribute__((aligned(16)));
    const Bits48 &tmp = self->v127();

    r.p = (Bits48 *)&tmp;
    r.pos = n;
    if ((u32)n >= 0x30) {
        Fprintf_12f9a0(D_00449858->stderr_, D_0045CB40);
        Abort_12de80();
    }
    return ((*(Bits48 *volatile *)&r.p)->w & (1ULL << n)) != 0;
}
