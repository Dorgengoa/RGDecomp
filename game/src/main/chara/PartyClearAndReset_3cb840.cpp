#include "types.h"

/* six zero stores then a C++ VIRTUAL TAIL CALL at slot 0x1C = index 5.
   mwcc lays data members BEFORE the vptr, so the members are reached
   through a plain struct to keep the vptr at offset 0. */

struct D3CB840 {
    u8  pad000[0x168];
    s32 m168;
    u8  pad16C[0x4];
    s32 m170;
    s32 m174;
    u8  pad178[0x4];
    s32 m17C;
};

extern "C" {
extern s32 D_00483890;
extern s32 D_00483894;
}

class V3CB840 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    void v5() { VCM0(void, 0x1C); }
};

extern "C" void PartyClearAndReset_3cb840(V3CB840 *o)
{
    D3CB840 *d = (D3CB840 *)o;

    D_00483890 = 0;
    D_00483894 = 0;
    d->m168 = 0;
    d->m170 = 0;
    d->m174 = 0;
    d->m17C = 0;
    o->v5();
}
