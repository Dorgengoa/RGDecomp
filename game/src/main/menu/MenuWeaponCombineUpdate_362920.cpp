#include "types.h"

typedef struct Ctx2920 {
    u8 pad0[0x5C];
    s32 m5C;
    u8 m60;
    u8 m61;
    u8 pad62[2];
    s32 m64;
    s32 m68;
    s32 m6C;
    s32 m70;
    u8 pad74[4];
    s32 m78;
    s32 m7C;
    u8 m80;
    u8 m81;
    u8 m82;
    u8 pad83;
    s32 m84;
    s32 m88;
    s32 m8C;
    u8 pad90[4];
    s8 m94;
    s8 m95;
    s8 m96;
} Ctx2920;

typedef struct Dsc2920 {
    u8 pad0[2];
    s8 m2;
    u8 pad3;
    s16 m4;
    u8 pad6[2];
    s16 m8;
} Dsc2920;

class VObj2920 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v48() { return VCM0(s32, 0x48); }
};

typedef struct Obj2920 {
    VObj2920 v;
    u8 pad4[6];
    u8 b0:1;
    u8 b1:7;
    u8 padB[5];
    Dsc2920 *m10;
} Obj2920;

class VList2920 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v70(s32 a0) { return VCM(s32, (void *, s32), 0x70, a0); }
};

typedef struct Sub40_2920 {
    u8 pad0[8];
    VList2920 *m8;
} Sub40_2920;

typedef struct Sub8_2920 {
    u8 pad0[0x40];
    Sub40_2920 *m40;
} Sub8_2920;

typedef struct Chr2920 {
    u8 pad0[8];
    Sub8_2920 *m8;
    u8 padC[0xC];
    s32 m18;
} Chr2920;

typedef struct Pan2920 {
    u8 pad0[0x14];
    s16 m14;
    s16 m16;
} Pan2920;

typedef struct Sys2920 {
    u8 pad0[0x11];
    s8 m11;
} Sys2920;

typedef struct Ent2920 {
    u8 pad0[3];
    u8 p0:4;
    u8 f4:1;
    u8 p5:3;
    s16 m4;
} Ent2920;

typedef struct Buf2920 {
    u8 pad[0x24];
} Buf2920;

extern "C" {
void *memset(void *, s32, u32);
void Sprintf_1343b8(void *, s32, void *);
s32 PadIsHeld_183a20(void *, s32);
void SoundPlayDefault_1b9ae0(s32, s32, s32);
Chr2920 *GetGameData_1fede0(void);
Pan2920 *UiEntryListFindByTag_28ea40(s32, s32);
s32 MsgTableLookup_28aa30(s32, s32);
void StateMachineSetState_28ede0(s32, s32, s32);
void PlayMenuSe_289ef0(s32);
void UiFadeWidgetAlpha_290690(s32, s32, f32, f32, f32);
Ent2920 *MenuGetSelItem_2a02d0(Sys2920 *);
void MenuSetSelItem_2a02e0(Sys2920 *, Obj2920 *);
s32 MenuWeaponCombineAnimTickMaybe_361cd0(Ctx2920 *);
s32 MenuWeaponCombineStartAnim_362360(Ctx2920 *, s32);
void MenuWeaponCombineShowMsg_362490(Ctx2920 *, s32, s32);
void MenuWeaponCombineAutoHideTick_362700(Ctx2920 *);
s32 MenuWeaponCombineCanPickCellMaybe_3627f0(Ctx2920 *);
void MenuWeaponCombineGridRefreshMaybe_3619d0(Ctx2920 *, s32);
Ent2920 *WeaponCombineAddResult_3c3520(s32, Ent2920 *, u8 *, s32 *, u8 *);
s32 WeaponCombineCheck_3c3e30(s32, Obj2920 *, u8 *, u8 *, s32 *);
Obj2920 *InvFindByCategoryIndex_3c86e0(s32, s32, s32, s32, s32, s32);
s32 ItemIsWeapon_3d46c0(Obj2920 *);
s32 PartyFindItemHolder_3d4c20(Obj2920 *);
void ItemDefGetDisplayName_40e470(s32, Buf2920 *, s32);
extern u8 D_004B2570[];
extern u8 D_004E8F80[];
extern Sys2920 *D_00482374;
extern s32 D_004823D8;
extern s32 D_004823E4;
extern u8 D_00483060;
extern u8 D_00483064;
extern u8 D_00483068;
extern u8 D_0048306C;
extern u8 D_00483070;
extern u8 D_00483074;
extern s16 D_0048307C;
extern s16 D_00483080;
extern s16 D_00483084;
}

