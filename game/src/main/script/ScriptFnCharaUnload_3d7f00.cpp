/* rgp:protos */
#line 1
#include "types.h"

class C3d {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f2b4(s32 a0) { VCM(void, (void *, s32), 0x2B4, a0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f438(s32 a0) { VCM(void, (void *, s32), 0x438, a0); }
};

extern "C" {
void CharaUnloadById_2f3090(s32, s32);
void VariantSetS32_36f040(s32, s32, s32);
s16 VariantGetS16_36fcc0(s32);
C3d *ObjFindById_3bb3a0(s32, s32);
extern void *D_00483960;
extern s32 D_00483964;
}

extern "C" void ScriptFnCharaUnload_3d7f00(s32 arg0, s32 pad, s32 cnt, s32 id)
{
    s32 h;
    C3d *obj;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL || D_00483964 == 0) {
        return;
    }
    if (id == 0 || cnt <= 0) {
        return;
    }
    h = VariantGetS16_36fcc0(id);
    obj = ObjFindById_3bb3a0(*(s32 *)((u8 *)D_00483960 + 0x1C), h);
    if (obj == NULL) {
        return;
    }
    CharaUnloadById_2f3090(h, 0);
    obj->f2b4(0);
    obj->f438(1);
    VariantSetS32_36f040(arg0, 1, 1);
}
