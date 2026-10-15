#include "types.h"

extern void MemStackReset_14d830(s32);
extern void PadClearStickDpadThreshold_183940(u8 *);
extern void PadSetStickDpadThreshold_183950(u8 *, s32);
extern void PadClearRepeatAll_183960(u8 *);
extern void PadSetRepeat_183d50(u8 *, s32, s32, s32);
extern u8 *GetGameData_1fede0(void);
extern s32 GetWorldDataMgr_1fedf0(void);
extern s32 GetMenuResGroup_206a40(void);
extern void WorkIconBuildPartyWeaponsMaybe_28dde0(void);
extern void MenuModelRelease_2942c0(void);
extern void MenuMainRelease_296d10(void);
extern void MenuMainResFree_298b60(void);
extern void MenuCatalogPageRelease_360d00(s32);
extern void CharaAbilityBitsBackupMaybe_3ad2f0(u8 *);
extern s32 CharaIsPartyLeader_3ae1a0(u8 *);
extern s32 PartyCountReserve_3c1c20(s32, s32, s32);
extern s32 PartyCountMembers_3c2010(s32, s32, s32);
extern u8 *PartyGetSlotChara_3c2fb0(s32, s32);
extern s32 WorldDataMgrNoRequestPending_3eef10(s32);
extern void WorldDataRequestRelease_3f08f0(s32);
extern void WorldDataRequestKind_3f0960(s32, s32);
extern void ResGroupUnloadGroup_42b650(s32, s32);
extern void func_4F50E0(u8 *, s32);
extern u8 D_00527020[];
extern s16 D_0047EB90;
extern s16 D_0047EB98;
extern s32 D_00482334;
extern s32 D_00482338;
extern s32 D_0048234C;
extern s32 D_00482370;
extern s32 D_00482374;
extern s32 D_00482388;
extern s16 D_0048239C;
extern s16 D_004823A4;
extern s16 D_004823A8;
extern s16 D_004823AC;
extern s16 D_004823B0;
extern s8 D_004823B4;
extern s32 D_004823D8;
extern s32 D_004823DC;
extern s32 D_004823E0;
extern u8 D_004B2570[];

void MenuMainClose_296de0(s32 arg0)
{
    s32 lst;
    s16 fid;
    s16 fi;
    s32 i;
    u8 *e;
    s32 n;
    s32 g;
    u8 *p;

    g = GetWorldDataMgr_1fedf0();
    if (arg0 != 0) {
        MenuMainResFree_298b60();
        MenuModelRelease_2942c0();
        if (D_00482388 != 0) {
            MenuCatalogPageRelease_360d00(D_00482388);
        }
        if (D_00482334 != 0) {
            MemStackReset_14d830(D_00482334);
        }
        if (D_00482338 != 0) {
            MemStackReset_14d830(D_00482338);
        }
        WorldDataRequestRelease_3f08f0(g);
        WorldDataRequestKind_3f0960(g, 7);
    } else {
        if (WorldDataMgrNoRequestPending_3eef10(g) == 0) {
            WorldDataRequestRelease_3f08f0(g);
        }
        WorkIconBuildPartyWeaponsMaybe_28dde0();
        MenuMainResFree_298b60();
        PadClearRepeatAll_183960(D_004B2570);
        PadClearStickDpadThreshold_183940(D_004B2570);
        p = GetGameData_1fede0();
        if (p == NULL) {
            return;
        }
        if (*(*(u8 **)(p + 0x20) + 0x24C) & 1) {
            PadSetStickDpadThreshold_183950(D_004B2570, 0x78);
            PadSetRepeat_183d50(D_004B2570, 0xF00C, 0xA, 3);
        }
        D_004823D8 = 0;
        D_0047EB98 = 1;
        D_004823E0 = 0;
        D_004823DC = 0;
        lst = *(s32 *)(p + 0x18);
        n = PartyCountMembers_3c2010(lst, 1, 1);
        n = n + PartyCountReserve_3c1c20(lst, 1, 1);
        fid = -1;
        fi = fid;
        for (i = 0; i < n; i++) {
            e = PartyGetSlotChara_3c2fb0(*(s32 *)(p + 0x18), i);
            if (e != NULL) {
                if ((CharaIsPartyLeader_3ae1a0(e) & 0xFF) == 1) {
                    fid = *(s16 *)(e + 0xC);
                    fi = i;
                }
                CharaAbilityBitsBackupMaybe_3ad2f0(e);
            }
        }
        if (D_0047EB90 != fid) {
            func_4F50E0(D_00527020, fi);
        }
        MenuMainRelease_296d10();
    }
    D_0048234C = 0;
    D_00482374 = 0;
    D_00482370 = 0;
    D_00482388 = 0;
    D_004823A8 = 0;
    D_004823B0 = 0;
    D_004823A4 = 0;
    D_004823AC = 0;
    D_0048239C = 0;
    D_004823B4 = 0;
    ResGroupUnloadGroup_42b650(GetMenuResGroup_206a40(), 1);
}
