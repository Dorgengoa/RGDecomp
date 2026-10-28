/* rgp:protos */
#line 1
#include "types.h"

/* Same "vptr at object offset +0" shape used across the corpus (see
   src/s13d/CharaMgrPoolUpdate_3a8490.cpp, src/s13o/CharaGetEquippedWeapon_3acd40.cpp, etc.) -- `arg0` is
   directly the polymorphic object; m2c's `(*arg0)->` is its usual confused
   spelling of a plain `arg0->method()`, and its "(arg0, ...)" first argument
   on two of the calls is really just the (implicit) `this`, not a real
   parameter. Four slots used: +0x14C, +0x174, +0x180, +0x18C -> virtual
   indices 81, 91, 94, 97. */

class V {
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
    /* +0x060 */ 
    /* +0x064 */ 
    /* +0x068 */ 
    /* +0x06C */ 
    /* +0x070 */ 
    /* +0x074 */ 
    /* +0x078 */ 
    /* +0x07C */ 
    /* +0x080 */ 
    /* +0x084 */ 
    /* +0x088 */ 
    /* +0x08C */ 
    /* +0x090 */ 
    /* +0x094 */ 
    /* +0x098 */ 
    /* +0x09C */ 
    /* +0x0A0 */ 
    /* +0x0A4 */ 
    /* +0x0A8 */ 
    /* +0x0AC */ 
    /* +0x0B0 */ 
    /* +0x0B4 */ 
    /* +0x0B8 */ 
    /* +0x0BC */ 
    /* +0x0C0 */ 
    /* +0x0C4 */ 
    /* +0x0C8 */ 
    /* +0x0CC */ 
    /* +0x0D0 */ 
    /* +0x0D4 */ 
    /* +0x0D8 */ 
    /* +0x0DC */ 
    /* +0x0E0 */ 
    /* +0x0E4 */ 
    /* +0x0E8 */ 
    /* +0x0EC */ 
    /* +0x0F0 */ 
    /* +0x0F4 */ 
    /* +0x0F8 */ 
    /* +0x0FC */ 
    /* +0x100 */ 
    /* +0x104 */ 
    /* +0x108 */ 
    /* +0x10C */ 
    /* +0x110 */ 
    /* +0x114 */ 
    /* +0x118 */ 
    /* +0x11C */ 
    /* +0x120 */ 
    /* +0x124 */ 
    /* +0x128 */ 
    /* +0x12C */ 
    /* +0x130 */ 
    /* +0x134 */ 
    /* +0x138 */ 
    /* +0x13C */ 
    /* +0x140 */ 
    /* +0x144 */ 
    /* +0x148 */ 
    /* +0x14C */ void slot14C(s32 arg1, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, s32, int, int), 0x14C, arg1, rgp_fwd2, rgp_fwd3); }
    /* +0x150 */ 
    /* +0x154 */ 
    /* +0x158 */ 
    /* +0x15C */ 
    /* +0x160 */ 
    /* +0x164 */ 
    /* +0x168 */ 
    /* +0x16C */ 
    /* +0x170 */ 
    /* +0x174 */ void slot174(s32 arg1) { VCM(void, (void *, s32), 0x174, arg1); }
    /* +0x178 */ 
    /* +0x17C */ 
    /* +0x180 */ void slot180(s32 arg1) { VCM(void, (void *, s32), 0x180, arg1); }
    /* +0x184 */ 
    /* +0x188 */ 
    /* +0x18C */ int slot18C(s32 arg1, s32 arg2) { return VCM(int, (void *, s32, s32), 0x18C, arg1, arg2); }
};

typedef struct Arg1FUN_003d13d0 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 arr[6];   /* accessed as (u8*)arg1 + i*4 + 0xC, i.e. an s32[6] at +0xC */
} Arg1FUN_003d13d0;

extern "C" void InsectSetStats_3d13d0(V *arg0, Arg1FUN_003d13d0 *arg1, int rgp_a2, int rgp_a3)
{
    s32 i;

    arg0->slot14C(arg1->unk0, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    arg0->slot174(arg1->unk4);
    arg0->slot180(arg1->unk8);
    i = 0;
    do {
        arg0->slot18C(i, arg1->arr[i]);
        i += 1;
    } while (i < 6);
}
