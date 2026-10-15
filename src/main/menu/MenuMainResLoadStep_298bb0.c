#include "types.h"
#pragma opt_propagation off
static inline s16 g1(u8 *p) { s64 r = 3; if ((*(*(u8 **)(p + 0x20) + 0x24C) & 1)) r = 3; return r; }
static inline s16 g2(u8 *p) { if ((*(*(u8 **)(p + 0x20) + 0x24C) & 1)) return 3; else return 3; }
static inline s16 g3(u8 *p) { s16 r; if ((*(*(u8 **)(p + 0x20) + 0x24C) & 1)) r = 3; else r = 3; return r; }


extern void GetDrawCtxNameTable_15de40();
extern s32 ArchiveGetFileByPath_1c2800(s32, u8 *, s32 *);
extern void GetLoaderMgr_1f59d0();
extern u8 *GetGameData_1fede0();
extern s32 MsgTableLoadFromArchive_202a50(s32, u8 *, s32);
extern void TexGroupLoadFromArchive_202be0(s32, u8 *, s32, s32, s32);
extern s32 GetMenuResGroup_206a40();
extern s32 LoadHandleIsReady_28b200(s32);
extern s32 LoadHandleGetId_28b220(s32);
extern void LoadHandleFree_28b230(s32);
extern s32 LoadHandleGetData_28b270(s32, s32 *);
extern s32 LoadHandleGetStatus_28b2e0(s32);
extern void LoadHandleRegisterData_28b320(s32, s32, s32, s32);
extern u8 *UiEntryListFindByTag_28ea40(u8 *, s32);
extern void MenuModelCreate_294330(s32);
extern void MenuPartyEquipSnapshot_2978e0();
extern void MenuMainInitMaybe_297ac0();
extern void MainMenuBuildIconMaskClut_2994d0();
extern void HelpSheetDataLoad_350450(s32, s32);
extern void InfoEdgeDataLoad_399f30(s32, s32);
extern void ResGroupLoadByKind_42b840(s32, s32, s32, s32, s32);
extern u8 D_00461250[];
extern u8 D_00461260[];
extern u8 D_00461280[];
extern u8 D_004612A0[];
extern u8 D_004612C0[];
extern u8 D_004612E0[];
extern u8 D_00461300[];
extern u8 D_00461320[];
extern u8 D_00461338[];
extern u8 D_00461350[];
extern u8 D_00461360[];
extern s32 D_0047EBA0;
extern s32 D_00482334;
extern s32 D_00482338;
extern s16 D_00482390;
extern s16 D_0048239C;
extern s16 D_004823AC;
extern s8 D_004823B4;
extern s32 D_004823D8;
extern s32 D_004823DC;
extern s32 D_004823F8;
extern s32 D_004823FC;
extern s32 D_0048240C;
extern u8 D_004DB1F0[];

static inline s32 ieq(s32 a, s32 b) { return a == b; }

s32 MenuMainResLoadStep_298bb0(void) {
    u8 *p; u8 *q; s32 count; s32 i; s32 j; s32 off; s32 h; s32 r; s32 sp7C; s16 n; s64 t64; s32 f; s32 e;
    GetLoaderMgr_1f59d0();
    count = 0;
    p = GetGameData_1fede0();
    if (p == 0) {
        return 1;
    }
    { s32 u = 3; r = u; if ((*(*(u8 **)(p + 0x20) + 0x24C) & 1)) r = u; } r = (s16)r; n = r;
    for (i = 0; i < n; i++) {
        off = i * 56;
        if (LoadHandleGetId_28b220(D_004823F8 + off) == -1) continue;
        if (LoadHandleGetStatus_28b2e0(D_004823F8 + off) != 1) continue;
        GetDrawCtxNameTable_15de40();
        h = LoadHandleGetData_28b270(D_004823F8 + off, &sp7C);
        if (i == 2 && (ieq((e = D_0047EBA0), i) || e < 0)) {
            D_0047EBA0 = i;
            switch (D_0048240C) {
            case 0:
                off = ((i << 3) - i) << 3;
                LoadHandleRegisterData_28b320(D_004823F8 + off, D_004823FC, 0x32E, D_00482338);
                LoadHandleFree_28b230(D_004823F8 + off);
                MainMenuBuildIconMaskClut_2994d0();
                D_0048240C = 0;
                D_0047EBA0 = -1;
                break;
            }
            break;
        } else if (i == 0 && (ieq((e = D_0047EBA0), i) || e < 0)) {
            D_0047EBA0 = i;
            r = GetMenuResGroup_206a40();
            switch (D_0048240C) {
            case 0:
                ResGroupLoadByKind_42b840(r, 1, 0, D_00482334, h);
                D_0048240C++;
                break;
            case 1:
                D_004823DC = MsgTableLoadFromArchive_202a50(h, D_00461250, D_00482334);
                D_0048240C++;
                break;
            case 2:
                MenuMainInitMaybe_297ac0();
                if (D_0048239C == 0) {
                    MenuPartyEquipSnapshot_2978e0();
                    q = UiEntryListFindByTag_28ea40(D_004DB1F0, 1);
                    *(s16 *)(q + 0x16) = D_00482390;
                }
                D_004823B4 = 1;
                LoadHandleFree_28b230(D_004823F8 + off);
                D_0048240C = 0;
                D_0047EBA0 = -1;
                break;
            }
            break;
        } else if (i == 1 && (ieq((e = D_0047EBA0), i) || e < 0) && LoadHandleGetId_28b220(D_004823F8 + 0x70) == -1) {
            D_0047EBA0 = i;
            switch (D_0048240C) {
            case 0:
                D_004823D8 = MsgTableLoadFromArchive_202a50(h, D_00461260, D_00482334);
                D_0048240C++;
                break;
            case 1:
                InfoEdgeDataLoad_399f30(ArchiveGetFileByPath_1c2800(h, D_00461280, &sp7C), sp7C);
                D_0048240C++;
                break;
            case 2:
                HelpSheetDataLoad_350450(ArchiveGetFileByPath_1c2800(h, D_004612A0, &sp7C), sp7C);
                D_0048240C++;
                break;
            case 3:
                TexGroupLoadFromArchive_202be0(h, D_004612C0, D_00482334, 0x32D, 0);
                TexGroupLoadFromArchive_202be0(h, D_004612E0, D_00482334, 0x32D, 0);
                TexGroupLoadFromArchive_202be0(h, D_00461300, D_00482334, 0x32D, 0);
                TexGroupLoadFromArchive_202be0(h, D_00461320, D_00482334, 0x32F, 0);
                TexGroupLoadFromArchive_202be0(h, D_00461338, D_00482334, 0x32F, 0);
                TexGroupLoadFromArchive_202be0(h, D_00461350, D_00482334, 0x32F, 0);
                D_0048240C++;
                break;
            case 4:
                if (!(*(*(u8 **)(p + 0x20) + 0x24C) & 1)) {
                    MenuModelCreate_294330(ArchiveGetFileByPath_1c2800(h, D_00461360, &sp7C));
                }
                LoadHandleFree_28b230(D_004823F8 + off);
                D_0048240C = 0;
                D_0047EBA0 = -1;
                break;
            }
            break;
        }
    }
    for (j = 0; j < n; j++) {
        count += LoadHandleIsReady_28b200(D_004823F8 + j * 56);
    }
    if (count == n && D_0047EBA0 < 0) {
        D_004823AC = 2;
        return 1;
    }
    if (LoadHandleIsReady_28b200(D_004823F8) != 0 && D_0047EBA0 < 0) {
        { s32 one = 1; D_004823AC = one; return one; }
    }
    return 0;
}
