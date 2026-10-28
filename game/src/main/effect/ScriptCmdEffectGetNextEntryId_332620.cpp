/* rgp:protos */
#line 1
#include "types.h"

class C_00332620 {
    u8 pad000[0x190];
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
    /* +0x044 */ s32 v44(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, int, int, int), 0x44, rgp_fwd1, rgp_fwd2, rgp_fwd3); }
};

struct Obj_00332620;

extern "C" C_00332620 *D_004826E0;
extern "C" void ScriptSlotStoreIntRef_3347f0(Obj_00332620 *o, s16 v);

extern "C" s32 ScriptCmdEffectGetNextEntryId_332620(Obj_00332620 *o, s32 mode, int rgp_a2, int rgp_a3)
{
    s32 r;

    if (mode != 1) {
        return 0;
    }
    r = D_004826E0->v44((int)(long)(mode), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    ScriptSlotStoreIntRef_3347f0(o, (s16)r);
    return 1;
}
