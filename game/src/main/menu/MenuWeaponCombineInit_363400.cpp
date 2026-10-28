#include "types.h"

typedef struct Mgr { u8 pad[0x18]; s32 f18; } Mgr;
typedef struct Obj {
    u8 pad[0x5C];
    s32 f5C;
    s8 f60;
    s8 f61;
    u8 pad62[2];
    s32 f64;
    s32 f68;
    s32 f6C;
    s32 f70;
    s16 f74;
    u8 pad76[2];
    s32 f78;
    s32 f7C;
    s8 f80;
    s8 f81;
    s8 f82;
    s8 f83;
    u8 pad84[0x10];
    s8 f94;
    s8 f95;
    s8 f96;
} Obj;
class Ent {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 v48() { return VCM0(s32, 0x48); }
};

extern "C" {
extern Mgr *GetGameData_1fede0(void);
extern s32 MsgTableLookup_28aa30(s32, s32);
extern void MenuWeaponCombineShowMsg_362490(Obj *, s32, s32);
extern s32 MenuWeaponCombineIsFeedableMaybe_3627a0(Obj *, Ent *);
extern Ent *InvFindByInvId_3c87d0(s32, s32, s32);
extern s32 InvMakeIdFromCategory_3c88b0(s32, s32, s32, s32, s32);
extern s32 ItemIsWeapon_3d46c0(Ent *);
extern s32 D_004659E8[4];
extern s32 D_004659F0[4];
extern s32 D_004659F8[4];
extern s32 D_004823D8;
extern s8 D_00483060;
extern s8 D_00483064;
extern s8 D_00483068;
extern s8 D_0048306C;
extern s32 D_00483078;
}

extern "C" void MenuWeaponCombineInit_363400(Obj *arg0, s8 arg1) {
    Mgr *mgr;
    s32 found;
    s32 row;
    s32 h1;
    s32 w1;
    s32 rows;
    s32 col;
    s32 end;
    Ent *e;

    arg0->f5C = 0x78;
    arg0->f94 = 0;
    arg0->f95 = 6;
    arg0->f96 = 2;
    arg0->f60 = 0;
    arg0->f64 = -1;
    arg0->f68 = -1;
    arg0->f6C = -1;
    arg0->f70 = 0;
    arg0->f7C = 0;
    arg0->f80 = 0;
    arg0->f81 = 0;
    arg0->f82 = 0;
    D_00483060 = 0;
    D_00483064 = 0;
    D_00483068 = 0;
    D_0048306C = 0;
    arg0->f61 = 0;
    arg0->f78 = 0;
    D_00483078 = 0;
    mgr = GetGameData_1fede0();
    found = 0;
    row = 0;
    h1 = D_004659F8[0] - 1;
    w1 = D_004659F0[0] - 1;
    rows = D_004659E8[0];
    for (; row < rows; row++) {
        col = InvMakeIdFromCategory_3c88b0(mgr->f18, 0, row, 0, 0);
        end = InvMakeIdFromCategory_3c88b0(mgr->f18, 0, row, w1, h1);
        for (; col < end + 1; col++) {
            e = InvFindByInvId_3c87d0(mgr->f18, col, 0);
            if (e != 0 && ItemIsWeapon_3d46c0(e) != 0 && MenuWeaponCombineIsFeedableMaybe_3627a0(arg0, e) != 0 && e->v48() == 0) {
                found = 1;
                break;
            }
        }
        if (found) break;
    }
    if (arg1 == 0) {
        arg0->f94 = 1;
        if (found) {
            MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x3F8), 0);
            arg0->f96 = 2;
        } else {
            MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x3F9), 0);
            arg0->f96 = 2;
        }
    } else {
        arg0->f94 = 8;
        if (found) {
            MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x403), 0);
            arg0->f96 = 2;
        } else {
            MenuWeaponCombineShowMsg_362490(arg0, MsgTableLookup_28aa30(D_004823D8, 0x40D), 0);
            arg0->f96 = 2;
        }
    }
    arg0->f74 = arg1;
    arg0->f83 = 0;
}
