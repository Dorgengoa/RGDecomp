/* rgp:protos */
#line 1
#include "types.h"

class VE {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f460() { return VCM0(s32, 0x460); }
};

/* Stack locals are allocated in REVERSE declaration order, so `info` (sp+0x50)
   must be declared AFTER the 0x80-byte text buffer (sp+0x90).
   Indirect call: vtable at offset 0 of the returned object, slot 0x460. */


extern "C" s32 GetCharaDataMgr_1fdb70(void);
extern "C" s32 PcIdToResIndexMaybe_1f4f90(void *);
extern "C" s32 CharaPcResNameBuildMaybe_40dc60(s16 *);
extern "C" void Sprintf_1343b8(char *, char *, s32);
extern "C" void *GetGameData_1fede0(void);
extern "C" void *CharaMgrPoolFindByDataId_3a8a70(void *, void *, s32, s32, s32, s32, s32);
extern "C" void CharaPcBuildPath_1f4ef0(char *, s16 *);
extern "C" int CharaDataLoadSubRecById_1eda70(s32, void *);
extern "C" char D_0045B790[];

extern "C" int CharaPcLoadRequest_1f4db0(void *a0, void *a1, s16 *a2)
{
    char text[0x80] __attribute__((aligned(16)));   /* sp+0x90 */
    u8 info[0x38] __attribute__((aligned(16)));     /* sp+0x50 */
    s32 h;
    void *r;

    h = GetCharaDataMgr_1fdb70();
    *(s32 *)(info + 0x18) = 0;
    *(s32 *)(info + 0x08) = -1;
    *(s32 *)(info + 0x0C) = -1;
    *(s32 *)(info + 0x10) = -1;
    *(s32 *)(info + 0x14) = -1;
    *(s32 *)(info + 0x1C) = -1;
    *(s32 *)(info + 0x24) = -1;
    *(s32 *)(info + 0x30) = -1;
    *(s32 *)(info + 0x20) = 0;
    *(s32 *)(info + 0x28) = 0;
    *(s32 *)(info + 0x2C) = 0;
    *(s32 *)(info + 0x34) = 0;
    *(void **)(info + 0x00) = a1;
    *(s32 *)(info + 0x04) = 0;
    *(s32 *)(info + 0x1C) = PcIdToResIndexMaybe_1f4f90(a0);
    *(void **)(info + 0x14) = a1;
    *(s32 *)(info + 0x08) = 1;
    *(s32 *)(info + 0x0C) = 1;
    *(s32 *)(info + 0x10) = *a2;
    *(char **)(info + 0x18) = text;
    Sprintf_1343b8(text, D_0045B790, CharaPcResNameBuildMaybe_40dc60(a2));
    r = CharaMgrPoolFindByDataId_3a8a70(*(void **)((u8 *)GetGameData_1fede0() + 0x14), a0, 1, 1, 0, 0, 0);
    if (r != 0 && ((VE *)r)->f460() != 0) {
        CharaPcBuildPath_1f4ef0(text, a2);
        *(s32 *)(info + 0x34) = 1;
    }
    return CharaDataLoadSubRecById_1eda70(h, info);
}
