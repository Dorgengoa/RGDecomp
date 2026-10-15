#include "types.h"
#pragma opt_propagation off


typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    u8 pad10[0x8];
    s16 unk18;
    u8 unk1A;
    u8 unk1B;
} T299dc0_arg0;

typedef struct { s32 a, b; } Iter;

s32 PadIsReleased_1839c0(void *, s32);
s32 PadIsTriggered_1839f0(void *, s32);
s32 PadIsHeld_183a20(void *, s32);
char *GetGameData_1fede0(void);
void MenuFillItemGrid_2a4b40(s32, s32);
void MenuDrawItemTabs_2a4ee0(s32, s32, s32);
char *IterNext_370040(Iter *);
void IterInit_370170(Iter *, char *);
void InvAddItemCoreMaybe_3c6540(s32, s32, s32, s32, s32, s32, s32);
s32 InvGetCageItem_3c8040(s32, s32);
s32 InsectItemCreateWithRandomName_3cff30(s32, s32);
void RevelationBoardRefreshMaybe_3eaec0(char *, s32, s32);
extern s32 D_0047F6C4;
extern s16 D_00482344;
extern s32 D_00482374;
extern u8 D_004B2570[];

void DebugItemListUpdate_299dc0(T299dc0_arg0 *a) {
    s32 step;
    s32 page;
    char *ctx;
    char *e;
    s32 i;
    char *p;
    Iter it;

    if (a->unk1B == 0) {
        return;
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x1000) || PadIsTriggered_1839f0(D_004B2570, 4) || PadIsHeld_183a20(D_004B2570, 1)) {
        step = 1;
        page = 0;
        if (PadIsTriggered_1839f0(D_004B2570, 4) || PadIsHeld_183a20(D_004B2570, 1)) {
            step = a->unk8;
            page = step;
        }
        if (PadIsHeld_183a20(D_004B2570, 0x80)) {
            step *= 10;
            page *= 10;
        }
        if (a->unkC == 0) {
            if (a->unk1A == 0) {
                a->unkC = a->unk4 - step;
                a->unk0 = a->unk4 - page;
            }
        } else {
            a->unkC -= step;
            a->unk0 -= page;
        }
        a->unk1A = 1;
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x4000) || PadIsTriggered_1839f0(D_004B2570, 8) || PadIsHeld_183a20(D_004B2570, 2)) {
        step = 1;
        page = 0;
        if (PadIsTriggered_1839f0(D_004B2570, 8) || PadIsHeld_183a20(D_004B2570, 2)) {
            step = a->unk8;
            page = step;
        }
        if (PadIsHeld_183a20(D_004B2570, 0x80)) {
            step *= 10;
            page *= 10;
        }
        if (a->unkC == a->unk4 - 1) {
            if (a->unk1A == 0) {
                a->unk0 = a->unkC = step - 1;
            }
        } else {
            a->unkC += step;
            a->unk0 += page;
        }
        a->unk1A = 1;
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x100)) {
        a->unk18 = a->unk18 + 1;
        a->unk18 = a->unk18 % 4;
    } else if (PadIsTriggered_1839f0(D_004B2570, 0x40)) {
        ctx = GetGameData_1fede0();
        p = *(char **)(*(char **)(*(char **)(ctx + 8) + 0x40) + 8);
        if (p != 0) {
            p += 0x88;
        }
        IterInit_370170(&it, p);
        i = 0;
        while ((e = IterNext_370040(&it)) != 0) {
            if (a->unkC == i) {
                if (*(s8 *)(e + 2) == 0x14) {
                    for (i = 0; i < 3; i++) {
                        s32 c = InvGetCageItem_3c8040(*(s32 *)(ctx + 0x18), i);
                        if (c != 0 && InsectItemCreateWithRandomName_3cff30(c, *(s16 *)e) != 0) {
                            break;
                        }
                    }
                } else {
                    InvAddItemCoreMaybe_3c6540(*(s32 *)(ctx + 0x18), *(s16 *)e, 10, 1, -1, 0, 0);
                }
                MenuDrawItemTabs_2a4ee0(D_00482374, 0x67, 1);
                MenuFillItemGrid_2a4b40(D_00482374, 0x76);
                if (D_00482344 == 3) {
                    RevelationBoardRefreshMaybe_3eaec0(ctx, D_0047F6C4, 0);
                }
                break;
            }
            i++;
        }
    } else {
        if (PadIsReleased_1839c0(D_004B2570, 0x1000) || PadIsReleased_1839c0(D_004B2570, 4) || PadIsReleased_1839c0(D_004B2570, 1) ||
            PadIsReleased_1839c0(D_004B2570, 0x4000) || PadIsReleased_1839c0(D_004B2570, 8) || PadIsReleased_1839c0(D_004B2570, 2)) {
            a->unk1A = 0;
        }
    }
    if (a->unkC < 0) {
        a->unkC = 0;
    }
    if (a->unk4 - 1 < a->unkC) {
        a->unkC = a->unk4 - 1;
    }
    if (a->unkC < a->unk0) {
        a->unk0 = a->unkC;
    }
    if (a->unk0 < a->unkC - a->unk8 + 1) {
        a->unk0 = a->unkC - a->unk8 + 1;
    }
    if (a->unk0 < 0) {
        a->unk0 = 0;
    }
    if (a->unk4 - a->unk8 < a->unk0) {
        a->unk0 = a->unk4 - a->unk8;
    }
}
