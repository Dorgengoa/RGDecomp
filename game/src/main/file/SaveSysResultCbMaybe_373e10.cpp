#include "types.h"

/* retail's node->unk0->unk18(...) call goes through `jalr $25` -- only a real
   C++ virtual dispatch reaches that (jalr-is-cpp-virtual lever). vptr at
   node+0, slot 0x18 => 4 dummy virtuals ahead of the real one. */
class VE00373e10 {
public:
    VC_VPTR_MEMBER;
    
    
    
    s32 v4(s32 arg1, s32 arg2) { return VCM(s32, (void *, s32, s32), 0x18, arg1, arg2); }
};

typedef struct ObjFUN_00373e10 {
    u8 pad0[0x4EE];
    s16 unk4EE;
} ObjFUN_00373e10;

extern "C" VE00373e10 *GetGameData_1fede0(void);
extern "C" void SaveResultSetFromDataError_374070(ObjFUN_00373e10 *arg0);
extern "C" void SysMsgFillFromSaveRecMaybe_3e4d10(VE00373e10 *arg0, void *arg1, s32 arg2);
extern "C" s32 SlotRecordFindById_3e4e80(VE00373e10 *arg0, s16 arg1);

extern "C" u8 D_004E9080[12]; /* oversize: keeps mwcc off $gp-relative, matching retail's lui/lo */

extern "C" s32 SaveSysResultCbMaybe_373e10(ObjFUN_00373e10 *arg0, s32 arg1, s32 arg2)
{
    VE00373e10 *node;

    node = GetGameData_1fede0();
    SysMsgFillFromSaveRecMaybe_3e4d10(node, D_004E9080, SlotRecordFindById_3e4e80(node, arg0->unk4EE));
    node->v4(arg1, arg2);
    SaveResultSetFromDataError_374070(arg0);
    return 1;
}
