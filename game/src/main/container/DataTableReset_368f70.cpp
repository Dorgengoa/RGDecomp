/* rgp:protos */
#line 1
#include "types.h"

class Obj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    void v20() { VCM0(void, 0x20); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    int v5C() { return VCM0(int, 0x5C); }

    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    u8 unk14[0x64];
    s16 unk78;
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 pad7B;
    u8 pad7C[4];
    s16 unk80;

    void reset();
};

extern "C" void MemStackInit_14d810(void *, s32, s32);
extern "C" s16 D_004830FC;

extern "C" int DataTableReset_368f70(Obj *arg0)
{ int rgp_v0;
    D_004830FC = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    MemStackInit_14d810(arg0->unk14, 0, 0);
    arg0->unk78 = 0;
    arg0->unk8 = 0;
    arg0->b0 = 0;
    arg0->unk80 = 4;
    arg0->unk4 = 0;
    arg0->b1 = 0;
    arg0->b2 = 0;
    arg0->v20();
    rgp_v0 = arg0->v5C();
return rgp_v0; }
