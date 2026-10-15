#include "types.h"

/* MWo3 C++ destructor template, lane M2 (session 18).
   vptr at 0x00 and a second vptr at 0x88; the virtual call is
   slot 0x4C = 8 + 4*17, i.e. the 18th declared virtual.
   The bitfield insert at 0x7A is a 1-bit field at bit 1. */

extern u8 D_004714E0[];
extern u8 D_00471F60[];
extern u8 D_00472250[];
extern u8 D_00479650[];
extern u8 D_004794F0[];
extern u8 D_00479564[];
extern u8 D_00479710[];
extern u8 D_00479784[];

extern "C" void MemStackCtor_14e030(void *);
extern "C" void ArenaCtxClear_370650(void *);

class VE {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    u8 pad004[0x76];
    u8 bf0 : 1;
    u8 bf1 : 1;
    u8 bf2 : 6;
};

extern "C" void *DataTableCtor_410430(VE *o)
{
    *(void **)((u8 *)o + 0x00) = D_004714E0;
    *(void **)((u8 *)o + 0x00) = D_00471F60;
    MemStackCtor_14e030((u8 *)o + 0x14);
    ArenaCtxClear_370650((u8 *)o + 0x6C);
    o->v17();
    *(void **)((u8 *)o + 0x88) = D_00472250;
    *(void **)((u8 *)o + 0x88) = D_00479650;
    *(void **)((u8 *)o + 0x00) = D_004794F0;
    *(void **)((u8 *)o + 0x88) = D_00479564;
    *(void **)((u8 *)o + 0x00) = D_00479710;
    *(void **)((u8 *)o + 0x88) = D_00479784;
    o->v17();
    o->bf1 = 0;
    return o;
}
