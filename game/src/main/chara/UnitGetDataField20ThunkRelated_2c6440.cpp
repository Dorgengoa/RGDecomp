/* rgp:protos */
#line 1
#include "types.h"

extern "C" s32 ScriptSlotGetInt_2cc9c0(s32);
extern "C" void ScriptSlotStoreIntRef_2cc900(s32, s32);
extern "C" s32 PartyCollectLiveMemberIds_2cd6e0(s32 *);
extern "C" s32 AiCollectTargetIds_2cd530(s32 *);
extern "C" s32 D_004DB928[4];

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
};

extern "C" s32 __attribute__((naked)) UnitGetDataField20ThunkRelated_2c6440(VE *o)
{ __asm__ volatile("movl 4(%esp), %eax\n\t" "movl 0(%eax), %eax\n\t" "jmp *852(%eax)"); 

}

extern "C" s32 func_002C6450(s64 *arg0)
{
    s32 buf[0x80] __attribute__((aligned(16)));
    s32 r = ScriptSlotGetInt_2cc9c0((s32)arg0++);
    s32 lv = D_004DB928[0];
    s32 n = 0;
    switch (r) {
    case 0x100:
        n = PartyCollectLiveMemberIds_2cd6e0(buf);
        break;
    case 0x101:
        n = AiCollectTargetIds_2cd530(buf);
        break;
    case 0x102:
        if (lv <= 11) n = PartyCollectLiveMemberIds_2cd6e0(buf);
        else n = AiCollectTargetIds_2cd530(buf);
        break;
    case 0x103:
        if (lv <= 11) n = AiCollectTargetIds_2cd530(buf);
        else n = PartyCollectLiveMemberIds_2cd6e0(buf);
        break;
    }
    ScriptSlotStoreIntRef_2cc900((s32)arg0, n);
    return 1;
}
