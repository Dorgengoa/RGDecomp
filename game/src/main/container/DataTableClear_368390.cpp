/* rgp:protos */
#line 1
#include "types.h"

class C_00368390 {
public:
    /* +0x008 */ VC_VPTR_MEMBER;
    /* +0x00C */ 
    /* +0x010 */ 
    /* +0x014 */ 
    /* +0x018 */ 
    /* +0x01C */ 
    /* +0x020 */ 
    /* +0x024 */ 
    /* +0x028 */ 
    /* +0x02C */ 
    /* +0x030 */ 
    /* +0x034 */ 
    /* +0x038 */ 
    /* +0x03C */ 
    /* +0x040 */ 
    /* +0x044 */ 
    /* +0x048 */ 
    /* +0x04C */ 
    /* +0x050 */ 
    /* +0x054 */ 
    /* +0x058 */ 
    /* +0x05C */ 
    /* +0x060 */ void v60() { VCM0(void, 0x60); }
    /* +0x064 */ 
    /* +0x068 */ 
    /* +0x06C */ void v6C(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x6C, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

extern "C" void MemStackReset_14d830(void *p);

extern "C" void DataTableClear_368390(C_00368390 *o, int rgp_a1, int rgp_a2, int rgp_a3)
{
    o->v6C((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    o->v60();
    if (*(s16 *)((u8 *)o + 0x78) > 0) {
        MemStackReset_14d830((u8 *)o + 0x14);
    }
}
