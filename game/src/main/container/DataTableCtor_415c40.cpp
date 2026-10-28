#include "types.h"

/* MWo3 C++ destructor template, lane M2 (session 18).
   vptr at 0x00 and a second vptr at 0x88; the virtual call is
   slot 0x4C = 8 + 4*17, i.e. the 18th declared virtual.
   The bitfield insert at 0x7A is a 1-bit field at bit 1. */

extern "C" u8 D_004714E0[];
extern "C" u8 D_00471F60[];
extern "C" u8 D_00472250[];
extern "C" u8 D_00479D70[];
extern "C" u8 D_00479CD0[];
extern "C" u8 D_00479D44[];
extern "C" u8 D_0047AA10[];
extern "C" u8 D_0047AA84[];

extern "C" void MemStackCtor_14e030(void *);
extern "C" void ArenaCtxClear_370650(void *);

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v17() { VCM0(void, 0x4C); }
    u8 pad004[0x76];
    u8 bf0 : 1;
    u8 bf1 : 1;
    u8 bf2 : 6;
};

extern "C" void *DataTableCtor_415c40(VE *o)
{
    *(void **)((u8 *)o + 0x00) = D_004714E0;
    *(void **)((u8 *)o + 0x00) = D_00471F60;
    MemStackCtor_14e030((u8 *)o + 0x14);
    ArenaCtxClear_370650((u8 *)o + 0x6C);
    o->v17();
    *(void **)((u8 *)o + 0x88) = D_00472250;
    *(void **)((u8 *)o + 0x88) = D_00479D70;
    *(void **)((u8 *)o + 0x00) = D_00479CD0;
    *(void **)((u8 *)o + 0x88) = D_00479D44;
    *(void **)((u8 *)o + 0x00) = D_0047AA10;
    *(void **)((u8 *)o + 0x88) = D_0047AA84;
    o->v17();
    o->bf1 = 1;
    return o;
}
