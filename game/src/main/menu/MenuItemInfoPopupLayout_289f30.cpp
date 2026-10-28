/* rgp:protos */
#line 1
#include "types.h"

class VC_0 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x70); }
    u8 pad4[0xC];
    s8 *x10;
};
class VC_1 {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f() { return VCM0(s32, 0x60); }
};

struct Args {
    s16 *x0;
    s16 *x4;
    s16 *x8;
    s16 *xC;
};

extern "C" {
void Sprintf_1343b8(void *, void *, s32);
u8 *GetGameData_1fede0();
void TextStyleInit_26c610(void *);
void FontMeasureString_26daf0(void *, void *, s32 *, s32 *);
void TextStyleSetFontType_26edf0(void *, s32);
void TextStyleAddSpacing_26f2b0(void *, s32, s32);
void UiLayoutStringGlyphs_28a800(s16 *, void *, s32, s16, s32);
void *MsgTableLookup_28aa30(s32, s32);
VC_1 *PoolGetUsedElem_36acb0(s32, s32);
s32 ItemIsInsectFood_3d45b0(VC_0 *);
s32 ItemIsWeapon_3d46c0(VC_0 *);
s32 ItemKindBelow4_3d4860(VC_0 *);
s32 ItemGetOwnerCharaId_3d4d50(VC_0 *, s32);
s32 ItemDefGetIconIndex_40e1b0(s8 *);
extern s16 D_00461060[14][3];
extern char D_004610B0[0x40];
extern s32 D_00481BBC;
extern char D_004822E0[8];

#pragma opt_propagation off
s32 MenuItemInfoPopupLayout_289f30(VC_0 *arg0, Args *arg1) {
    s32 spEC;
    s32 spE8;
    char spE0[8];
    u8 spA0[0x40] __attribute__((aligned(16)));
    s16 *p0;
    s16 *p4;
    s16 *pC;
    s16 *p8;
    s32 y;
    s32 id;
    s32 i;
    bool flag;
    s32 sel;
    void *name;

    p0 = arg1->x0;
    if (p0 == NULL) {
        return 0;
    }
    p4 = arg1->x4;
    if (p4 == NULL) {
        return 0;
    }
    pC = arg1->xC;
    if (pC == NULL) {
        return 0;
    }
    p8 = arg1->x8;
    if (p8 == NULL) {
        return 0;
    }
    y = 0x168;
    if (arg0->x10 == NULL) {
        return 0;
    }
    id = ItemDefGetIconIndex_40e1b0(arg0->x10);
    *pC = -1;
    *p8 = -1;
    *p4 = -1;
    for (i = 0; i < 14; i++) {
        if (id == D_00461060[i][0]) {
            s16 a;
            s16 b;
            a = D_00461060[i][1];
            b = D_00461060[i][2];
            p0[4] = a;
            p0[5] = b;
            p0[0x10] = -1;
            break;
        }
    }
    flag = 0;
    if (ItemKindBelow4_3d4860(arg0) != 0 && id != 3) {
        sel = ItemGetOwnerCharaId_3d4d50(arg0, 1);
        if (ItemIsWeapon_3d46c0(arg0) != 0) {
            y -= 0x2C;
            name = MsgTableLookup_28aa30(D_00481BBC, 0x5F);
            Sprintf_1343b8(spE0, name, arg0->f());
            UiLayoutStringGlyphs_28a800(pC, spE0, 0, y, -2);
        }
        if (sel != -1) {
            Sprintf_1343b8(D_004822E0, D_004610B0, PoolGetUsedElem_36acb0(*(s32 *)(*(u8 **)(GetGameData_1fede0() + 0x14) + 8), sel)->f());
            *(char **)(p8 + 2) = D_004822E0;
            TextStyleInit_26c610(spA0);
            TextStyleInit_26c610(spA0);
            TextStyleSetFontType_26edf0(spA0, 2);
            TextStyleAddSpacing_26f2b0(spA0, 3, 0);
            FontMeasureString_26daf0(spA0, *(char **)(p8 + 2), &spEC, &spE8);
            y -= spEC + 1;
            *p8 = y;
        }
        flag = 1;
    }
    y -= 0x17;
    *p0 = y;
    if (ItemIsWeapon_3d46c0(arg0) != 0) {
        y -= 0x16;
        p0[0x10] = y;
        p0[0x14] = 0;
        p0[0x15] = 0x52;
    } else if ((((unsigned char)ItemIsInsectFood_3d45b0(arg0)) != 0 || arg0->x10[2] == 0xD) && id != 0xC) {
        y -= 0x16;
        p0[0x10] = y;
        flag = 1;
        p0[0x14] = 0;
        p0[0x15] = 0x7E;
    }
    if (flag) {
        p4[0x20] = 0x162;
        p4[0x10] = y + 7;
        p4[0x12] = 0x15B - y;
        p4[0] = y - 1;
    }
    return 1;
}

}
