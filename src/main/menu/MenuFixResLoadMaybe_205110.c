/* PARK (round 1): length 0x1D0 vs retail 0x1CC, close. */
#include "types.h"

#define S32(p, o) (*(s32 *)((u8 *)(p) + (o)))

extern void MemStackReturnToOwnerMaybe_14dad0(s32);
extern s32 MemStackHeapAlloc_14db10(s32, s32, s32, s32);
extern void MemStackHeapFree_14dcb0(s32, s32);
extern void NameTableFreeGroup_158ac0(s32, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 ResidentFileReadLocalizedMaybe_1c2860(s32, s32, s32 *);
extern s32 GetReadBuffHeap_2025e0(void);
extern s32 MsgTableLoadFromArchive_202a50(s32, s32, void *);
extern void TexGroupLoadFromArchive_202be0(s32, void *, void *, s32, void *);
extern void MenuIconAllTexLoadResident_2055f0(void);
extern u8 D_0045C3B0[];
extern u8 D_0045C3D0[];
extern u8 D_0045C3F0[];
extern u8 D_0045C410[];
extern u8 D_0045C420[];
extern s32 D_00480270;
extern s32 D_00480278;
extern s32 D_00481BBC;
extern s32 D_00481C00;
extern s8 D_00481C04;
typedef struct Slot { s32 a; s8 b; } Slot;
extern Slot D_00481C10[2] __attribute__((section(".sdata")));
extern s32 D_00481C20;
extern s8 D_00481C24;
extern u8 D_004BBB60[];

void MenuFixResLoadMaybe_205110(void)
{
    s32 temp_18;
    s32 temp_5;
    s32 temp_2;
    s32 temp_16;
    s32 sp5C;
    s32 var_6;
    s32 temp_19;
    void *temp_3;

    temp_18 = GetDrawCtxNameTable_15de40();
    temp_2 = GetReadBuffHeap_2025e0();
    temp_16 = MemStackHeapAlloc_14db10(temp_2, 2, 0, 0x40);
    temp_5 = temp_16;
    sp5C = 0;
    temp_19 = ResidentFileReadLocalizedMaybe_1c2860(D_00480270, temp_5, &sp5C) & 0xFF;
    MemStackReturnToOwnerMaybe_14dad0(temp_2);
    if (temp_19 == 0 || sp5C <= 0) {
        return;
    }
    {
        TexGroupLoadFromArchive_202be0(temp_16, D_0045C3B0, D_004BBB60, 0x32B, D_004BBB60);
        TexGroupLoadFromArchive_202be0(temp_16, D_0045C3D0, D_004BBB60, 0x32B, D_004BBB60);
        TexGroupLoadFromArchive_202be0(temp_16, D_0045C3F0, D_004BBB60, 0x32B, D_004BBB60);
        TexGroupLoadFromArchive_202be0(temp_16, D_0045C410, D_004BBB60, 0x32B, D_004BBB60);
        TexGroupLoadFromArchive_202be0(temp_16, D_0045C420, D_004BBB60, 0x32B, D_004BBB60);
        if (D_00481BBC == 0) {
            D_00481BBC = MsgTableLoadFromArchive_202a50(temp_16, D_00480278, D_004BBB60);
        }
        MemStackHeapFree_14dcb0(temp_2, temp_16);
        MenuIconAllTexLoadResident_2055f0();
        D_00481C04 = 0;
        D_00481C00 = -1;
        var_6 = 0;
        do {
            D_00481C10[var_6].a = -1;
            D_00481C10[var_6].b = 0;
            var_6 += 1;
        } while (var_6 < 2);
        D_00481C20 = -1;
        D_00481C24 = 0;
        NameTableFreeGroup_158ac0(temp_18, 0x32D);
        NameTableFreeGroup_158ac0(temp_18, 0x32F);
        NameTableFreeGroup_158ac0(temp_18, 0x32E);
    }
}
