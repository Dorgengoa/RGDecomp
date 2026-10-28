/* rgp:protos */
#line 1
#include "types.h"

/* retail's node->unk0->unk504(...) call goes through `jalr $25` -- only a real
   C++ virtual dispatch reaches that. vptr at node+0, slot 0x504 => 319 dummy
   virtuals ahead of the real one (slot = 8 + 4*N). */
class VE003e65b0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v319(s32 arg1, s32 arg2) { VCM(void, (void *, s32, s32), 0x504, arg1, arg2); }
};

typedef struct ObjFUN_003e65b0 {
    u8 pad0[0x14];
    s32 unk14;
    u8 pad18[0x1C - 0x18];
    s32 unk1C;
    s32 unk20;
} ObjFUN_003e65b0;

extern "C" VE003e65b0 * CharaMgrPoolFindById_3a8c60(s32, int);
extern "C" void ObjMgrAttackChainEnd_3ba540(s32 arg0, s32 arg1, s32 arg2);
extern "C" void CharaSysAttackChainEnd_3a1090(s32);

extern "C" s32 GameDataAttackChainEnd_3e65b0(ObjFUN_003e65b0 *arg0, s32 arg1, s32 arg2)
{
    VE003e65b0 *node;
    s32 v;

    node = CharaMgrPoolFindById_3a8c60(arg0->unk14, (int)arg1);
    if (node != NULL) {
        node->v319(arg1, arg2);
    }
    ObjMgrAttackChainEnd_3ba540(arg0->unk1C, arg1, arg2);
    v = arg0->unk20;
    if (v != 0) {
        CharaSysAttackChainEnd_3a1090(v);
    }
    return 1;
}
