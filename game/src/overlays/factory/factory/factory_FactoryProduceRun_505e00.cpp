/* rgp:protos */
#line 1
#include "types.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct Slot Slot;   /* arg0 + 0xE0, stride 0x40 */
typedef struct Lay  Lay;    /* 00504080 result, and the fCC / fD4 list nodes */
typedef struct Tile Tile;   /* 005037f0 result */
typedef struct Unit Unit;   /* 004fea80 / 005035b0 result, and the list children */
typedef struct A    A;

struct Unit {
    u8  pad0[0x25];
    s8  f25;
    s8  f26;
    u8  pad27[0x1];
    s16 f28;
    u16 f2A;
    u8  pad2C[0x4];
    s16 f30;
    s16 f32;
};

struct Lay {
    u8  pad0[0x4];
    s16 f4;
    s16 f6;
    u16 f8;
    u8  padA[0x2];
    s16 fC;
    u8  padE[0x2];
    Unit *f10;
};

struct Tile {
    s16 f0;
    s16 f2;
    u16 f4;
};

struct Slot {
    Lay *f0;
    s16 f4;
    u8  pad6[0x2];
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
    s16 f10;
    s16 f12;
    u8  pad14[0xC];
    f32 f20;
    f32 f24;
    f32 f28;
    u8  pad2C[0x4];
    s16 f30;
    s16 f32;
    s16 f34;
    u8  pad36[0xA];
};

/* `lw $25,0x0($4)` / `lw $25,0x70($25)` / `jalr $25` is a C++ VIRTUAL CALL.
   vptr offset K=0 => no data members before the first virtual.
   slot 0x70 = 8 + 4*26 => f70 is the 26th (0-based) declared virtual. */
class VObj {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    s32 f70(s16 a) { return VCM(s32, (void *, s16), 0x70, a); }
};
struct Ob3  { u8 pad0[0x8]; VObj *f8; };
struct Ob2  { u8 pad0[0x40]; struct Ob3 *f40; };
struct Ob1  { u8 pad0[0x8]; struct Ob2 *f8; };

struct A {
    u8  pad0[0x4];
    s32 f4;
    s32 f8;
    u8  padC[0x8];
    s32 f14;
    s32 f18;
    u8  pad1C[0xB0];
    Lay *fCC;
    s32 fD0;
    Lay *fD4;
    s32 fD8;
    u8  padDC[0x4];
    Slot slots[4];
    u8  pad1E0[0xF0];
    s32 f2D0;
    s32 f2D4;
    s32 f2D8;
};

struct Buf { u8 pad0[0x8]; s32 f8; u8 padC[0x14]; };

extern "C" {
s32 factory_FactoryMergeInputsMatchBlueprintMaybe_4e9f40(s32, void *);                  /* extern */
s32 factory_FactoryMarkerRemove_4ea140(s16, s32);                     /* extern */
s32 factory_FactoryPartObjPathPos_4fe500(Lay *, void *, s16, s16, s16); /* extern */
Unit *factory_FactoryPartGroupGetObj_4fea80(Lay *, s16);                 /* extern */
void factory_FactorySlotResetState_4ff590(Slot *);                       /* extern */
s32 factory_FactoryGridDirDy_4ff9b0(s8);                           /* extern */
s32 factory_FactoryGridDirDx_4ff9f0(s8);                           /* extern */
s32 factory_FactoryRouteStep_4ffdc0(A *, s16 *, s16 *);            /* extern */
s32 factory_FactoryRouteStart_4fff20(A *, s16 *, s16, s16);         /* extern */
void factory_FactorySlotMarkersRefresh_5002c0(A *);                          /* extern */
void factory_FactorySlotClearAll_5003b0(A *);                          /* extern */
Unit *factory_FactoryPartGroupGetObjById_5035b0(A *, s16, s16);              /* extern */
Tile *factory_FactoryGridCellAt_5037f0(A *, s32, s32);              /* extern */
Lay *factory_FactoryPartGroupFindById_504080(A *, s16);                    /* extern */
s32 Rand_133710();                                      /* extern */
s32 PadIsTriggered_1839f0(const u8 *, s32);                              /* extern */
void StreamSetChanVolumeFade_1cd960(s32, s32, s32, f32);                    /* extern */
s32 GameSceneSoundSlot6PlaySeVol_1d05c0(s32, s32, f32);                         /* extern */
s32 GetLoaderMgr_1f59d0(void);                                   /* extern */
s32 GetCurrentScene_1f5be0();                                      /* extern */
struct Ob1 *GetGameData_1fede0();                              /* extern */
void StreamPlayMwv_207340(s32, s32, f32);                         /* extern */
void BgmResumeSavedTrack_207420(s32);                                   /* extern */
void BgmSwitchTrackSaveResume_2076c0(s32, s32);                              /* extern */
void BgmSetResumeWaitChan_207e80(s32);                                   /* extern */
s32 GetEffectMgr_2d9040();                                      /* extern */
s32 EffectSetId_2e0100(s32, void *, s32);                      /* extern */
void EffectSetName_2e01c0(s32, void *, void *);                   /* extern */
void EffectSetPosXyz_2e0ad0(s32, void *, f32, f32, f32);            /* extern */
void EffectCreateByName_2e1020(void *, s32, void *, s32);              /* extern */
}
extern "C" u8 D_004B2570[];
extern "C" u8 factory_D_0050D640[0x10];
extern "C" u8 factory_D_0050D658[0x10];

