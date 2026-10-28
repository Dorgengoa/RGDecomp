/* rgp:protos */
#line 1
#include "types.h"

class VE73D0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void act(s32 a, s32 b, s32 c) { VCM(void, (void *, s32, s32, s32), 0x1A0, a, b, c); }
};

extern "C" {
s32 GetEventObjMgr_2d1960();
s32 EvSpawnChrMonographs_2e91e0(s32, s32, f32, f32);
void VariantSetS32_36f040(s32, s32, s32);
VE73D0 *ObjMgrFindFiltered_3bb190(s32, s32, s32, s32, s32, s32, s32, s32);
extern void *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;
}

extern "C" void ScriptFnSpawnChrMonographs_3d73d0(s32 arg0) {
    s32 temp_2_2;
    VE73D0 *temp_2;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    temp_2 = ObjMgrFindFiltered_3bb190((*(s32 *)((u8 *)(D_00483960) + 0x1C)), 0x2EE1, 1, 1, 0, 0, 0, 0);
    if (temp_2 != NULL) {
        temp_2->act(0x1F, 1, 1);
        temp_2_2 = GetEventObjMgr_2d1960();
        if (temp_2_2 != 0) {
            EvSpawnChrMonographs_2e91e0(temp_2_2, (*(s32 *)((u8 *)(temp_2) + 0xC)), -1.0f, -1.0f);
        }
    }
    VariantSetS32_36f040(arg0, 1, 1);
}
