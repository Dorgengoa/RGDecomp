#include "types.h"

extern "C" void ArenaCtxInit_370610(void *);

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
    virtual s32 v0();
    virtual s32 v1();
    virtual s32 v2();
    virtual s32 v3();
    virtual s32 v4();
    virtual s32 v5();
    virtual s32 v6();
    virtual s32 v7();
    virtual s32 v8();
    virtual s32 v9();
    virtual s32 v10();
    virtual s32 v11();
    virtual s32 v12();
    virtual s32 v13();
    virtual s32 v14();
    virtual s32 v15();
    virtual s32 v16();
    virtual s32 v17();
    virtual s32 v18();
    virtual s32 v19();
    virtual s32 v20();
    virtual s32 v21();
};

extern "C" s32 DataTableInitWithCount_368b00(s32 objAddr, s32 count)
{
    VE *obj;

    obj = (VE *)objAddr;
    if (count == 0) {
        return 0;
    }
    *(s32 *)((u8 *)obj + 0x10) = count;
    ArenaCtxInit_370610((u8 *)obj + 0x6C);
    obj->v6();
    return obj->v21();
}
