#include "types.h"

/* lane N4: the round-2 M2 destructor family shape, with TWO bitfield
   inserts at 0x7A instead of one (bf1 = 0 then bf2 = 1).
   vptr at 0x00, second vptr at 0x88; virtual slot 0x4C = 8 + 4*17. */

extern "C" u8 D_004714E0[];
extern "C" u8 D_00471F60[];
extern "C" u8 D_00472250[];
extern "C" u8 D_00476C30[];
extern "C" u8 D_00476B90[];
extern "C" u8 D_00476C04[];
extern "C" u8 D_00476A30[];
extern "C" u8 D_00476AA4[];

extern "C" void MemStackCtor_14e030(void *);
extern "C" void ArenaCtxClear_370650(void *);

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v17() { VCM0(void, 0x4C); }
    u8 pad004[0x76];
    u8 bf0 : 1;
    u8 bf1 : 1;
    u8 bf2 : 1;
    u8 bf3 : 5;
};

extern "C" void *DataTableCtor_3f85f0(VE *o)
{
    *(void **)((u8 *)o + 0x00) = D_004714E0;
    *(void **)((u8 *)o + 0x00) = D_00471F60;
    MemStackCtor_14e030((u8 *)o + 0x14);
    ArenaCtxClear_370650((u8 *)o + 0x6C);
    o->v17();
    *(void **)((u8 *)o + 0x88) = D_00472250;
    *(void **)((u8 *)o + 0x88) = D_00476C30;
    *(void **)((u8 *)o + 0x00) = D_00476B90;
    *(void **)((u8 *)o + 0x88) = D_00476C04;
    *(void **)((u8 *)o + 0x00) = D_00476A30;
    *(void **)((u8 *)o + 0x88) = D_00476AA4;
    o->v17();
    o->bf1 = 0;
    o->bf2 = 1;
    return o;
}
