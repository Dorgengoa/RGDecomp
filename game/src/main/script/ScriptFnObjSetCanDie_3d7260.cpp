#include "types.h"

class V003D7260 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void x38() { VCM0(void, 0xA0); }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f260(bool a0) { VCM(void, (void *, bool), 0x418, a0); }
};

struct D003D7260 {
    u8 pad0[0x1C];
    s32 unk1C;
};

extern "C" {
extern void VariantSetS32_36f040(s32, s32, s32);
extern s32 VariantGetS32_36fb30(s32);
extern V003D7260 *ObjMgrFindByEncounterSlotIdMaybe_3bb0c0(s32, s32);
extern V003D7260 *ObjMgrFindFiltered_3bb190(s32, s32, s32, s32, s32, s32, s32, s32);
extern D003D7260 *D_00483960;
extern s32 D_00483964;
extern s32 D_00483968;
}

extern "C" void ScriptFnObjSetCanDie_3d7260(s32 arg0, s32 arg1, s32 arg2, s32 arg3)
{
    V003D7260 *o;
    s32 a;
    bool flag;
    s32 r;
    s32 b;

    if (arg0 == 0) {
        return;
    }
    VariantSetS32_36f040(arg0, 0, 1);
    if (D_00483960 == NULL) {
        return;
    }
    if (D_00483964 == 0 || D_00483968 == 0) {
        return;
    }
    if (arg3 == 0 || arg2 <= 0) {
        return;
    }
    a = VariantGetS32_36fb30(arg3);
    arg3 += 0x38;
    flag = true;
    if (arg2 >= 2) {
        flag = VariantGetS32_36fb30(arg3) != 0;
        arg3 += 0x38;
    }
    r = 0;
    b = -1;
    if (arg2 >= 3) {
        r = VariantGetS32_36fb30(arg3);
    }
    if (r == 1) {
        b = a;
        a = -1;
    }
    if (r == 0) {
        o = ObjMgrFindByEncounterSlotIdMaybe_3bb0c0(D_00483960->unk1C, a);
    } else {
        o = ObjMgrFindFiltered_3bb190(D_00483960->unk1C, b, 1, 1, 0, 0, 0, 0);
    }
    if (o != NULL) {
        o->f260(!flag);
    }
    VariantSetS32_36f040(arg0, 1, 1);
}
