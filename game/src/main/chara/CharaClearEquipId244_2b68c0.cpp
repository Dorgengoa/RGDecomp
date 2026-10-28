/* PARK (round 0, not attempted): m2c fails with "Unable to determine jump
   table for jr instruction" - needs the .rodata jump table read alongside
   the raw asm and a manual switch reconstruction. Not started. */
/* s49m: MATCH (multi-section, multicheck.py) */
#include "types.h"
#undef NULL
#define NULL 0

class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void f3D4(s32 a0) { VCM(void, (void *, s32), 0x3D4, a0); }
    s32 f3D8() { return VCM0(s32, 0x3D8); }
};

typedef struct Ent {
    u8 pad0[0x14];
    s16 unk14;
    s16 unk16;
} Ent;

extern "C" s32 D_00482370;
extern "C" s32 D_00482364;
extern "C" void MenuChoiceCursorSet_29c180(s32, s32, s32);
extern "C" Ent *UiEntryListFindByTag_28ea40(s32, s32);
extern "C" u8 *GetGameData_1fede0(void);
extern "C" s32 MenuGetCursorIndex_29fa80(s32);
extern "C" void MenuChoiceDim_29c130(s32, s32);
extern "C" s32 StateFlagTest_3ccd70(s32, s32);
extern "C" s32 PartyGetSlotId_3c3120(s32, s32);
extern "C" VObj *PartyGetSlotChara_3c2fb0(s32, s32);

extern "C" void CharaClearEquipId244_2b68c0(VObj *o)
{
    o->f3D4(-1);
}

extern "C" s32 func_002B68C0_e1(u8 *o)
{
    Ent *a;
    u8 *g;
    s32 c;
    VObj *x;

    MenuChoiceCursorSet_29c180(D_00482370, *(s16 *)(o + 0x12), 1);
    a = UiEntryListFindByTag_28ea40(D_00482364, 0x13);
    g = GetGameData_1fede0();
    c = MenuGetCursorIndex_29fa80(D_00482370);
    if (a->unk14 == 0 || a->unk16 == 0) {
        MenuChoiceDim_29c130(D_00482370, 1);
        if (a->unk14 == 0 && a->unk16 == 0 && StateFlagTest_3ccd70(*(s32 *)(g + 0x10), 0xB6) != 0
            && PartyGetSlotId_3c3120(*(s32 *)(g + 0x18), c) == 0) {
            MenuChoiceDim_29c130(D_00482370, 0);
        }
    } else {
        x = PartyGetSlotChara_3c2fb0(*(s32 *)(g + 0x18), c);
        if (x->f3D8() == 0) {
            MenuChoiceDim_29c130(D_00482370, 1);
        }
    }
    return 1;
}
