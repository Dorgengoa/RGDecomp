/* rgp:protos */
#line 1
#include "types.h"

/* retail's two calls go through `jalr $25`, which only a real C++ virtual
   dispatch reaches (see jalr-is-cpp-virtual lever). vptr at node+0, slot
   0x70 => 26 dummy virtuals ahead of the real one (slot = 8 + 4*N). */
class VE003ebfc0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v26(s32 a, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(s32, (void *, s32, int, int), 0x70, a, rgp_fwd2, rgp_fwd3); }
};

typedef struct MidFUN_003ebfc0 {
    u8 pad0[0x18];
    VE003ebfc0 *unk18;
} MidFUN_003ebfc0;

typedef struct InnerFUN_003ebfc0 {
    u8 pad0[0x34];
    MidFUN_003ebfc0 *unk34;
} InnerFUN_003ebfc0;

typedef struct ObjFUN_003ebfc0 {
    u8 pad0[0x8];
    InnerFUN_003ebfc0 *unk8;
    u8 pad0C[0x2C - 0xC];
    u8 unk2C;
} ObjFUN_003ebfc0;

extern "C" s32 WorldOnPartyNavGraphChanged_3ebfc0(ObjFUN_003ebfc0 *arg0, s32 arg1, s32 arg2, int rgp_a3)
{
    InnerFUN_003ebfc0 *inner;
    VE003ebfc0 *node;

    if (arg0->unk2C & 1) {
        return 0;
    }
    inner = arg0->unk8;
    if (inner == NULL) {
        return 0;
    }
    node = inner->unk34->unk18;
    node->v26(arg2, (int)(long)(arg2), (int)(long)(rgp_a3));
    node = arg0->unk8->unk34->unk18;
    node->v26(arg1);
    return 1;
}
