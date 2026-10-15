#include "types.h"

/* lane N4: the round-2 M2 destructor family shape, with TWO bitfield
   inserts at 0x7A instead of one (bf1 = 0 then bf2 = 1).
   vptr at 0x00, second vptr at 0x88; virtual slot 0x4C = 8 + 4*17. */

extern u8 D_004714E0[];
extern u8 D_00471F60[];
extern u8 D_00472250[];
extern u8 D_0047CCD0[];
extern u8 D_0047CC30[];
extern u8 D_0047CCA4[];
extern u8 D_0047CB90[];
extern u8 D_0047CC04[];

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
    u8 bf2 : 1;
    u8 bf3 : 5;
};

extern "C" void *DataTableCtor_4298b0(VE *o)
{
    *(void **)((u8 *)o + 0x00) = D_004714E0;
    *(void **)((u8 *)o + 0x00) = D_00471F60;
    MemStackCtor_14e030((u8 *)o + 0x14);
    ArenaCtxClear_370650((u8 *)o + 0x6C);
    o->v17();
    *(void **)((u8 *)o + 0x88) = D_00472250;
    *(void **)((u8 *)o + 0x88) = D_0047CCD0;
    *(void **)((u8 *)o + 0x00) = D_0047CC30;
    *(void **)((u8 *)o + 0x88) = D_0047CCA4;
    *(void **)((u8 *)o + 0x00) = D_0047CB90;
    *(void **)((u8 *)o + 0x88) = D_0047CC04;
    o->v17();
    o->bf1 = 1;
    o->bf2 = 1;
    return o;
}
