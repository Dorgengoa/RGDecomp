#include "types.h"
#undef NULL
#define NULL 0
extern "C" {
extern void *GetGameData_1fede0(void);
extern void ScriptSlotStoreIntRef_2cc900(s32 arg0, s32 arg1);
extern s32 CharaSysStateUnitFlag7EBit3Related_3a38e0(s32 arg0);
extern s32 D_004DB928[0x100];
}
class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f4c8() { return VCM0(s32, 0x4C8); }
};
extern "C" VObj *CharaMgrPoolFindById_3a8c60(s32 arg0, s32 arg1);

extern "C" s32 AiCmdCharaHasGaugeLevel_2c5be0(s32 arg0)
{
    void *ctx;
    VObj *o;
    s32 id;

    ctx = GetGameData_1fede0();
    id = D_004DB928[0];
    if (CharaSysStateUnitFlag7EBit3Related_3a38e0(*(s32 *)((u8 *)ctx + 0x20)) == 0) {
        ScriptSlotStoreIntRef_2cc900(arg0, 0);
        return 1;
    }
    o = CharaMgrPoolFindById_3a8c60(*(s32 *)((u8 *)ctx + 0x14), id);
    if (o == NULL) {
        ScriptSlotStoreIntRef_2cc900(arg0, 0);
        return 1;
    }
    if (o->f4c8() != 0) {
        ScriptSlotStoreIntRef_2cc900(arg0, 1);
        return 1;
    }
    ScriptSlotStoreIntRef_2cc900(arg0, 0);
    return 1;
}
