#include "types.h"

/* DataTableLoadResidentBinDefault_367fe0 -- 72 B, THREE entries.
 *   e0/e1 virtual tail call vptr 0, slot 0x10 (v2, four s32 args)
 *   e2 `return 1;` */

class VB {
public:
    VC_VPTR_MEMBER;
    
    void v2(s32 a0, s32 a1, s32 a2, s32 a3) { VCM(void, (void *, s32, s32, s32, s32), 0x10, a0, a1, a2, a3); }
};

extern "C" void DataTableLoadResidentBinDefault_367fe0(VB *o, s32 a, s32 b) { o->v2(a, b, 0, 0); }

extern "C" void func_00367FE0_e1(VB *o, s32 a, s32 b, s32 c) { o->v2(a, b, 0, c); }

extern "C" s32 func_00367FE0_e2(void) { return 1; }