extern "C" s32 MenuWeaponCombineUpdate_362920(Ctx2920 *arg0, s32 key)
{
    Buf2920 buf __attribute__((aligned(16)));
    s32 sp98;
    u8 sp9F;
    u8 sp9E;
    s32 sp94;
    u8 sp9D;
    u8 sp9C;
    s32 r;
    Chr2920 *c;
    Obj2920 *o;
    Pan2920 *p;
    s32 x;
    bool redo;

    MenuWeaponCombineAutoHideTick_362700(arg0);
    r = MenuWeaponCombineAnimTickMaybe_361cd0(arg0);
    switch ((u8)arg0->m95) {
    case 8:
        if (arg0->m60 != 0) {
            break;
        }
        if (key == 2) {
            MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x400), 0);
            arg0->m94 = arg0->m95;
            arg0->m95 = 7;
            arg0->m96 = 2;
            r = 4;
            break;
        }
        if (key != 1) {
            break;
        }
        c = GetGameData_1fede0();
        p = UiEntryListFindByTag_28ea40(arg0->m88, 3);
        o = InvFindByCategoryIndex_3c86e0(c->m18, 0, D_00482374->m11, p->m14, p->m16, 0);
        if (o == 0) {
            return r;
        }
        if (ItemIsWeapon_3d46c0(o) == 0) {
            break;
        }
        if (o->v.v48() == 2) {
            if (MenuWeaponCombineStartAnim_362360(arg0, 3) == 0) {
                break;
            }
            MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x409), 0);
            arg0->m94 = arg0->m95;
            arg0->m95 = 6;
            arg0->m96 = 2;
            StateMachineSetState_28ede0(arg0->m8C, 0x13, 0);
        } else {
            MenuSetSelItem_2a02e0(D_00482374, o);
            MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x404), 0);
            arg0->m94 = 9;
            D_0048307C = 0;
            D_00483080 = 0;
            arg0->m95 = 6;
            arg0->m96 = 2;
        }
        break;
    case 1:
        if (arg0->m60 != 0) {
            break;
        }
        if (key == 2) {
            MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x400), 0);
            arg0->m94 = arg0->m95;
            arg0->m95 = 7;
            arg0->m96 = 2;
            r = 4;
            break;
        }
        if (key == 1) {
            if (MenuWeaponCombineCanPickCellMaybe_3627f0(arg0) != 0) {
                StateMachineSetState_28ede0(arg0->m8C, 0x11, 0);
            }
        }
        break;
    case 2:
        if (arg0->m60 != 0) {
            break;
        }
        if (key == 2) {
            MenuWeaponCombineStartAnim_362360(arg0, 4);
            break;
        }
        if (key == 1) {
            if (MenuWeaponCombineCanPickCellMaybe_3627f0(arg0) != 0) {
                arg0->m78 = 0;
                StateMachineSetState_28ede0(arg0->m8C, 0x11, 0);
            }
        }
        break;
    case 3:
        if (key == 2) {
            arg0->m95 = arg0->m94;
            arg0->m96 = 0;
            StateMachineSetState_28ede0(arg0->m8C, 0x13, 0);
            break;
        }
        if (key != 1) {
            break;
        }
        x = 0;
        c = GetGameData_1fede0();
        p = UiEntryListFindByTag_28ea40(arg0->m88, 3);
        o = InvFindByCategoryIndex_3c86e0(c->m18, 0, D_00482374->m11, p->m14, p->m16, 0);
        if (o == 0) {
            return r;
        }
        MenuSetSelItem_2a02e0(D_00482374, o);
        switch (UiEntryListFindByTag_28ea40(arg0->m88, 4)->m16) {
        case 0:
            {
                s32 v;
                D_00483060 = 0;
                D_00483064 = 0;
                D_00483068 = 0;
                D_0048306C = 0;
                D_00483070 = 0;
                D_00483074 = 0;
                sp9F = 0;
                sp9E = 0;
                sp98 = 0;
                redo = false;
                v = WeaponCombineCheck_3c3e30(c->m18, o, &sp9F, &sp9E, &sp98);
                if (sp9E != 0) {
                    D_00483064 = 1;
                }
                if (sp98 < 0) {
                    D_00483068 = 1;
                }
                if (v == 2) {
                    D_00483060 = 1;
                }
                if (v == 4) {
                    D_00483068 = 1;
                }
                if (v == 5) {
                    D_0048306C = 1;
                }
                if (v == 6) {
                    D_00483070 = 1;
                }
                if (v == -10) {
                    D_00483074 = 1;
                }
                switch (v) {
                case -10:
                case -2:
                case 1:
                case 2:
                case 4:
                case 5:
                case 6:
                    if ((u8)arg0->m94 == 2) {
                        x = 1;
                    }
                    if (MenuWeaponCombineStartAnim_362360(arg0, x) != 0) {
                        arg0->m64 = o->m10->m2;
                        arg0->m68 = o->m10->m4;
                        arg0->m6C = o->m10->m8;
                        o->b0 = true;
                        {
                            bool on = PartyFindItemHolder_3d4c20(o);
                            if (on) {
                                arg0->m81 = 1;
                            }
                        }
                        if (o->m10->m2 == 7) {
                            arg0->m82 = 1;
                        }
                    }
                    break;
                case -1:
                    redo = true;
                    break;
                case -4:
                    if (MenuWeaponCombineStartAnim_362360(arg0, 3) != 0) {
                        MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x3FE), 0);
                        arg0->m95 = 6;
                        arg0->m96 = 2;
                        r = 1;
                    }
                    break;
                case -6:
                    if (MenuWeaponCombineStartAnim_362360(arg0, 3) != 0) {
                        MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x410), 0);
                        arg0->m95 = 6;
                        arg0->m96 = 2;
                        r = 1;
                    }
                    break;
                case -7:
                    MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x402), 0);
                    arg0->m95 = 6;
                    arg0->m96 = 2;
                    r = 1;
                    break;
                case -8:
                    MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x414), 0);
                    arg0->m95 = 6;
                    arg0->m96 = 2;
                    r = 1;
                    break;
                case -9:
                    MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x416), 0);
                    arg0->m95 = 6;
                    arg0->m96 = 2;
                    r = 1;
                    break;
                case 0:
                    redo = true;
                    break;
                case -5:
                case -3:
                case 3:
                    break;
                }
                if (redo) {
                    if (MenuWeaponCombineStartAnim_362360(arg0, 3) != 0) {
                        MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x3FF), 0);
                        arg0->m95 = 6;
                        arg0->m96 = 2;
                        r = 1;
                    }
                }
                StateMachineSetState_28ede0(arg0->m8C, 0x2D, 0);
            }
            break;
        case 1:
            if (ItemIsWeapon_3d46c0(o) == 0) {
                break;
            }
            StateMachineSetState_28ede0(arg0->m8C, 0x2E, 0);
            arg0->m5C = 0;
            UiFadeWidgetAlpha_290690(arg0->m84, 0x1E7, 0.0f, -0.0625f, -1.0f);
            break;
        case 2:
            StateMachineSetState_28ede0(arg0->m8C, 0x2F, 0);
            arg0->m95 = arg0->m94;
            arg0->m96 = 0;
            break;
        }
        break;
    case 9:
        if (D_00483080 == 1) {
            MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, D_00483084), 0);
            arg0->m94 = 8;
            arg0->m95 = 6;
            arg0->m96 = 2;
            StateMachineSetState_28ede0(arg0->m8C, 9, 0);
            break;
        }
        if (PadIsHeld_183a20(D_004B2570, 0x20) != 0) {
            arg0->m94 = 8;
            arg0->m95 = 8;
            arg0->m96 = 0;
            UiFadeWidgetAlpha_290690(arg0->m84, 0x1E7, 0.0f, -0.0625f, -1.0f);
            r = 2;
            break;
        }
        {
            Ent2920 *e = MenuGetSelItem_2a02d0(D_00482374);
            Ent2920 *t;
            sp9D = 0;
            sp94 = 0;
            sp9C = 0;
            c = GetGameData_1fede0();
            t = WeaponCombineAddResult_3c3520(c->m18, e, &sp9D, &sp94, &sp9C);
            memset(D_004E8F80, 0, 0x20);
            if (t == 0) {
                if (D_00483080 != 0) {
                    break;
                }
                {
                    s32 k = 0x407;
                    if (sp9C) {
                        k = 0x41E;
                    }
                    MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, k), 0);
                }
                arg0->m94 = 8;
                arg0->m95 = 6;
                arg0->m96 = 2;
                StateMachineSetState_28ede0(arg0->m8C, 9, 0);
                break;
            }
            if (sp9D == 0) {
                PlayMenuSe_289ef0(0x20);
            }
            ItemDefGetDisplayName_40e470(c->m8->m40->m8->v70(t->m4), &buf, t->f4 != 0);
            D_00483084 = 0x41A;
            if (sp94 > 0) {
                D_00483084 = 0x41C;
            } else if (sp9D != 0) {
                D_00483084 = 0x41B;
            }
            Sprintf_1343b8(D_004E8F80, MsgTableLookup_28aa30(D_004823D8, 0x41D), &buf);
            MenuWeaponCombineShowMsg_362490(arg0, (s32)D_004E8F80, 0);
            arg0->m94 = arg0->m95;
            arg0->m95 = 6;
            arg0->m96 = 1;
            D_00483080 = 1;
        }
        break;
    case 6:
        if ((u32)(key - 1) < 2) {
            s32 t;
            arg0->m95 = arg0->m94;
            UiFadeWidgetAlpha_290690(arg0->m84, 0x1E7, 0.0f, -0.0625f, -1.0f);
            t = (u8)arg0->m96;
            r = 2;
            if (t == 1 || (t == 2 && key == 1)) {
                PlayMenuSe_289ef0(5);
            } else if (t == 2 && key == 2) {
                PlayMenuSe_289ef0(6);
            }
        }
        break;
    case 7:
        if (key == 1) {
            UiFadeWidgetAlpha_290690(arg0->m84, 0x1E7, 0.0f, -0.0625f, -1.0f);
            if (UiEntryListFindByTag_28ea40(arg0->m88, 0xD)->m14 == 0) {
                SoundPlayDefault_1b9ae0(D_004823E4, 2, 0);
                MenuWeaponCombineGridRefreshMaybe_3619d0(arg0, 0);
                StateMachineSetState_28ede0(arg0->m8C, 0x93, 0);
                break;
            }
            arg0->m95 = arg0->m94;
            r = 2;
            StateMachineSetState_28ede0(arg0->m8C, 9, 0);
        } else if (key == 2) {
            UiFadeWidgetAlpha_290690(arg0->m84, 0x1E7, 0.0f, -0.0625f, -1.0f);
            arg0->m95 = arg0->m94;
            r = 2;
            StateMachineSetState_28ede0(arg0->m8C, 9, 0);
        }
        break;
    case 0:
    case 4:
    case 5:
        break;
    }
    return r;
}
