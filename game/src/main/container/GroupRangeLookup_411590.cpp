/* rgp:protos */
#line 1
#include "types.h"

/* jalr $25: vptr at offset 0; slot 0x70 = 8 + 4*26 -> the 27th declared
   virtual. */
struct Obj {
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * v26(s32 i) { return VCM(void *, (void *, s32), 0x70, i); }
    u8  pad004[0x98 - 4];
    s16 m98;
    s16 m9A;
};

extern "C" Obj * GroupFindByKey_4117d0(void *, int);

extern "C" void *GroupRangeLookup_411590(void *a, void *b, s16 idx)
{
    Obj *p;
    bool ok;

    if (idx < 0) {
        return 0;
    }
    p = GroupFindByKey_4117d0((void *)a, (int)b);
    if (p != 0) {
        ok = idx >= p->m98;
        if (ok) {
            ok = idx <= p->m9A;
        }
        if (ok) {
            return p->v26(idx);
        }
    }
    return 0;
}
