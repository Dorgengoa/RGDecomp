#include "types.h"

typedef struct S340 { u8 pad[0x340]; } S340;
typedef struct S50 { u8 pad[0x50]; } S50;
typedef struct S10 { u8 pad[0x10]; } S10;
typedef struct S70 { u8 pad[0x70]; } S70;
typedef struct S150 { u8 pad[0x150]; } S150;

extern void MemStackClear_14dff0(void *);
extern void EffectMgrResetSlots_2e3270(void *);
extern void EffectMgrHeapInit_2e3170(void *, s32);
extern void StatusEffectReset_33c050(void *);
extern void StatusEffectSlotsAlloc_33c060(void *, void *);
extern s32 GetReadBuffHeap_2025e0(void);
extern void *MemStackHeapAlloc_14db10(s32, s32, s32, s32);
extern void MemStackAlign64_14d8e0(s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 ResidentFileReadLocalizedMaybe_1c2860(void *, void *, s32 *);
extern void *MemStackAllocQw_14d950(void *, s32);
extern void *memcpy(void *, const void *, u32);
extern void NameTableRegisterImArchive_1594d0(s32, void *, s32, void *, s32);
extern void MemStackReturnToOwnerMaybe_14dad0(s32);
extern void MemStackHeapFree_14dcb0(s32, void *);
extern u32 strlen(char *);
extern char *strcpy(char *, char *);
extern void *MemStackAllocAligned64_14da10(s32, s32);
extern void MemStackHeapInit_14dee0(void *, void *, s32);
extern void MemStackHeapReinit_14de90(void *);
extern void GuardEffectReset_2d5070(S340 *);
extern void GuardWaveEffectInit_2d5680(S50 *);
extern void GuardWaveEffectSetTex_2d56a0(S50 *, s32);
extern void EffectTimedSlotInit_2d4d10(S10 *);
extern void EffectTimedSlotSetGuardTex_2d4ca0(S10 *, s32);
extern void BladeLineInit_2d5b90(S70 *);
extern void BladeLineSetTex_2d5bf0(S70 *, s32);
extern void MovingLineInit_2d5f40(S150 *);
extern void MovingLineSetTex_2d5fa0(S150 *, s32);
extern void LightningMgrReset_2d71e0(void *);
extern void LightningMgrAllocBolts_2d6690(void *, void *);
extern void LightningMgrSetTex_2d64a0(void *, s32);
extern char D_00461700[];
extern char D_00461718[];
extern s32 D_004826A0;
extern s32 D_004826A4;
extern s32 D_004826A8;
extern s32 D_004826AC;
extern s32 D_004826B0;
extern s16 D_004826B4;
extern char D_004DCCF0[];
extern u8 D_004DCD50[];
extern S340 D_004E0DD0[];
extern S50 D_004E34D0[];
extern S10 D_004E39D0[];
extern S70 D_004E3A90[];
extern S150 D_004E4190[];
extern u8 D_004E6110[];

void EffectMgrInit_2d8a80(s32 arg0, void *arg1)
{
    s32 sz;
    s32 h;
    void *buf;
    s32 k;
    void *dst;
    s32 i;
    void *p;

    MemStackClear_14dff0(D_004DCCF0);
    EffectMgrResetSlots_2e3270(D_004DCD50);
    EffectMgrHeapInit_2e3170(D_004DCD50, arg0);
    StatusEffectReset_33c050(&D_004826B0);
    StatusEffectSlotsAlloc_33c060(&D_004826B0, arg1);
    D_004826B4 = 0x2A6;
    if (arg1 != 0) {
        h = GetReadBuffHeap_2025e0();
        buf = MemStackHeapAlloc_14db10(h, 2, 0, 0x40);
        if (buf != 0) {
            MemStackAlign64_14d8e0(h);
            k = GetDrawCtxNameTable_15de40();
            if (ResidentFileReadLocalizedMaybe_1c2860(D_00461700, buf, &sz) != 0) {
                dst = MemStackAllocQw_14d950(arg1, sz / 16 + 1);
                memcpy(dst, buf, sz);
                NameTableRegisterImArchive_1594d0(k, dst, 0x2A6, arg1, 0);
            }
            MemStackReturnToOwnerMaybe_14dad0(h);
            MemStackHeapFree_14dcb0(h, buf);
        }
    }
    if (arg0 != 0) {
        if (strlen(D_00461718) < 0x10) {
            strcpy(D_004DCCF0, D_00461718);
        }
        MemStackHeapInit_14dee0(D_004DCCF0, MemStackAllocAligned64_14da10(arg0, 0x14300), 0x14300);
        MemStackHeapReinit_14de90(D_004DCCF0);
    }
    for (i = 0; i < 12; i++) {
        GuardEffectReset_2d5070(&D_004E0DD0[i]);
    }
    D_004826A0 = 0;
    for (i = 0; i < 16; i++) {
        S50 *q = &D_004E34D0[i];
        GuardWaveEffectInit_2d5680(q);
        GuardWaveEffectSetTex_2d56a0(q, 0x2A6);
    }
    for (i = 0; i < 12; i++) {
        S10 *q = &D_004E39D0[i];
        EffectTimedSlotInit_2d4d10(q);
        EffectTimedSlotSetGuardTex_2d4ca0(q, 0x2A6);
    }
    D_004826A4 = 0;
    for (i = 0; i < 16; i++) {
        S70 *q = &D_004E3A90[i];
        BladeLineInit_2d5b90(q);
        BladeLineSetTex_2d5bf0(q, 0x2A6);
    }
    D_004826A8 = 0;
    for (i = 0; i < 24; i++) {
        S150 *q = &D_004E4190[i];
        MovingLineInit_2d5f40(q);
        MovingLineSetTex_2d5fa0(q, 0x2A6);
    }
    D_004826AC = 0;
    LightningMgrReset_2d71e0(D_004E6110);
    p = D_004E6110;
    if (p != 0) {
        LightningMgrAllocBolts_2d6690(p, arg1);
        LightningMgrSetTex_2d64a0(p, 0x2A6);
    }
}
