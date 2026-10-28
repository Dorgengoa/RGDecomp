/* rgp:protos */
#line 1
#include "types.h"

/* jalr $25 (see jalr-is-cpp-virtual lever) -- not reachable from the plain-C
   function-pointer-struct spelling that sibling src/s45a/ModelCtor_195470.c uses
   (that unit is parked with the same 3-word register residue). Virtual call
   is on an EMBEDDED SUB-OBJECT: `lw $25,0xF0($16) / lw $25,0x10($25) / jalr;
   addiu $4,$16,0x10` means `this` = arg0+0x10, vptr at arg0+0xF0, so the
   class (relative to that embedded this) has pad[0xE0] before the vptr;
   slot 0x10 -> N=(0x10-8)/4=2. */

extern "C" void MotionListInit_1726f0(void *);

class VE {
public:
    u8 pad000[0xE0];
    VC_VPTR_MEMBER;
    
    s32 v2(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x10, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

struct Obj00195470 {
    u8 pad0[0xF0];
    void *unkF0;
    u8 pad_F4[0x1B0 - 0xF4];
    void *unk1B0;
};

struct VTable00195470 {
    u8 pad0[0x10];
    void (*unk10)(void *self);
};

extern "C" VTable00195470 D_0046FFA0;
extern "C" u8 D_0046FFC0[];
extern "C" u8 D_00470440[];
extern "C" u8 D_00470690[];

extern "C" Obj00195470 *ModelObjBaseCtor_1954e0(Obj00195470 *arg0, int rgp_a1, int rgp_a2, int rgp_a3)
{
    arg0->unk1B0 = D_0046FFC0;
    arg0->unkF0 = &D_0046FFA0;
    ((VE *)((u8 *)arg0 + 0x10))->v2((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    arg0->unk1B0 = D_00470440;
    arg0->unk1B0 = D_00470690;
    MotionListInit_1726f0((u8 *)arg0 + 0x1F0);
    return arg0;
}