extern "C" void factory_FactoryProduceRun_505e00( struct A *arg0){
    s16 sp118[3];
    s32 sp100[4] __attribute__((aligned(16)));
    struct Buf spE0 __attribute__((aligned(16)));
    u8  spD0;
    s32 spC0;
    s32 spB0;
    s32 spA0;
    s16 temp_3;
    s16 temp_3_2;
    s16 temp_4_2;
    s16 temp_5_2;
    s32 temp_16;
    s32 temp_19;
    s32 temp_2_3;
    s32 temp_2_7;
    s32 temp_5;
    Slot *var_17;
    s32 var_16;
    Slot *var_17_2;
    s32 var_16_2;
    Lay *var_21_2;
    s32 var_18_2;
    Unit *var_17_4;
    s32 var_16_4;
    Unit *var_21_3;
    s32 var_18_3;
    s32 var_21;
    u8 var_23;
    s32 var_30;
    Slot *var_4_2;
    s32 var_3_2;
    Lay *var_7_2;
    s32 var_6_2;
    Unit *var_5_2;
    s32 var_4_3;
    Lay *var_7_3;
    s32 var_6_3;
    Unit *var_5_3;
    s32 var_4_4;
    Lay *var_8;
    s32 var_7;
    Unit *var_6;
    s32 var_5;
    s8 temp_4_3;
    u16 temp_4;
    u8 var_4;
    Slot *var_18b;
    u8 var_17_3;
    u8 var_16_3;
    u8 var_22;
    struct Ob1 *temp_16_2;
    VObj *temp_4_4;
    Slot *temp_22;
    Lay *temp_2;
    Lay *temp_2_10;
    Unit *temp_2_11;
    Unit *temp_2_2;
    Lay *temp_2_4;
    Unit *temp_2_5;
    Unit *temp_2_6;
    Lay *temp_2_8;
    Tile *temp_2_9;
    s32 need;
    s16 want32;
    s16 wantE;
    s16 want10;
    s16 tmpArg;

    temp_19 = GetCurrentScene_1f5be0();
    temp_5 = arg0->f2D4;
    switch (temp_5) {                               /* switch 1; irregular */
    case 0:                                         /* switch 1 */
        if (arg0->f14 == 0) {
            arg0->f4 = 0;
            arg0->f8 = 0;
        } else {
            arg0->f2D0 = (s32) (arg0->f2D0 | 1);
            arg0->f8 = 0;
            var_21_2 = arg0->fD4;
            var_22 = 1;
            if (var_21_2 != NULL) {
                var_18_2 = 0;
                while (var_18_2 < arg0->fD8) {
                    var_17_4 = var_21_2->f10;
                    var_16_4 = 0;
                    while (var_16_4 < var_21_2->fC) {
                        var_17_4->f2A = 0;
                        temp_4_3 = var_17_4->f25;
                        switch (temp_4_3) {         /* switch 2; irregular */
                        case 2:                     /* switch 2 */
                            var_22 = 0;
                            var_17_4->f25 = 3;
                            var_17_4->f28 = 0;
                            break;
                        case 4:                     /* switch 2 */
                            GameSceneSoundSlot6PlaySeVol_1d05c0(temp_19, 7, 1.0f);
                            var_22 = 0;
                            var_17_4->f25 = 5;
                            var_17_4->f28 = 0;
                            break;
                        }
                        var_16_4 += 1;
                        var_17_4 = (Unit *)((void *)((u8 *)var_17_4 + (0x40)));
                    }
                    var_18_2 += 1;
                    var_21_2 = (Lay *)((void *)((u8 *)var_21_2 + (0x68)));
                }
            }
            var_7_2 = arg0->fCC;
            if (var_7_2 != NULL) {
                var_6_2 = 0;
                while (var_6_2 < arg0->fD0) {
                    var_5_2 = var_7_2->f10;
                    var_4_3 = 0;
                    while (var_4_3 < var_7_2->fC) {
                        var_5_2->f2A = 0;
                        var_4_3 += 1;
                        var_5_2 = (Unit *)((void *)((u8 *)var_5_2 + (0x34)));
                    }
                    var_6_2 += 1;
                    var_7_2 = (Lay *)((void *)((u8 *)var_7_2 + (0x14)));
                }
            }
            if (arg0->fD4 != NULL) {
                temp_2_8 = factory_FactoryPartGroupFindById_504080(arg0, 6);
                if (temp_2_8 != NULL) {
                    var_21_3 = temp_2_8->f10;
                    var_18_3 = 0;
                    while (var_18_3 < temp_2_8->fC) {
                        temp_16 = var_21_3->f30 + factory_FactoryGridDirDx_4ff9f0(var_21_3->f26);
                        temp_2_9 = factory_FactoryGridCellAt_5037f0(arg0, temp_16, var_21_3->f32 + factory_FactoryGridDirDy_4ff9b0(var_21_3->f26));
                        if ((temp_2_9 != NULL) && ((((temp_2_9->f4 & 0x8000) != 0) ^ 1) != 0)) {
                            temp_2_10 = factory_FactoryPartGroupFindById_504080(arg0, temp_2_9->f0);
                            if ((temp_2_10 != NULL) && (temp_2_10->f8 & 2)) {
                                temp_2_11 = factory_FactoryPartGroupGetObj_4fea80(temp_2_10, temp_2_9->f2);
                                if (temp_2_11 != NULL) {
                                    temp_2_11->f2A = (u16) (temp_2_11->f2A | 1);
                                }
                            }
                        }
                        var_18_3 += 1;
                        var_21_3 = (Unit *)((void *)((u8 *)var_21_3 + (0x40)));
                    }
                }
            }
            if (var_22) {
                GameSceneSoundSlot6PlaySeVol_1d05c0(temp_19, 0xF, 1.0f);
                arg0->f2D4 = (s32) (arg0->f2D4 + 1);
                arg0->f2D8 = 0;
            }
        }
        break;
    case 1:                                         /* switch 1 */
        var_17 = (Slot *)((u8 *)arg0 + 0xE0);
        var_16 = 0;
        while (var_16 < 4) {
            if (var_17->f4 >= 0) {
                factory_FactorySlotResetState_4ff590(var_17);
                if (factory_FactoryRouteStart_4fff20(arg0, &var_17->fE, var_17->fA, var_17->fC) == 0) {
                    arg0->f4 = 0;
                    break;
                }
            }
            var_16 += 1;
            var_17 = (Slot *)((void *)((u8 *)var_17 + (0x40)));
        }
        BgmSwitchTrackSaveResume_2076c0(0x29, 1);
        arg0->f2D4 = (s32) (arg0->f2D4 + 1);
        arg0->f2D8 = 0;
    case 2:                                         /* switch 1 */
        if (PadIsTriggered_1839f0(D_004B2570, 0x20) != 0) {
            arg0->f4 = 0;
            arg0->f8 = 0x12;
        } else {
            var_8 = arg0->fD4;
            if (var_8 != NULL) {
                var_7 = 0;
                while (var_7 < arg0->fD8) {
                    var_6 = var_8->f10;
                    var_5 = 0;
                    while (var_5 < var_8->fC) {
                        if (var_6->f25 >= 5) {
                            var_6->f25 = 5;
                        }
                        var_5 += 1;
                        var_6 = (Unit *)((void *)((u8 *)var_6 + (0x40)));
                    }
                    var_7 += 1;
                    var_8 = (Lay *)((void *)((u8 *)var_8 + (0x68)));
                }
            }
            spD0 = 0;
            var_17_2 = (Slot *)((u8 *)arg0 + 0xE0);
            spC0 = 0;
            var_16_2 = 0;
            while (var_16_2 < 4) {
                if ((var_17_2->f4 >= 0) && (var_17_2->f12 >= 0)) {
                    temp_5_2 = var_17_2->fE;
                    spC0 += 1;
                    if (temp_5_2 == 0xE) {
                        spD0 = 1;
                    }
                    temp_2 = factory_FactoryPartGroupFindById_504080(arg0, temp_5_2);
                    if (temp_2 != NULL) {
                        temp_2_2 = factory_FactoryPartGroupGetObj_4fea80(temp_2, var_17_2->f10);
                        if (temp_2_2 != NULL) {
                            temp_2_2->f25 = 6;
                            var_17_2->f32 = (s16) (var_17_2->f32 + 1);
                            var_17_2->f34 = (s16) (var_17_2->f34 + 1);
                            temp_2_3 = factory_FactoryPartObjPathPos_4fe500(temp_2, &var_17_2->f20, var_17_2->f10, var_17_2->f12, var_17_2->f32);
                            if (temp_2_3 >= 0) {
                                var_4 = 1;
                                if (temp_2_3 > 0) {
                                    var_4 = factory_FactoryRouteStep_4ffdc0(arg0, sp118, &var_17_2->fE) & 0xFF;
                                    var_17_2->fE = sp118[0];
                                    var_17_2->f10 = sp118[1];
                                    var_17_2->f12 = sp118[2];
                                    var_17_2->f32 = 0;
                                }
                                if (var_4) {
                                    goto next_95;
                                }
                            }
                        }
                    }
                    arg0->f4 = 0;
                    arg0->f8 = 4;
                    break;
                }
next_95:
                var_16_2 += 1;
                var_17_2 = (Slot *)((void *)((u8 *)var_17_2 + (0x40)));
            }
            var_18b = arg0->slots;
            spA0 = 0;
            spB0 = spC0;
            goto test_202;
body_202:
            {
                if ((var_18b->f4 >= 0) && (var_18b->f8 >= 0)) {
                    temp_2_4 = factory_FactoryPartGroupFindById_504080(arg0, var_18b->fE);
                    var_17_3 = 0;
                    if ((var_18b->f32 * 2) == (temp_2_4->f6 * 0x1E)) {
                        temp_3 = temp_2_4->f4;
                        var_16_3 = 1;
                        switch (temp_3) {           /* switch 3 */
                        case 4:                     /* switch 3 */
                            if ((var_18b->f30 == 0) && (var_18b->f0->f4 == 0x44F)) {
                                var_17_3 = 1;
                                var_18b->f30 = 2;
                            } else {
                                var_16_3 = 0;
                                arg0->f8 = 0xC;
                            }
                            break;
                        case 5:                     /* switch 3 */
                            if ((var_18b->f30 == 2) && (var_18b->f0->f4 == 0x44F)) {
                                var_17_3 = 1;
                                var_18b->f30 = 3;
                            } else {
                                var_16_3 = 0;
                                arg0->f8 = 0xD;
                            }
                            break;
                        case 15:                    /* switch 3 */
                        case 16:                    /* switch 3 */
                        case 17:                    /* switch 3 */
                            temp_2_5 = factory_FactoryPartGroupGetObjById_5035b0(arg0, var_18b->fE, var_18b->f10);
                            if ((temp_2_5 != NULL) && (temp_2_5->f2A & 1)) {
                                switch (var_18b->f30) {
                                case 3:
                                    var_17_3 = 1;
                                    var_18b->f30 = 4;
                                    break;
                                }
                            }
                            break;
                        case 2:                     /* switch 3 */
                            if ((var_18b->f30 == 0) && (var_18b->f0->f4 == 0x44C)) {
                                var_17_3 = 1;
                                var_18b->f30 = 5;
                            } else {
                                var_16_3 = 0;
                                arg0->f8 = 0xA;
                            }
                            break;
                        case 0:                     /* switch 3 */
                            if ((var_18b->f30 == 0) && (var_18b->f0->f4 == 0x44D)) {
                                var_18b->f30 = 1;
                                var_17_3 = 1;
                            } else {
                                var_16_3 = 0;
                                arg0->f8 = 8;
                            }
                            break;
                        case 3:                     /* switch 3 */
                            if ((var_18b->f30 == 0) && (var_18b->f0->f4 == 0x44E)) {
                                var_17_3 = 1;
                                var_18b->f30 = 7;
                            } else {
                                var_16_3 = 0;
                                arg0->f8 = 0xB;
                            }
                            break;
                        case 1:                     /* switch 3 */
                            if ((var_18b->f30 == 0) && (var_18b->f0->f4 == 0x450)) {
                                var_17_3 = 1;
                                var_18b->f30 = 6;
                            } else {
                                var_16_3 = 0;
                                arg0->f8 = 9;
                            }
                            break;
                        case 10:                    /* switch 3 */
                        case 11:                    /* switch 3 */
                        case 12:                    /* switch 3 */
                            temp_2_6 = factory_FactoryPartGroupGetObjById_5035b0(arg0, var_18b->fE, var_18b->f10);
                            if (temp_2_6 != NULL) {
                                temp_4 = temp_2_6->f2A;
                                if (!(temp_4 & 2)) {
                                    need = temp_2_4->f4 - 9;
                                    var_4_2 = &arg0->slots[0];
                                    var_3_2 = 0;
                                    temp_2_6->f2A = (u16) (temp_4 | 2);
                                    want32 = var_18b->f32;
                                    var_21 = 0;
                                    wantE = var_18b->fE;
                                    want10 = var_18b->f10;
                                    do {
                                        if ((var_4_2->f4 >= 0) && (var_4_2->f8 >= 0) && (var_4_2->f12 >= 0) && (var_4_2->f32 == want32) && (var_4_2->fE == wantE) && (var_4_2->f10 == want10)) {
                                            sp100[var_21] = var_3_2;
                                            var_21 += 1;
                                        }
                                        var_3_2 += 1;
                                        var_4_2 = (Slot *)((void *)((u8 *)var_4_2 + (0x40)));
                                    } while (var_3_2 < 4);
                                    if (var_21 == need) {
                                    temp_4_2 = var_18b->f30;
                                    switch (temp_4_2) { /* switch 4; irregular */
                                    case 0:         /* switch 4 */
                                        var_16_3 = 0;
                                        arg0->f8 = 0xE;
                                        break;
                                    case 2:         /* switch 4 */
                                        var_16_3 = 0;
                                        arg0->f8 = 0x11;
                                        break;
                                    case 3:         /* switch 4 */
                                        var_16_3 = 0;
                                        arg0->f8 = 0x10;
                                        break;
                                    }
                                    if (var_16_3) {
                                        var_17_3 = 1;
                                        var_30 = 0;
                                        var_23 = 1;
                                        while ((var_30 < var_21) && var_23) {
                                            temp_22 = (Slot *)((u8 *)arg0 + (sp100[var_30] << 6) + 0xE0);
                                            if (var_18b != temp_22) {
                                                temp_3_2 = temp_22->f30;
                                                switch (temp_3_2) { /* switch 5; irregular */
                                                case 0: /* switch 5 */
                                                    var_23 = 0;
                                                    var_16_3 = 0;
                                                    arg0->f8 = 0xE;
                                                    break;
                                                case 2: /* switch 5 */
                                                    var_23 = 0;
                                                    var_16_3 = 0;
                                                    arg0->f8 = 0x11;
                                                    break;
                                                case 3: /* switch 5 */
                                                    var_23 = 0;
                                                    var_16_3 = 0;
                                                    arg0->f8 = 0x10;
                                                    break;
                                                }
                                                factory_FactoryMarkerRemove_4ea140(temp_22->f8, 1);
                                                temp_22->f12 = -1;
                                                temp_22->f8 = -1;
                                                spB0 -= 1;
                                            }
                                            var_30 += 1;
                                        }
                                        if (var_16_3 && (factory_FactoryMergeInputsMatchBlueprintMaybe_4e9f40(var_21, (void *)sp100) == 0)) {
                                            var_16_3 = 0;
                                            arg0->f8 = 0x13;
                                        }
                                        var_18b->f30 = 8;
                                    }
                                    } else {
                                        var_16_3 = 0;
                                        arg0->f8 = 0x15;
                                    }
                                }
                            }
                            break;
                        }
                        if (!var_16_3) {
                            arg0->f4 = 0;
                            goto out_202;
                        }
                    }
                    if (var_17_3) {
                        temp_2_7 = GetEffectMgr_2d9040();
                        EffectCreateByName_2e1020((void *)&spE0, temp_2_7, factory_D_0050D640, -1);
                        if (spE0.f8 >= 0) {
                            EffectSetId_2e0100(temp_2_7, (void *)&spE0, -1);
                            EffectSetPosXyz_2e0ad0(temp_2_7, (void *)&spE0, var_18b->f20, var_18b->f24, var_18b->f28);
                            EffectSetName_2e01c0(temp_2_7, (void *)&spE0, factory_D_0050D658);
                            if (spB0 == 1) {
                                GameSceneSoundSlot6PlaySeVol_1d05c0(temp_19, 0x13, 1.0f);
                            } else {
                                GameSceneSoundSlot6PlaySeVol_1d05c0(temp_19, 0x11, 1.0f);
                            }
                        }
                    }
                }
next_202:
                var_18b = (Slot *)((void *)((u8 *)var_18b + (0x40)));
                spA0 += 1;
            }
test_202:
            if (spA0 < 4) {
                goto body_202;
            }
out_202:
            if ((spC0 == 1) && spD0) {
                arg0->f2D4 = (s32) (arg0->f2D4 + 1);
                arg0->f2D8 = 0;
                StreamSetChanVolumeFade_1cd960(GetLoaderMgr_1f59d0(), 0, 0xF, 0.0f);
            }
        }
        break;
    case 3:                                         /* switch 1 */
        if (arg0->f2D8 == 0x19) {
            GameSceneSoundSlot6PlaySeVol_1d05c0(temp_19, 0x14, 1.0f);
        }
        if (arg0->f2D8 >= 0x1E) {
            StreamPlayMwv_207340(0x324, 0, 1.0f);
            BgmSetResumeWaitChan_207e80(1);
            factory_FactorySlotClearAll_5003b0(arg0);
            arg0->f4 = 0;
            arg0->f8 = 1;
            arg0->f2D0 = (s32) (arg0->f2D0 & ~1);
            temp_16_2 = GetGameData_1fede0();
            tmpArg = (s16) ((Rand_133710() & 0x7F) + 0x4074);
            temp_4_4 = temp_16_2->f8->f40->f8;
            arg0->f18 = temp_4_4->f70(tmpArg);
            arg0->f2D4 = (s32) (arg0->f2D4 + 1);
            arg0->f2D8 = 0;
        }
        break;
    }
    if (arg0->f4 == 0) {
        var_7_3 = arg0->fD4;
        if (var_7_3 != NULL) {
            var_6_3 = 0;
            while (var_6_3 < arg0->fD8) {
                var_5_3 = var_7_3->f10;
                var_4_4 = 0;
                while (var_4_4 < var_7_3->fC) {
                    if (var_5_3->f25 >= 5) {
                        var_5_3->f25 = 5;
                    }
                    var_4_4 += 1;
                    var_5_3 = (Unit *)((void *)((u8 *)var_5_3 + (0x40)));
                }
                var_6_3 += 1;
                var_7_3 = (Lay *)((void *)((u8 *)var_7_3 + (0x68)));
            }
        }
        if (arg0->f8 == 1) {
            factory_FactorySlotClearAll_5003b0(arg0);
        } else {
            factory_FactorySlotMarkersRefresh_5002c0(arg0);
            arg0->f2D0 = (s32) (arg0->f2D0 & ~1);
            BgmResumeSavedTrack_207420(1);
            GameSceneSoundSlot6PlaySeVol_1d05c0(temp_19, 0x12, 1.0f);
        }
    }
    arg0->f2D8 = (s32) (arg0->f2D8 + 1);
}
