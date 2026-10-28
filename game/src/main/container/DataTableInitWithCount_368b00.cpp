/* rgp:protos */
#line 1
#include "types.h"

extern "C" void ArenaCtxInit_370610(void *, void *);

/* Signature pinned by already-closed callers (e.g.
   src/p20x/WorldSubsysInit_3f6890.cpp): extern "C" s32 DataTableInitWithCount_368b00(s32, s32) --
   first arg is a `this`-style object address, second a count. Both
   indirect calls in the body assemble as `jalr $25` -- a C++ virtual
   member call (see jalr-is-cpp-virtual lever), not reachable from any
   plain-C function-pointer spelling. Slot offset = 8 + 4*N for the
   Nth (0-based) declared virtual: 0x20 -> N=6, 0x5C -> N=21. Dummy
   virtuals declared-never-defined so no vtable/undefined-symbol noise. */

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    s32 v6() { return VCM0(s32, 0x20); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v21() { return VCM0(s32, 0x5C); }
};

extern "C" s32 DataTableInitWithCount_368b00(s32 objAddr, s32 count)
{
    VE *obj;

    obj = (VE *)objAddr;
    if (count == 0) {
        return 0;
    }
    *(s32 *)((u8 *)obj + 0x10) = count;
    ArenaCtxInit_370610((u8 *)obj + 0x6C, (void *)count);
    obj->v6();
    return obj->v21();
}
