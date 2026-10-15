#include "types.h"

#ifndef NULL
#define NULL 0
#endif

extern "C" f32 sqrtf(f32);
extern "C" f32 fabsf(f32);

extern const u8 D_004B2570[];
extern f32 D_0047D5D0;
extern f32 D_0047DB14;
extern f32 D_0047DB50;
extern f32 D_0047DB7C;
extern f32 D_0047DC90;
extern f32 D_0047DC94;
extern f32 D_0047DC98;
extern f32 D_00480E00;
extern f32 D_00480E04;
extern f32 D_00480E08;
extern f32 D_00480E0C;
extern s32 D_0048516A;
extern s32 D_0048516C;

typedef struct Q { u32 w[4]; } Q;
typedef struct V16 { f32 x; f32 y; f32 z; f32 w; } __attribute__((aligned(16))) V16;
typedef struct VI4 { s32 a, b, c, d; } VI4;
typedef struct VF4 { f32 a, b, c, d; } VF4;
typedef struct VIFI { s32 a; f32 b; s32 c; s32 d; } VIFI;
typedef struct VP8 { f32 a; f32 b; f32 c; s32 d; s32 e; f32 f; s32 g; s32 h; } VP8;
typedef struct S S;
/* arg0's class.  Retail accesses 0x4/0x8/0xC/0x18/0x1C/0xD0/0xD8
   through $20 with lw/sw -- 32-bit integers -- while the SAME
   offsets reached through the child pointers are 16-bit and, at
   0x1C, float.  They are two different structures. */
typedef struct A A;
struct A {
    s16 f0;
    s16 f2;
    s32 f4;
    s32 f8;
    s32 fC;
    struct S *f10;
    struct S *f14;
    s32 f18;
    s32 f1C;
    f32 f20;
    s8  f24;
    s8  f25;
    s8  f26;
    s8  f27;
    s16 f28;
    s16 f2A;
    u8  pad2C[0x4];
    s16 f30;
    s16 fx32;
    s16 f34;
    s16 f36;
    s32 f38;
    s32 f3C;
    u8  pad40[0x4];
    s32 (*f44)();
    u8  pad48[0xC];
    struct S *f54;
    struct S *f58;
    u8  pad5C[0x4];
    f32 f60;
    s32 fx64;
    u8  pad68[0x3C];
    s32 (*fA4)();
    s32 (*fA8)();
    u8  padAC[0x14];
    struct S *fC0;
    u8  padC4[0x8];
    s32 fCC;
    s32 fD0;
    struct S *fD4;
    s32 fD8;
    u8  padDC[0xD4];
    struct S *f1B0;
    u8  pad1B4[0xE0];
    s32 f294;
    s16 f298;
    s16 f29A;
    u8  pad29C[0xC];
    f32 f2A8;
    s32 f2AC;
    u8  pad2B0[0x4];
    s32 f2B4;
    f32 f2B8;
    f32 f2BC;
    u8  pad2C0[0x8];
    s32 f2C8;
    s32 f2CC;
    s32 f2D0;
    s32 f2D4;
    s32 f2D8;
    f32 f2DC;
    f32 f2E0;
    s16 f2E4;
    s16 f2E6;
    s16 f2E8;
    s16 f2EA;
    s16 f2EC;
    s16 f2EE;
    s16 f2F0;
    s16 f2F2;
    s16 f2F4;
    s16 f2F6;
    s16 f2F8;
    s16 f2FA;
    s16 f2FC;
    s16 f2FE;
    s16 f300;
    s8  f302;
    u8  pad303[0x5D];
    f32 f360;
    u8  pad364[0x4];
    f32 f368;
    u8  pad36C[0x14];
    f32 f380;
    u8  pad384[0x4];
    f32 f388;
    u8  pad38C[0x58];
    f32 f3E4;
    u8  pad3E8[0x18];
    f32 f400;
    s32 f404;
    f32 f408;
    s32 f40C;
    f32 f410;
    f32 f414;
    f32 f418;
    f32 f41C;
    u8  pad420[0x10];
    V16 v430;
    f32 f440;
    u8  pad444[0x4];
    f32 f448;
    u8  pad44C[0x4];
    f32 f450;
    u8  pad454[0x4];
    f32 f458;
    u8  pad45C[0x4];
    f32 f460;
    u8  pad464[0x4];
    f32 f468;
    u8  pad46C[0x4];
    V16 v470;
    s8  f480;
    u8  pad481[0x1];
    s8  f482;
    u8  b483_0 : 1;
    u8  b483_1 : 1;
    u8  b483_r : 6;
    f32 f484;
    u8  pad488[0x3EBC];
    s32 f4344;
};

struct S {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    u16 f8;
    s16 fA;
    s16 fC;
    u8  pad0E[0x2];
    struct S *f10;
    struct S *f14;
    f32 f18;
    f32 f1C;
    s32 f20;
    s8  f24;
    s8  f25;
    s8  f26;
    s8  f27;
    s16 f28;
    s16 f2A;
    u8  pad2C[0x4];
    s16 f30;
    s16 fx32;
    s16 f34;
    s16 f36;
    s32 f38;
    s32 f3C;
    u8  pad40[0x4];
    s32 (*f44)();
    u8  pad48[0xC];
    struct S *f54;
    struct S *f58;
    u8  pad5C[0x4];
    f32 f60;
    s32 fx64;
    u8  pad68[0x3C];
    s32 (*fA4)();
    s32 (*fA8)();
    u8  padAC[0x14];
    struct S *fC0;
    u8  padC4[0x8];
    s32 fCC;
    f32 fD0;
    struct S *fD4;
    f32 fD8;
    u8  padDC[0xD4];
    struct S *f1B0;
    u8  pad1B4[0xE0];
    s32 f294;
    s16 f298;
    s16 f29A;
    u8  pad29C[0xC];
    f32 f2A8;
    s32 f2AC;
    u8  pad2B0[0x4];
    s32 f2B4;
    f32 f2B8;
    f32 f2BC;
    u8  pad2C0[0x8];
    s32 f2C8;
    s32 f2CC;
    s32 f2D0;
    s32 f2D4;
    s32 f2D8;
    f32 f2DC;
    f32 f2E0;
    s16 f2E4;
    s16 f2E6;
    s16 f2E8;
    s16 f2EA;
    s16 f2EC;
    s16 f2EE;
    s16 f2F0;
    s16 f2F2;
    s16 f2F4;
    s16 f2F6;
    s16 f2F8;
    s16 f2FA;
    s16 f2FC;
    s16 f2FE;
    s16 f300;
    s8  f302;
    u8  pad303[0x5D];
    f32 f360;
    u8  pad364[0x4];
    f32 f368;
    u8  pad36C[0x14];
    f32 f380;
    u8  pad384[0x4];
    f32 f388;
    u8  pad38C[0x58];
    f32 f3E4;
    u8  pad3E8[0x18];
    f32 f400;
    s32 f404;
    f32 f408;
    s32 f40C;
    f32 f410;
    f32 f414;
    f32 f418;
    f32 f41C;
    u8  pad420[0x10];
    V16 v430;
    f32 f440;
    u8  pad444[0x4];
    f32 f448;
    u8  pad44C[0x4];
    f32 f450;
    u8  pad454[0x4];
    f32 f458;
    u8  pad45C[0x4];
    f32 f460;
    u8  pad464[0x4];
    f32 f468;
    u8  pad46C[0x4];
    V16 v470;
    s8  f480;
    u8  pad481[0x1];
    s8  f482;
    u8  b483_0 : 1;
    u8  b483_1 : 1;
    u8  b483_r : 6;
    f32 f484;
    u8  pad488[0x3EBC];
    s32 f4344;
};

/* ---- C++ virtual dispatch ----------------------------------------------
   Retail's SEVEN indirect calls are all `jalr $25` -> C++ virtual member
   calls ([[jalr-is-cpp-virtual]]).  TWO vptr offsets, and they are NOT one
   folded class: 0x1B0 - 0xC0 = 0xF0 is not an offset this unit computes.
     * vptr 0xC0 on the func_1C3BC0 result, slots 0xA4 -> v39, 0xA8 -> v40
       (the SAME class as factory_FactoryCameraUpdate_5050c0's VObj -- one family).
     * vptr 0x1B0 on arg0->f54 / arg0->f58, slot 0x44 -> v15.
   slot = 8 + 4*N.  Dummies are declared and never defined. */
class VC0 {
public:
    u8 padVC0[0xC0];
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39(void *);
    virtual void v40(void *);
};

class V1B0 {
public:
    u8 padV1B0[0x1B0];
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15(f32);
};

extern f32 D_0045B078[];
extern f32 D_0045B080[];
extern "C" s32 factory_FactoryMaterialIsInputActive_4e9f00();                         /* extern */
extern "C" s32 factory_FactoryBlueprintIsListOpen_4e9f20();                         /* extern */
extern "C" s32 factory_FactoryBlueprintOptPartUnlockedMaybe_4e9f70();                         /* extern */
extern "C" s32 factory_FactoryMarkerClearAll_4ea120();                           /* extern */
extern "C" s32 factory_FactoryPartDefGetGridPoint_4fe4c0(void *, void *, void *, s8, s32); /* extern */
extern "C" s32 factory_FactoryPartDefGetFineGridPoint_4fe4e0(void *, void *, void *, s8, s32); /* extern */
extern "C" s32 factory_FactoryPartGroupStep_4fea10(void *, void *);              /* extern */
extern "C" void *factory_FactoryPartGroupGetObj_4fea80(void *, s32);            /* extern */
extern "C" s32 factory_FactoryBeltTileGroupSetVisible_4ff110(void *, void *);              /* extern */
extern "C" void *factory_FactoryBeltTileGroupGetObj_4ff180(s32, s32);               /* extern */
extern "C" f32 factory_FactoryGridDirToAngle_4ff990(s32);                      /* extern */
extern "C" s64 factory_FactoryGridDirDy_4ff9b0(s32);                      /* extern */
extern "C" s64 factory_FactoryGridDirDx_4ff9f0(s32);                      /* extern */
extern "C" s64 factory_FactoryBeltTotalLength_4ffa30(void *);                   /* extern */
extern "C" s32 factory_FactorySlotDropHeld_4fffe0(void *, s32, f32, f32);        /* extern */
extern "C" s32 factory_FactorySlotFill_500160(void *, s32, s32, s32, s32); /* extern */
extern "C" s32 factory_FactorySlotClearAll_5003b0(void *);                     /* extern */
extern "C" s32 factory_FactoryBeltCommitPreview_500400(void *);                     /* extern */
extern "C" s32 factory_FactoryBeltTrimPreview_500450(void *, s32, s32, s32);      /* extern */
extern "C" s32 factory_FactoryBeltCommitPreview_5005d0(void *);                   /* extern */
extern "C" s32 factory_FactoryBeltDragTo_500920(void *, s32, s32, s32);      /* extern */
extern "C" s32 factory_FactoryBeltHasRoom_500d30(void *);                   /* extern */
extern "C" s32 factory_FactoryBeltFindEndNear_500d80(void *, void *, void *, f32, f32); /* extern */
extern "C" s32 factory_FactoryPartRemoveAtPos_500ec0(void *, f32, f32);           /* extern */
extern "C" s32 factory_FactoryBeltTileRemoveAt_500f20(void *, s32, s32);           /* extern */
extern "C" s32 factory_FactoryBeltResetAll_500f50(void *);                     /* extern */
extern "C" s32 factory_FactoryFloorClearAll_501150(void *);                     /* extern */
extern "C" s32 factory_FactoryPartPlace_5013f0(void *, s32, s32, f32, f32); /* extern */
extern "C" s32 factory_FactoryPartPlaceAtCell_501950(void *, s32, s32, s32, s32); /* extern */
extern "C" s32 factory_FactoryBeltTilePlaceAt_501ad0(void *, s32, s32, s32, s8);    /* extern */
extern "C" f32 factory_FactoryPartCentreZ_501d70(void *, s32, s32, f32);    /* extern */
extern "C" f32 factory_FactoryPartCentreX_501e20(void *, s32, s32, f32);    /* extern */
extern "C" s32 factory_FactoryPartLiftAtPos_501ed0(void *, f32, f32);         /* extern */
extern "C" s32 factory_FactoryPartFootprintRect_502760(void *, void *, void *, s32, f32, f32); /* extern */
extern "C" s32 factory_FactoryPartHitTestCell_502970(void *, s32, s32, void *, void *, s32); /* extern */
extern "C" void *factory_FactoryFineGridBeltTileGroupAt_502b60(void *, s32, s32);       /* extern */
extern "C" void *factory_FactoryPartGroupGetObjById_5035b0(void *, s32, s32);       /* extern */
extern "C" void *factory_FactoryBeltTileGroupGetObjById_5035f0(void *, s32, s32);       /* extern */
extern "C" f32 factory_FactoryGridSnapZ_503670(void *, f32);              /* extern */
extern "C" f32 factory_FactoryGridSnapX_5036a0(void *, f32);              /* extern */
extern "C" f32 factory_FactoryGridCellCenterZ_503730(void *, s32);              /* extern */
extern "C" f32 factory_FactoryGridCellCenterX_503760(void *, s32);              /* extern */
extern "C" f32 factory_FactoryFineGridCellCenterZ_503790(void *, s32);              /* extern */
extern "C" f32 factory_FactoryFineGridCellCenterX_5037c0(void *, s32);              /* extern */
extern "C" s16 *factory_FactoryGridCellAt_5037f0(void *, s32, s32);        /* extern */
extern "C" void *factory_FactoryFineGridCellAt_503880(void *, s32, s32);       /* extern */
extern "C" void *factory_FactoryGetFloor_503c00(void *);                 /* extern */
extern "C" f32 factory_FactoryGridHeightAt_503ea0(void *, s32, s32);         /* extern */
extern "C" s32 factory_FactoryGridRowFromZ_503f00(void *, f32);              /* extern */
extern "C" s32 factory_FactoryGridColFromX_503f60(void *, f32);              /* extern */
extern "C" s32 factory_FactoryFineGridRowFromZ_503fc0(void *, f32);              /* extern */
extern "C" s32 factory_FactoryFineGridColFromX_504020(void *, f32);              /* extern */
extern "C" void *factory_FactoryPartGroupFindById_504080(void *, s32);            /* extern */
extern "C" s32 factory_FactoryBeltTileGroupFindById_5040d0(void *, s32);                /* extern */
extern "C" s32 factory_FactoryProduceRun_505e00(void *);                     /* extern */
extern "C" s32 func_10AAB8(void *, void *, void *, f32);         /* extern */
extern "C" f32 func_128D30(f32);                               /* extern */
extern "C" f32 func_128FD0(f32);                               /* extern */
extern "C" f32 func_1291A8(f32, f32);                          /* extern */
extern "C" s32 func_13BE40(void *, void *, void *);                   /* extern */
extern "C" f32 func_13C050(f32);                               /* extern */
extern "C" f32 func_13D3D0(void *, void *, void *);              /* extern */
extern "C" s32 func_150FF0(void *, void *);                       /* extern */
extern "C" s32 func_151080(void *, void *);                       /* extern */
extern "C" s32 func_151110(void *, void *);                       /* extern */
extern "C" s32 func_1839F0(const void *, s32);                              /* extern */
extern "C" s32 func_183A20(const void *, s32);                              /* extern */
extern "C" f32 func_183A50(const void *);                                 /* extern */
extern "C" f32 func_183AF0(const void *);                    /* extern */
extern "C" f32 func_183B90(const void *);                                 /* extern */
extern "C" f32 func_183C30(const void *);                                 /* extern */
extern "C" s32 func_183DD0(const void *, s32);                              /* extern */
extern "C" s32 func_186650(s32, void *);                            /* extern */
extern "C" s32 func_194350(void *, void *);                         /* extern */
extern "C" void *func_1C3BC0(void *, s32);                     /* extern */
extern "C" f32 func_1CBA90(void *, void *);                          /* extern */
extern "C" s32 func_1CBD00(void *, void *, void *);                     /* extern */
extern "C" f32 func_1CBF30(f32);                               /* extern */
extern "C" s32 func_1D05C0(void *, s32, f32);                        /* extern */
extern "C" s32 func_1E49B0(s32, s32, s32);                       /* extern */
extern "C" void *func_1E71D0(s32, s32);                        /* extern */
extern "C" void *func_1F5BE0();                                /* extern */
extern "C" s32 func_201A90();                                  /* extern */

extern "C" void factory_FactoryStep_5069e0(struct A *arg0);

void factory_FactoryStep_5069e0(struct A *arg0){
    struct S *temp_2;
    struct S *temp_2_2;
    u8 var_17;
    u8 var_16;
    f32 saved_reg_f21;
    s16 sp28E;
    s16 sp28C;
    s16 sp28A;
    s16 sp288;
    s16 sp286;
    s16 sp284;
    s16 sp278[4];
    s16 sp270[4];
    s16 sp268[4];
    struct { s16 a; s16 b; u16 c; } sp260;
    struct { s16 a; s16 b; u16 c; } sp258;
    f32 sp240[4];
    f32 sp230[4];
    u8  sp220[0x10];
    u8  sp210[0x10];
    f32 sp200[4];
    volatile struct { s8 a; s8 pad[3]; void *b; s32 pad2[2]; } sp1F0;
    VP8 sp1D0;
    u8  sp1C0[0x10];
    u8  sp1B0[0x10];
    u8  sp1A0[0x10];
    u8  sp190[0x10];
    u8  sp170[0x20];
    u8  sp160[0x10];
    VI4 sp150;
    VIFI sp140;
    VF4 sp130;
    VI4 sp120;
    VF4 sp110;
    VI4 sp100;
    VIFI spF0;
    VF4 spE0;

    f32 temp_f31_2;
    f32 temp_f30;
    f32 temp_f29;
    f32 var_f28;
    f32 temp_f27;
    f32 temp_f26;
    f32 temp_f25;
    f32 temp_f24;
    f32 var_f23;
    f32 var_f22;
    f32 var_f21;
    f32 var_f20;
    f32 temp_f0;
    f32 temp_f0_10;
    f32 temp_f0_11;
    f32 temp_f0_12;
    f32 temp_f0_13;
    f32 temp_f0_14;
    f32 temp_f0_15;
    f32 temp_f0_16;
    f32 temp_f0_17;
    f32 temp_f0_18;
    f32 temp_f0_19;
    f32 temp_f0_20;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f0_9;
    f32 temp_f13;
    f32 temp_f1;
    f32 temp_f1_2;
    f32 temp_f1_4;
    f32 var_f23_3;
    f32 var_f23_2;
    f32 var_f22_2;
    f32 temp_f21_4;
    f32 temp_f21_3;
    f32 temp_f21_2;
    f32 temp_f21;
    f32 var_f21_4;
    f32 var_f21_3;
    f32 var_f21_2;
    f32 temp_f20_4;
    f32 temp_f20_3;
    f32 temp_f20_2;
    f32 temp_f20;
    f32 temp_f24_2;
    f32 temp_f23;
    f32 temp_f23_2;
    f32 temp_f12;
    f32 var_f0;
    f32 var_f0_2;
    f32 var_f1;
    f32 var_f29;
    f32 var_f4;
    f32 var_f3;
    f32 var_f30;
    f32 var_f2;
    f32 temp_f1_3;
    f32 spDC;
    f32 spD8;
    f32 spD4;
    f32 spD0;
    s16 *temp_2_13;
    s16 *temp_2_17;
    struct S *temp_2_23;
    s32 temp_16;
    s32 temp_16_2;
    s32 temp_17_2;
    s32 temp_16_4;
    s32 temp_18_2;
    s32 temp_17_3;
    s32 temp_18;
    s32 temp_2_10;
    s16 temp_3_3;
    s16 temp_3_4;
    s16 temp_4_3;
    s16 temp_5_8;
    struct S *var_18;
    s32 var_17_3;
    s32 var_16_3;
    struct S *temp_2_11;
    s32 var_17_2;
    s32 var_16_2;
    s32 temp_2_26;
    s32 *var_18_3;
    s8 *var_3;
    s8 *var_3_2;
    s8 *var_3_3;
    s8 *var_3_4;
    s8 *var_3_5;
    s32 temp_17;
    s32 temp_16_3;
    s32 temp_21;
    s32 temp_21_2;
    s32 temp_21_3;
    s32 temp_21_4;
    s32 temp_21_5;
    s32 temp_22;
    s32 temp_2_18;
    s32 temp_2_19;
    s32 var_17_4;
    s32 var_16_4;
    s32 temp_2_3;
    s32 temp_2_5;
    s32 temp_2_8;
    s32 temp_3;
    s32 temp_3_2;
    s32 temp_3_5;
    s32 temp_4_4;
    s32 temp_5;
    s32 temp_5_2;
    s32 temp_5_3;
    s32 temp_5_4;
    s32 temp_6_2;
    s32 temp_6_3;
    s32 temp_6_4;
    f32 temp_f31;
    struct S *var_21_2;
    struct S *var_18_2;
    s32 var_16_5;
    void *var_17_7;
    s32 var_16_6;
    u8 var_17_5;
    u8 var_17_6;
    s32 var_17_8;
    s32 var_21;
    u8 var_22;
    s32 var_22_2;
    s32 var_23;
    u32 var_2_2;
    u32 var_2_3;
    u32 var_2_4;
    u32 var_2_5;
    u32 var_2_6;
    s32 var_30;
    s32 var_3_7;
    s32 temp_2_22;
    s8 temp_17_4;
    s8 temp_21_6;
    s8 temp_2_4;
    s8 temp_2_6;
    s8 temp_5_7;
    struct S *temp_16_5;
    struct S *temp_16_6;
    struct S *temp_16_7;
    struct S *temp_2_12;
    struct S *temp_2_14;
    struct S *temp_2_15;
    struct S *temp_2_16;
    struct S *temp_2_20;
    struct S *temp_2_21;
    struct S *temp_2_24;
    struct S *temp_2_25;
    struct S *temp_2_27;
    struct S *temp_2_7;
    struct S *temp_2_9;
    void *temp_4;
    struct S *temp_4_2;
    struct S *temp_5_5;
    struct S *temp_5_6;
    void *tmp_a1;
    struct S *var_6;
    s32 var_5;
    struct S *var_4;
    s32 var_3_6;
    struct S *var_7;
    s32 var_6_2;
    temp_2 = (struct S *)(func_1F5BE0());
    temp_2_2 = (struct S *)(func_1C3BC0(temp_2, temp_2->f4344));
    ((VC0 *)temp_2_2)->v40((void *)sp240);
    ((VC0 *)temp_2_2)->v39((void *)sp230);
    temp_f26 = func_1291A8(sp240[0] - sp230[0], sp240[2] - sp230[2]);
    arg0->f2EA = (s16) arg0->f2EE;
    arg0->f2EC = (s16) arg0->f2F0;
    arg0->f2F2 = (s16) arg0->f2F6;
    arg0->f2F4 = (s16) arg0->f2F8;
    arg0->f2DC = arg0->f360;
    arg0->f2E0 = (f32) arg0->f368;
    arg0->f2EE = factory_FactoryFineGridColFromX_504020(arg0, arg0->f2DC);
    arg0->f2F0 = factory_FactoryFineGridRowFromZ_503fc0(arg0, arg0->f2E0);
    arg0->f2F6 = factory_FactoryGridColFromX_503f60(arg0, arg0->f2DC);
    arg0->f2F8 = factory_FactoryGridRowFromZ_503f00(arg0, arg0->f2E0);
    temp_2_3 = arg0->f2C8;
    var_17 = 0;
    switch (temp_2_3) {                             /* switch 1 */
    case 11:                                        /* switch 1 */
    case 12:                                        /* switch 1 */
    case 13:                                        /* switch 1 */
    case 14:                                        /* switch 1 */
    case 17:                                        /* switch 1 */
    case 18:                                        /* switch 1 */
    case 19:                                        /* switch 1 */
        break;
    case 15:                                        /* switch 1 */
    case 16:                                        /* switch 1 */
        var_17 = 1;
        break;
    }
    temp_5 = 0;
    temp_21 = *(volatile u8 *)((u8 *)arg0 + 0x483) & 1;
    arg0->b483_0 = temp_5;
    arg0->b483_1 = temp_5;
    if (var_17) {
        var_f0 = D_0047DC90;
    } else {
        var_f0 = D_0047DB50;
    }
    arg0->f484 = var_f0;
    temp_2_4 = arg0->f482;
    if (temp_2_4 > 0) {
        arg0->f482 = (s8) (temp_2_4 - 1);
    }
    arg0->f410 = func_183AF0(D_004B2570);
    arg0->f414 = func_183A50(D_004B2570);
    arg0->f418 = func_183C30(D_004B2570);
    arg0->f41C = func_183B90(D_004B2570);
    var_16 = 0;
    if ((arg0->f410 != 0.0f) || (arg0->f414 != 0.0f)) {
        if (temp_21 == 0) {
            var_16 = 1;
        }
    } else {
        {
            temp_2_5 = arg0->f2C8;
            switch (temp_2_5) {                     /* switch 2 */
            case 11:                                /* switch 2 */
            case 15:                                /* switch 2 */
            case 16:                                /* switch 2 */
            case 17:                                /* switch 2 */
            case 18:                                /* switch 2 */
            case 19:                                /* switch 2 */
                arg0->b483_1 = (func_183DD0(D_004B2570, 0xF000) != 0);
                if (arg0->b483_1 != 0) {
                    temp_21_4 = -func_183A20(D_004B2570, 0x8000);
                    arg0->f410 = (f32) (temp_21_4 + func_183A20(D_004B2570, 0x2000));
                    temp_21_5 = -func_183A20(D_004B2570, 0x1000);
                    arg0->f414 = (f32) (temp_21_5 + func_183A20(D_004B2570, 0x4000));
                } else {
                    temp_21_2 = -func_1839F0(D_004B2570, 0x8000);
                    arg0->f410 = (f32) (temp_21_2 + func_1839F0(D_004B2570, 0x2000));
                    temp_21_3 = -func_1839F0(D_004B2570, 0x1000);
                    arg0->f414 = (f32) (temp_21_3 + func_1839F0(D_004B2570, 0x4000));
                    if ((arg0->f410 != 0.0f) || (arg0->f414 != 0.0f)) {
                        var_16 = 1;
                    }
                }
                break;
            }
        }
    }
    if (var_16) {
        arg0->f484 = 1.0f;
        temp_f1 = arg0->f410;
        if (temp_f1 != 0.0f) {
            arg0->f410 = (f32) (temp_f1 / fabsf(temp_f1));
        }
        temp_f1_2 = arg0->f414;
        if (temp_f1_2 != 0.0f) {
            arg0->f414 = (f32) (temp_f1_2 / fabsf(temp_f1_2));
        }
        if (var_17) {
            var_f1 = D_0047D5D0;
        } else {
            var_f1 = D_0047DB7C;
        }
        arg0->f482 = (s8) (s32) (var_f1 * D_0045B078[0]);
    }
    if ((arg0->f410 != 0.0f) || (arg0->f414 != 0.0f)) {
        arg0->b483_0 = 1;
    }
    ((VC0 *)temp_2_2)->v39((void *)sp210);
    ((VC0 *)temp_2_2)->v40((void *)sp220);
    func_13BE40((void *)sp200, (void *)sp210, (void *)sp220);
    temp_f20 = func_1291A8(sp200[0], sp200[2]);
    /* The three sites m2c could not represent, at 0x00506EA0-0x00506EA8.
       mula.s/madd.s are the sum of two squares and `c1 0x544` decodes as
       sqrt.s $f21,$f0 (COP1, fmt S, funct 0x04) -- the disassembler prints the
       raw form, which is why a grep for the MNEMONIC finds it nowhere in the
       corpus.  sqrtf() is an mwcc intrinsic and emits sqrt.s with no call.
       f414 is squared FIRST because mula.s takes the first product. */
    saved_reg_f21 = sqrtf(arg0->f410 * arg0->f410 + arg0->f414 * arg0->f414);
    temp_f0 = func_13C050(temp_f20 + func_1291A8(arg0->f410, arg0->f414));
    arg0->f400 = (f32) (saved_reg_f21 * func_128FD0(temp_f0));
    arg0->f404 = 0;
    arg0->f408 = (f32) (saved_reg_f21 * func_128D30(temp_f0));
    arg0->f40C = 0;
    var_f4 = 1.0f;
    temp_f0_2 = arg0->f400;
    temp_f1_3 = arg0->f408;
    var_f28 = arg0->f2B8;
    temp_f27 = arg0->f2BC;
    temp_f25 = fabsf(temp_f0_2);
    temp_f24 = fabsf(temp_f1_3);
    var_f2 = temp_f0_2 / temp_f25;
    var_f3 = temp_f1_3 / temp_f24;
    if (!(temp_f25 <= 1.0f)) {
        var_f3 = temp_f1_3 / temp_f24;
    } else {
        var_f2 = temp_f0_2;
    }
    if (!(temp_f24 <= 1.0f)) {
        var_f2 = var_f2;
    } else {
        var_f3 = temp_f1_3;
    }
    temp_3 = arg0->f2C8;
    var_f23 = arg0->f460;
    var_f22 = arg0->f468;
    var_f21 = arg0->f450;
    var_f20 = arg0->f458;
    temp_f12 = arg0->v430.x;
    temp_f31 = arg0->v430.z;
    temp_f30 = arg0->v470.x;
    temp_f29 = arg0->v470.z;
    switch (temp_3) {
    case 0x11:
    case 0x12:
    case 0x13:
    case 0xB:
        temp_2_6 = arg0->f480;
        if (temp_2_6 >= 0) {
            arg0->f480 = (s8) (temp_2_6 - 1);
        }
        temp_f1_4 = arg0->f2A8 * arg0->f484;
        spDC = var_f2;
        spDC *= temp_f1_4;
        spD8 = var_f3 * temp_f1_4;
        temp_f31_2 = factory_FactoryGridSnapX_5036a0(arg0, temp_f12);
        spD4 = factory_FactoryGridSnapX_5036a0(arg0, temp_f31);
        factory_FactoryGridSnapX_5036a0(arg0, temp_f30);
        factory_FactoryGridSnapX_5036a0(arg0, temp_f29);
        var_f30 = var_f23 + spDC;
        if (var_f30 < var_f28) {
            var_f30 = var_f28;
        } else if (!(var_f30 <= temp_f27)) {
            var_f30 = temp_f27;
        } else {
            var_f30 = var_f30;
        }
        var_f29 = var_f22 + spD8;
        if (var_f29 < var_f28) {
            var_f29 = var_f28;
        } else if (!(var_f29 <= temp_f27)) {
            var_f29 = temp_f27;
        } else {
            var_f29 = var_f29;
        }
        spD0 = factory_FactoryGridSnapX_5036a0(arg0, var_f30);
        temp_f0_4 = factory_FactoryGridSnapZ_503670(arg0, var_f29);
        if ((arg0->f480 < 0) && ((arg0->f482 == 0) || !(arg0->f484 < 1.0f))) {
            if (!(temp_f25 <= 0.0f) || (arg0->b483_1 != 0)) {
                var_f21 = spD0;
                var_f23 = var_f30;
            } else {
                var_f23 = temp_f31_2;
                var_f21 = temp_f31_2;
            }
            if (!(temp_f24 <= 0.0f) || (arg0->b483_1 != 0)) {
                var_f22 = var_f29;
                var_f20 = temp_f0_4;
            } else {
                var_f22 = spD4;
                var_f20 = var_f22;
            }
        }
        arg0->f460 = var_f23;
        arg0->f468 = var_f22;
        arg0->f450 = var_f21;
        var_f4 = D_0047DC94;
        arg0->f458 = var_f20;
        break;
    }
    *(__int128 *)&arg0->v470 = *(__int128 *)&arg0->v430;
    var_f0_2 = arg0->f450;
    if (var_f0_2 < var_f28) {
        var_f0_2 = var_f28;
    } else if (!(var_f0_2 <= temp_f27)) {
        var_f0_2 = temp_f27;
    } else {
        var_f0_2 = var_f0_2;
    }
    arg0->f450 = var_f0_2;
    temp_f0_5 = arg0->f458;
    if (temp_f0_5 < var_f28) {
        var_f28 = var_f28;
    } else if (!(temp_f0_5 <= temp_f27)) {
        var_f28 = temp_f27;
    } else {
        var_f28 = temp_f0_5;
    }
    arg0->f458 = var_f28;
    temp_4 = (void *)((struct S *)((u8 *)arg0 + 0x430));
    func_10AAB8(temp_4, (struct S *)((u8 *)arg0 + 0x450), temp_4, arg0->f3E4 * var_f4);
    temp_3_2 = arg0->f4;
    if (temp_3_2 == arg0->f2C8) {
        if (!(arg0->f2D0 & 1)) {
            if ((func_1839F0(D_004B2570, 0x20) != 0) || (func_1839F0(D_004B2570, 0x10) != 0)) {
                arg0->f4 = 0;
            }
        }
    } else {
        switch (temp_3_2) {                         /* switch 3 */
        case 4:                                     /* switch 3 */
            factory_FactoryFloorClearAll_501150(arg0);
            arg0->f2D0 = (s32) (arg0->f2D0 & ~1);
            temp_2_7 = (struct S *)((s32) arg0->f14);
            if (temp_2_7 != NULL) {
                temp_3_3 = temp_2_7->f2;
                switch (temp_3_3) {                 /* switch 4; irregular */
                case 0:                             /* switch 4 */
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xB, 7, 9, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 5, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 9, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xE, 7, 0xD, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 3, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 4, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 5, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 6, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 8, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 7, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 3, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 4, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 5, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 6, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 7, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 8, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 7, 0xC, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 6, 9, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 9, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 9, 9, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 5, 9, 1);
                    break;
                case 1:                             /* switch 4 */
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xC, 8, 9, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 8, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 3, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 0xD, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xE, 8, 0xD, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 3, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 4, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 5, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 6, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 7, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 8, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 3, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 4, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 5, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 6, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 7, 9, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 6, 9, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 4, 9, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 9, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 7, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 8, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 3, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 4, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 5, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 6, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 7, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 8, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 9, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xA, 9, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xB, 9, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xC, 9, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 0xC, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 3, 9, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 0xD, 9, 2);
                    break;
                case 2:                             /* switch 4 */
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xB, 0xA, 9, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xB, 6, 7, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 3, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 0xD, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 9, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xE, 0xA, 0xD, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 3, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 5, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 4, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xB, 9, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xC, 9, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 3, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 4, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 5, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 6, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 7, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 8, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xA, 0xC, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 9, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 7, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 4, 7, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 6, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 7, 7, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 6, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 5, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 4, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 3, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 7, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 7, 0xA, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 8, 9, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 0xD, 9, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 3, 7, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 9, 7, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 6, 0xA, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 8, 0xA, 2);
                    break;
                case 3:                             /* switch 4 */
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xB, 8, 9, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xB, 5, 7, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xB, 0xB, 7, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 3, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 0xD, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 9, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 7, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xE, 8, 0xD, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 3, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 4, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 5, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 6, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 7, 6, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 7, 5, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 7, 4, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 3, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 4, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 5, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 6, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 7, 3, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 3, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 4, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 5, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xD, 6, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xA, 7, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xC, 7, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 9, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 7, 9, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 0xC, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 6, 7, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 4, 7, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 3, 7, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 7, 7, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 9, 7, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 0xD, 7, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 0xA, 9, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 0xA, 0xA, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 0xB, 0xA, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 6, 9, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 5, 0xA, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 6, 0xA, 2);
                    break;
                case 4:                             /* switch 4 */
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xB, 9, 9, 0);
                    if (factory_FactoryBlueprintOptPartUnlockedMaybe_4e9f70() != 0) {
                        factory_FactoryPartPlaceAtCell_501950(arg0, 0xC, 5, 8, 0);
                    }
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 2, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 5, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 8, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xD, 0xC, 2, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xE, 9, 0xD, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 3, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 4, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 5, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 6, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 5, 7, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 2, 3, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 2, 4, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 2, 5, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 2, 6, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 2, 7, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 3, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 4, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 5, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 6, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 7, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 4, 8, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 3, 8, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 6, 8, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 7, 8, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 8, 9, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 6, 0xB, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 7, 0xA, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 9, 0xC, 0);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xA, 9, 3);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xC, 3, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xC, 4, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xC, 5, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xC, 6, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xC, 7, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xC, 8, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0xF, 0xB, 9, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 2, 8, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 8, 8, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 0xC, 9, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 7, 0xB, 2);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 5, 0xB, 1);
                    factory_FactoryPartPlaceAtCell_501950(arg0, 0x10, 7, 9, 0);
                    break;
                }
            }
            func_1D05C0(temp_2, 5, 1.0f);
            break;
        case 5:                                     /* switch 3 */
            if (arg0->fC == 0x12) {
                temp_6_2 = arg0->f2D0;
                temp_5_3 = temp_6_2 & ~1;
                arg0->f2D0 = temp_5_3;
                arg0->f2C8 = 0xF;
                arg0->f4 = 0xF;
                arg0->f2E6 = -1;
                arg0->f2EE = factory_FactoryFineGridColFromX_504020(arg0, arg0->f2DC);
                arg0->f2F0 = factory_FactoryFineGridRowFromZ_503fc0(arg0, arg0->f2E0);
            } else {
                temp_5_2 = arg0->f2D0;
                arg0->f2D0 = (s32) (temp_5_2 & ~1);
                arg0->f2C8 = 0x11;
                arg0->f4 = 0x11;
                arg0->f2E8 = (s16) arg0->fC;
                arg0->f2F6 = factory_FactoryGridColFromX_503f60(arg0, arg0->f2DC);
                arg0->f2F8 = factory_FactoryGridRowFromZ_503f00(arg0, arg0->f2E0);
            }
            break;
        case 6:                                     /* switch 3 */
            arg0->f2C8 = 0x13;
            arg0->f4 = 0x13;
            if (!(arg0->f2D0 & 1)) {
                arg0->f2E6 = -1;
                arg0->f2E8 = -1;
                arg0->f2F6 = factory_FactoryGridColFromX_503f60(arg0, arg0->f2DC);
                arg0->f2F8 = factory_FactoryGridRowFromZ_503f00(arg0, arg0->f2E0);
            }
            break;
        case 7:                                     /* switch 3 */
            if (arg0->fC == 0x12) {
                arg0->f2C8 = 0x12;
                arg0->f4 = 0x12;
                if (!(arg0->f2D0 & 1)) {
                    arg0->f2E6 = -1;
                    arg0->f2EE = factory_FactoryFineGridColFromX_504020(arg0, arg0->f2DC);
                    arg0->f2F0 = factory_FactoryFineGridRowFromZ_503fc0(arg0, arg0->f2E0);
                }
            } else {
                arg0->f2C8 = 0x12;
                arg0->f4 = 0x12;
                if (!(arg0->f2D0 & 1)) {
                    arg0->f2E8 = -1;
                    arg0->f2F6 = factory_FactoryGridColFromX_503f60(arg0, arg0->f2DC);
                    arg0->f2F8 = factory_FactoryGridRowFromZ_503f00(arg0, arg0->f2E0);
                }
            }
            break;
        case 8:                                     /* switch 3 */
            factory_FactoryFloorClearAll_501150(arg0);
            func_1D05C0(temp_2, 5, 1.0f);
            break;
        case 9:                                     /* switch 3 */
            factory_FactoryBeltResetAll_500f50(arg0);
            func_1D05C0(temp_2, 5, 1.0f);
            break;
        case 10:                                    /* switch 3 */
            factory_FactoryMarkerClearAll_4ea120();
            factory_FactorySlotClearAll_5003b0(arg0);
            func_1D05C0(temp_2, 5, 1.0f);
            break;
        case 11:                                    /* switch 3 */
            if ((arg0->f18 != 0) && (arg0->f1C > 0)) {
                temp_6_3 = arg0->f2D0;
                temp_5_4 = temp_6_3 & ~1;
                arg0->f2D0 = temp_5_4;
                arg0->f2C8 = 0xB;
                arg0->f4 = 0xB;
                arg0->f2E6 = -1;
                arg0->f2E8 = -1;
                arg0->f2F6 = factory_FactoryGridColFromX_503f60(arg0, arg0->f2DC);
                arg0->f2F8 = factory_FactoryGridRowFromZ_503f00(arg0, arg0->f2E0);
            }
            break;
        case 14:                                    /* switch 3 */
            arg0->f2C8 = 0xE;
            arg0->f4 = 0xE;
            arg0->f2D4 = 0;
            arg0->f2D8 = 0;
            arg0->f2E6 = -1;
            arg0->f2E8 = -1;
            break;
        }
        if (arg0->f4 != arg0->f2C8) {
            arg0->f4 = 0;
            arg0->f8 = 0;
        }
        arg0->f2EA = -1;
        arg0->f2EC = -1;
        arg0->f2F2 = -1;
        arg0->f2F4 = -1;
    }
    var_f22_2 = 0.0f;
    temp_f20_2 = D_0045B080[0];
    sp1D0.a = arg0->f2DC;
    sp1D0.b = 5.0f * temp_f20_2;
    sp1D0.c = arg0->f2E0;
    sp1D0.d = 0x3F800000;
    sp1D0.e = 0;
    temp_f0_6 = factory_FactoryGridDirToAngle_4ff990(arg0->f2E4);
    sp1D0.g = 0;
    sp1D0.f = temp_f0_6;
    sp1F0.a = 1;
    sp1D0.h = 0;
    temp_2_8 = arg0->f2C8;
    switch (temp_2_8) {                             /* switch 5 */
    case 15:                                        /* switch 5 */
        sp1D0.a = arg0->f2DC;
        temp_f0_3 = factory_FactoryGridHeightAt_503ea0(arg0, arg0->f2F6, arg0->f2F8);
        sp1D0.b = temp_f0_3 + temp_f20_2;
        temp_f13 = arg0->f2E0;
        sp1D0.d = 0x3F800000;
        sp1D0.c = temp_f13;
        if (!(arg0->f2D0 & 1)) {
            temp_2_10 = factory_FactoryBeltFindEndNear_500d80(arg0, (void *)&sp28E, (void *)&sp28C, arg0->f2DC, temp_f13);
            arg0->f300 = temp_2_10;
            if ((s16) temp_2_10 >= 0) {
                arg0->f2EE = sp28E;
                arg0->f2F0 = sp28C;
                if ((sp28E != arg0->f2EA) || (sp28C != arg0->f2EC)) {
                    arg0->f302 = 1U;
                }
                if (func_1839F0(D_004B2570, 0x40) != 0) {
                    func_1D05C0(temp_2, 6, 1.0f);
                    arg0->f2FA = (s16) arg0->f2EE;
                    arg0->f2FC = (s16) arg0->f2F0;
                    arg0->f2D0 = (s32) (arg0->f2D0 | 1);
                }
            }
        } else {
            temp_2_9 = (struct S *)(factory_FactoryFineGridBeltTileGroupAt_502b60(arg0, arg0->f2FA, arg0->f2FC));
            if ((temp_2_9 != NULL) && (temp_2_9->f4 == 0x17)) {
                arg0->f300 = -1;
                arg0->f2D0 = (s32) (arg0->f2D0 & ~1);
            } else if (func_1839F0(D_004B2570, 0x20) != 0) {
                arg0->f300 = -1;
                arg0->f2D0 = (s32) (arg0->f2D0 & ~1);
            } else {
                factory_FactoryBeltDragTo_500920(arg0, arg0->f300, arg0->f2EE, arg0->f2F0);
                if ((arg0->f300 >= 0) && (func_1839F0(D_004B2570, 0x40) != 0)) {
                    if (factory_FactoryBeltCommitPreview_5005d0(arg0) != 0) {
                        func_1D05C0(temp_2, 6, 1.0f);
                        temp_5_5 = (struct S *)(arg0->f2AC + (arg0->f300 * 0xC));
                        arg0->f2FA = (s16) *(s16 *)((u8 *)(temp_5_5->f6 * 6) + *(s32 *)&temp_5_5->f0 - 0x6);
                        arg0->f2FC = (s16) *(s16 *)((u8 *)(temp_5_5->f6 * 6) + *(s32 *)&temp_5_5->f0 - 0x4);
                        arg0->f2D0 = (s32) (arg0->f2D0 | 1);
                    }
                    if (factory_FactoryBeltHasRoom_500d30(arg0) == 0) {
                        arg0->f300 = -1;
                        arg0->f2C8 = 0;
                        arg0->f4 = 0;
                        arg0->f8 = 0;
                        arg0->f2D0 = (s32) (arg0->f2D0 & ~1);
                    }
                }
            }
        }
        break;
    case 17:                                        /* switch 5 */
        temp_2_11 = (struct S *)(factory_FactoryPartGroupFindById_504080(arg0, arg0->f2E8));
        if ((temp_2_11 == NULL) || ((temp_2_11->fA - temp_2_11->fC) <= 0)) {
            arg0->f2C8 = 0;
            arg0->f4 = 0;
            arg0->f8 = 0;
            arg0->f2D0 = (s32) (arg0->f2D0 & ~1);
            break;
        }
        var_f23_2 = 3.0f * temp_f20_2;
        temp_f21 = factory_FactoryGridSnapX_5036a0(arg0, arg0->f360);
        if (factory_FactoryPartFootprintRect_502760(arg0, (void *)sp278, temp_2_11, arg0->f2E4, temp_f21, factory_FactoryGridSnapZ_503670(arg0, arg0->f368)) != 0) {
            var_17_2 = sp278[1];
            while (sp278[3] >= var_17_2) {
                var_16_2 = sp278[0];
                while (sp278[2] >= var_16_2) {
                    if (factory_FactoryPartHitTestCell_502970(arg0, var_16_2, var_17_2, temp_2_11, (void *)sp278, arg0->f2E4) != 0) {
                        temp_f0_7 = factory_FactoryGridHeightAt_503ea0(arg0, var_16_2, var_17_2);
                        temp_f0_7 += temp_f20_2;
                        if (!(temp_f0_7 <= var_f23_2)) {
                            var_f23_2 = temp_f0_7;
                        }
                    }
                    var_16_2 += 1;
                }
                var_17_2 += 1;
            }
        }
        if (func_1839F0(D_004B2570, 8) != 0) {
            arg0->f2E4 = (s16) ((arg0->f2E4 - 1) & 3);
            func_1D05C0(temp_2, 2, 1.0f);
        } else if (func_1839F0(D_004B2570, 4) != 0) {
            arg0->f2E4 = (s16) ((arg0->f2E4 + 1) & 3);
            func_1D05C0(temp_2, 2, 1.0f);
        }
        temp_2_12 = (struct S *)(factory_FactoryPartGroupGetObj_4fea80(temp_2_11, temp_2_11->fC));
        if (temp_2_12 != NULL) {
            temp_2_12->f25 = 1;
            if (func_1839F0(D_004B2570, 0x40) != 0) {
                func_186650(temp_2_12->f20, (void *)sp1C0);
                temp_16 = arg0->f2E8;
                temp_f21_2 = factory_FactoryGridSnapX_5036a0(arg0, arg0->f360);
                factory_FactoryPartPlace_5013f0(arg0, temp_16, arg0->f2E4, temp_f21_2, factory_FactoryGridSnapZ_503670(arg0, arg0->f368));
            }
            var_f22_2 += temp_2_11->f1C;
        }
        temp_f0_8 = factory_FactoryPartCentreX_501e20(arg0, arg0->f2E8, arg0->f2E4, arg0->f2DC);
        sp1D0.b = var_f23_2;
        sp1D0.a = temp_f0_8;
        sp1D0.c = factory_FactoryPartCentreZ_501d70(arg0, arg0->f2E8, arg0->f2E4, arg0->f2E0);
        sp1D0.d = 0x3F800000;
        arg0->f440 = factory_FactoryPartCentreX_501e20(arg0, arg0->f2E8, arg0->f2E4, arg0->f450);
        arg0->f448 = factory_FactoryPartCentreZ_501d70(arg0, arg0->f2E8, arg0->f2E4, arg0->f458);
        break;
    case 19:                                        /* switch 5 */
        var_f21_2 = 3.0f * temp_f20_2;
        var_21 = func_1839F0(D_004B2570, 0x40) != 0;
        var_22 = 0;
        if ((func_1839F0(D_004B2570, 0x20) != 0) || (func_1839F0(D_004B2570, 0x10) != 0)) {
            var_22 = 1;
        }
        arg0->f300 = -1;
        var_18 = (struct S *)(factory_FactoryPartGroupFindById_504080(arg0, arg0->f2E8));
        temp_f24_2 = factory_FactoryGridSnapX_5036a0(arg0, arg0->f360);
        temp_f23 = factory_FactoryGridSnapZ_503670(arg0, arg0->f368);
        if ((var_18 == NULL) && (var_21 != 0)) {
            sp28A = -1;
            sp288 = -1;
            temp_16_2 = factory_FactoryGridColFromX_503f60(arg0, temp_f24_2);
            temp_2_13 = (s16 *)(factory_FactoryGridCellAt_5037f0(arg0, temp_16_2, factory_FactoryGridRowFromZ_503f00(arg0, temp_f23)));
            if ((temp_2_13 == NULL) || (*temp_2_13 < 0)) {
                arg0->f300 = factory_FactoryBeltFindEndNear_500d80(arg0, (void *)&sp28A, (void *)&sp288, temp_f24_2, temp_f23);
            }
            var_21 = 0;
            if (factory_FactoryPartLiftAtPos_501ed0(arg0, temp_f24_2, temp_f23) != 0) {
                arg0->f2D0 = (s32) (arg0->f2D0 | 1);
                func_1D05C0(temp_2, 5, 1.0f);
                var_18 = (struct S *)(factory_FactoryPartGroupFindById_504080(arg0, arg0->f2E8));
            } else {
                if (arg0->f300 >= 0) {
                    arg0->f2EE = sp28A;
                    arg0->f2F0 = sp288;
                    if ((sp28A != arg0->f2EA) || (sp288 != arg0->f2EC)) {
                        arg0->f302 = 1U;
                    }
                    arg0->f4 = 1;
                    arg0->f8 = 3;
                }
            }
        }
        if (var_18 == NULL) {
            temp_f0_10 = factory_FactoryGridHeightAt_503ea0(arg0, (s32) temp_f24_2, (s32) temp_f23);
            temp_f0_10 += temp_f20_2;
            if (!(temp_f0_10 <= var_f21_2)) {
                var_f21_2 = temp_f0_10;
            }
        } else {
            if (factory_FactoryPartFootprintRect_502760(arg0, (void *)sp270, var_18, arg0->f2E4, temp_f24_2, temp_f23) != 0) {
                var_17_3 = sp270[1];
                while (sp270[3] >= var_17_3) {
                    var_16_3 = sp270[0];
                    while (sp270[2] >= var_16_3) {
                        if (factory_FactoryPartHitTestCell_502970(arg0, var_16_3, var_17_3, var_18, (void *)sp270, arg0->f2E4) != 0) {
                            temp_f0_9 = factory_FactoryGridHeightAt_503ea0(arg0, var_16_3, var_17_3);
                            temp_f0_9 += temp_f20_2;
                            if (!(temp_f0_9 <= var_f21_2)) {
                                var_f21_2 = temp_f0_9;
                            }
                        }
                        var_16_3 += 1;
                    }
                    var_17_3 += 1;
                }
            }
            if (func_1839F0(D_004B2570, 8) != 0) {
                arg0->f2E4 = (s16) ((arg0->f2E4 - 1) & 3);
                func_1D05C0(temp_2, 2, 1.0f);
            } else if (func_1839F0(D_004B2570, 4) != 0) {
                arg0->f2E4 = (s16) ((arg0->f2E4 + 1) & 3);
                func_1D05C0(temp_2, 2, 1.0f);
            }
            temp_2_14 = (struct S *)(factory_FactoryPartGroupGetObj_4fea80(var_18, var_18->fC));
            if (temp_2_14 != NULL) {
                temp_2_14->f25 = 1;
                if (var_21 != 0) {
                    func_186650(temp_2_14->f20, (void *)sp1B0);
                    if (factory_FactoryPartPlace_5013f0(arg0, arg0->f2E8, arg0->f2E4, temp_f24_2, temp_f23) != 0) {
                        temp_2_15 = (struct S *)(factory_FactoryPartGroupGetObj_4fea80(var_18, var_18->fC));
                        if (temp_2_15 != NULL) {
                            temp_2_15->f24 = -1;
                            temp_2_15->f25 = 0;
                            temp_2_15->f26 = 0;
                            temp_2_15->f27 = 0;
                            temp_2_15->f28 = 0;
                            temp_2_15->f2A = 0;
                            temp_2_15->f30 = -1;
                            temp_2_15->fx32 = -1;
                            temp_2_15->f34 = -1;
                            temp_2_15->f36 = -1;
                            temp_2_15->f38 = 0;
                            temp_2_15->f3C = 0;
                        }
                        arg0->f2E8 = -1;
                        temp_f23_2 = (f32) factory_FactoryGridColFromX_503f60(arg0, temp_f24_2);
                        factory_FactorySlotDropHeld_4fffe0(arg0, 1, temp_f23_2, (f32) factory_FactoryGridRowFromZ_503f00(arg0, temp_f23));
                        arg0->f2D0 = (s32) (arg0->f2D0 & ~1);
                    }
                } else if (var_22 && (factory_FactoryPartPlaceAtCell_501950(arg0, arg0->f2E8, arg0->f2FA, arg0->f2FC, arg0->f2FE) != 0)) {
                    temp_2_16 = (struct S *)(factory_FactoryPartGroupGetObj_4fea80(var_18, var_18->fC));
                    if (temp_2_16 != NULL) {
                        temp_2_16->f24 = -1;
                        temp_2_16->f25 = 0;
                        temp_2_16->f26 = 0;
                        temp_2_16->f27 = 0;
                        temp_2_16->f28 = 0;
                        temp_2_16->f2A = 0;
                        temp_2_16->f30 = -1;
                        temp_2_16->fx32 = -1;
                        temp_2_16->f34 = -1;
                        temp_2_16->f36 = -1;
                        temp_2_16->f38 = 0;
                        temp_2_16->f3C = 0;
                    }
                    arg0->f2E8 = -1;
                    factory_FactorySlotDropHeld_4fffe0(arg0, 0, 0.0f, 0.0f);
                    arg0->f2D0 = (s32) (arg0->f2D0 & ~1);
                }
                var_f22_2 += var_18->f1C;
            }
        }
        temp_f0_11 = factory_FactoryPartCentreX_501e20(arg0, arg0->f2E8, arg0->f2E4, arg0->f2DC);
        sp1D0.b = var_f21_2;
        sp1D0.a = temp_f0_11;
        sp1D0.c = factory_FactoryPartCentreZ_501d70(arg0, arg0->f2E8, arg0->f2E4, arg0->f2E0);
        sp1D0.d = 0x3F800000;
        arg0->f440 = factory_FactoryPartCentreX_501e20(arg0, arg0->f2E8, arg0->f2E4, arg0->f450);
        arg0->f448 = factory_FactoryPartCentreZ_501d70(arg0, arg0->f2E8, arg0->f2E4, arg0->f458);
        break;
    case 16:                                        /* switch 5 */
    case 18:                                        /* switch 5 */
        temp_17 = (s32) factory_FactoryGridSnapX_5036a0(arg0, arg0->f360);
        temp_16_3 = (s32) factory_FactoryGridSnapZ_503670(arg0, arg0->f368);
        if (!(arg0->f2D0 & 1)) {
            arg0->f300 = -1;
            sp286 = -1;
            sp284 = -1;
            temp_18 = factory_FactoryGridColFromX_503f60(arg0, (f32) temp_17);
            temp_2_17 = (s16 *)(factory_FactoryGridCellAt_5037f0(arg0, temp_18, factory_FactoryGridRowFromZ_503f00(arg0, (f32) temp_16_3)));
            if ((temp_2_17 == NULL) || (*temp_2_17 < 0)) {
                arg0->f300 = factory_FactoryBeltFindEndNear_500d80(arg0, (void *)&sp286, (void *)&sp284, (f32) temp_17, (f32) temp_16_3);
            }
            if (arg0->f300 >= 0) {
                arg0->f2EE = sp286;
                arg0->f2F0 = sp284;
                if ((sp286 != arg0->f2EA) || (sp284 != arg0->f2EC)) {
                    arg0->f302 = 1U;
                }
                if (func_1839F0(D_004B2570, 0x40) != 0) {
                    arg0->f2FA = (s16) temp_17;
                    arg0->f2FC = (s16) temp_16_3;
                    arg0->f2D0 = (s32) (arg0->f2D0 | 1);
                    arg0->f4 = 0x10;
                    arg0->fC = 0x12;
                }
            } else {
                if (func_1839F0(D_004B2570, 0x40) != 0) {
                    factory_FactoryPartRemoveAtPos_500ec0(arg0, (f32) temp_17, (f32) temp_16_3);
                    func_1D05C0(temp_2, 5, 1.0f);
                }
            }
        } else {
            if ((((struct S *)(arg0->f2AC + (arg0->f300 * 0xC)))->f6 > 1) && (func_1839F0(D_004B2570, 0x20) == 0)) {
                if (func_1839F0(D_004B2570, 0x10) != 0) {
block_269:
                    arg0->f300 = -1;
                    arg0->f2D0 = (s32) (arg0->f2D0 & ~1);
                    arg0->f4 = 0x12;
                    arg0->fC = -1;
                } else {
                    factory_FactoryBeltTrimPreview_500450(arg0, arg0->f300, arg0->f2EE, arg0->f2F0);
                    if ((arg0->f300 >= 0) && (func_1839F0(D_004B2570, 0x40) != 0)) {
                        factory_FactoryBeltCommitPreview_500400(arg0);
                        func_1D05C0(temp_2, 5, 1.0f);
                        temp_5_6 = (struct S *)(arg0->f2AC + (arg0->f300 * 0xC));
                        arg0->f2FA = (s16) *(s16 *)((u8 *)(temp_5_6->f6 * 6) + *(s32 *)&temp_5_6->f0 - 0x6);
                        arg0->f2FC = (s16) *(s16 *)((u8 *)(temp_5_6->f6 * 6) + *(s32 *)&temp_5_6->f0 - 0x4);
                        arg0->f2D0 = (s32) (arg0->f2D0 | 1);
                    }
                }
            } else {
                goto block_269;
            }
        }
        temp_f21_3 = D_0045B080[0];
        var_f23_3 = 3.0f * temp_f21_3;
        temp_f0_12 = factory_FactoryGridHeightAt_503ea0(arg0, temp_17, temp_16_3);
        temp_f0_12 += temp_f21_3;
        if (!(temp_f0_12 <= var_f23_3)) {
            var_f23_3 = temp_f0_12;
        }
        temp_f0_13 = factory_FactoryPartCentreX_501e20(arg0, arg0->f2E8, arg0->f2E4, arg0->f2DC);
        sp1D0.b = var_f23_3;
        sp1D0.a = temp_f0_13;
        sp1D0.c = factory_FactoryPartCentreZ_501d70(arg0, arg0->f2E8, arg0->f2E4, arg0->f2E0);
        sp1D0.d = 0x3F800000;
        break;
    case 11:                                        /* switch 5 */
        temp_17_2 = factory_FactoryGridColFromX_503f60(arg0, factory_FactoryGridSnapX_5036a0(arg0, arg0->f360));
        temp_16_4 = factory_FactoryGridRowFromZ_503f00(arg0, factory_FactoryGridSnapZ_503670(arg0, arg0->f368));
        var_f21_3 = 3.0f * temp_f20_2;
        if ((func_1839F0(D_004B2570, 0x40) != 0) && (factory_FactorySlotFill_500160(arg0, arg0->f18, arg0->f1C, temp_17_2, temp_16_4) != 0)) {
            func_1D05C0(temp_2, 3, 1.0f);
            arg0->f2C8 = 0;
            arg0->f4 = 0;
        }
        temp_f0_14 = factory_FactoryGridHeightAt_503ea0(arg0, temp_17_2, temp_16_4);
        temp_f0_14 += temp_f20_2;
        if (!(temp_f0_14 <= var_f21_3)) {
            var_f21_3 = temp_f0_14;
        }
        temp_f0_15 = factory_FactoryPartCentreX_501e20(arg0, arg0->f2E8, arg0->f2E4, arg0->f2DC);
        sp1D0.b = var_f21_3;
        sp1D0.a = temp_f0_15;
        sp1D0.c = factory_FactoryPartCentreZ_501d70(arg0, arg0->f2E8, arg0->f2E4, arg0->f2E0);
        sp1D0.d = 0x3F800000;
        break;
    case 14:                                        /* switch 5 */
        factory_FactoryProduceRun_505e00(arg0);
        break;
    }
    temp_2_18 = arg0->f2C8;
    switch (temp_2_18) {                            /* switch 6 */
    case 15:                                        /* switch 6 */
    case 16:                                        /* switch 6 */
        temp_16_5 = (struct S *)((s32) arg0->f58);
        if (temp_16_5 != NULL) {
            arg0->f60 = func_1CBF30(D_0047DC98 + arg0->f60);
            var_3 = (s8 *)((void *)&sp150);
            var_2_2 = 0x10;
            if (var_3 != NULL) {
                do {
                    *var_3 = 0;
                    var_2_2 -= 1;
                    var_3 = (s8 *)((u8 *)var_3 + (1));
                } while (var_2_2 != 0);
            }
            sp150.a = 0x3F000000;
            sp150.b = 0x3F000000;
            sp150.c = 0x3F000000;
            func_150FF0(temp_16_5, (void *)&sp150);
            temp_f0_16 = func_1CBF30(arg0->f60 + temp_f26);
            var_3_2 = (s8 *)((void *)&sp140);
            var_2_3 = 0x10;
            if (var_3_2 != NULL) {
                do {
                    *var_3_2 = 0;
                    var_2_3 -= 1;
                    var_3_2 = (s8 *)((u8 *)var_3_2 + (1));
                } while (var_2_3 != 0);
            }
            sp140.b = temp_f0_16;
            sp140.a = 0;
            sp140.c = 0;
            func_151080(temp_16_5, (void *)&sp140);
            temp_f20_3 = factory_FactoryFineGridCellCenterZ_503790(arg0, factory_FactoryFineGridRowFromZ_503fc0(arg0, arg0->f2E0));
            var_f21_4 = sp1D0.b + var_f22_2;
            temp_f0_17 = factory_FactoryFineGridCellCenterX_5037c0(arg0, factory_FactoryFineGridColFromX_504020(arg0, arg0->f2DC));
            sp130.a = D_00480E00;
            sp130.b = D_00480E04;
            sp130.c = D_00480E08;
            sp130.d = D_00480E0C;
            sp130.a = temp_f0_17;
            sp130.b = var_f21_4;
            sp130.c = temp_f20_3;
            tmp_a1 = (void *)&sp130;
            func_151110(temp_16_5, tmp_a1);
            ((V1B0 *)temp_16_5)->v15(1.0f);
        }
        break;
    case 11:                                        /* switch 6 */
    case 17:                                        /* switch 6 */
    case 18:                                        /* switch 6 */
    case 19:                                        /* switch 6 */
        temp_16_6 = (struct S *)((s32) arg0->f54);
        if (temp_16_6 != NULL) {
            arg0->f60 = func_1CBF30(D_0047DC98 + arg0->f60);
            var_3_3 = (s8 *)((void *)&sp120);
            var_2_4 = 0x10;
            if (var_3_3 != NULL) {
                do {
                    *var_3_3 = 0;
                    var_2_4 -= 1;
                    var_3_3 = (s8 *)((u8 *)var_3_3 + (1));
                } while (var_2_4 != 0);
            }
            sp120.a = 0;
            sp120.b = 0;
            sp120.c = 0;
            func_151080(temp_16_6, (void *)&sp120);
            temp_f21_4 = factory_FactoryGridSnapZ_503670(arg0, arg0->f2E0);
            temp_f0_18 = factory_FactoryGridSnapX_5036a0(arg0, arg0->f2DC);
            tmp_a1 = (void *)&sp110;
            ((VF4 *)tmp_a1)->a = D_00480E00;
            ((VF4 *)tmp_a1)->b = D_00480E04;
            ((VF4 *)tmp_a1)->c = D_00480E08;
            ((VF4 *)tmp_a1)->d = D_00480E0C;
            sp110.a = temp_f0_18;
            sp110.b = 10.0f * (D_0047DB14 * temp_f20_2);
            sp110.c = temp_f21_4;
            func_151110(temp_16_6, tmp_a1);
            ((V1B0 *)temp_16_6)->v15(1.0f);
        }
        temp_16_7 = (struct S *)((s32) arg0->f58);
        if (temp_16_7 != NULL) {
            arg0->f60 = func_1CBF30(D_0047DC98 + arg0->f60);
            var_3_4 = (s8 *)((void *)&sp100);
            var_2_5 = 0x10;
            if (var_3_4 != NULL) {
                do {
                    *var_3_4 = 0;
                    var_2_5 -= 1;
                    var_3_4 = (s8 *)((u8 *)var_3_4 + (1));
                } while (var_2_5 != 0);
            }
            sp100.a = 0x3F800000;
            sp100.b = 0x3F800000;
            sp100.c = 0x3F800000;
            func_150FF0(temp_16_7, (void *)&sp100);
            temp_f0_19 = func_1CBF30(arg0->f60 + temp_f26);
            var_3_5 = (s8 *)((void *)&spF0);
            var_2_6 = 0x10;
            if (var_3_5 != NULL) {
                do {
                    *var_3_5 = 0;
                    var_2_6 -= 1;
                    var_3_5 = (s8 *)((u8 *)var_3_5 + (1));
                } while (var_2_6 != 0);
            }
            spF0.b = temp_f0_19;
            spF0.a = 0;
            spF0.c = 0;
            func_151080(temp_16_7, (void *)&spF0);
            temp_18_2 = factory_FactoryGridColFromX_503f60(arg0, arg0->f380);
            temp_17_3 = factory_FactoryGridRowFromZ_503f00(arg0, arg0->f388);
            temp_f20_4 = factory_FactoryGridCellCenterX_503760(arg0, temp_18_2) - (arg0->f380 - arg0->f360);
            temp_f0_20 = factory_FactoryGridCellCenterZ_503730(arg0, temp_17_3) - (arg0->f388 - arg0->f368);
            tmp_a1 = (void *)&spE0;
            ((VF4 *)tmp_a1)->a = D_00480E00;
            ((VF4 *)tmp_a1)->b = D_00480E04;
            ((VF4 *)tmp_a1)->c = D_00480E08;
            ((VF4 *)tmp_a1)->d = D_00480E0C;
            spE0.b = sp1D0.b + var_f22_2;
            spE0.c = temp_f0_20;
            spE0.a = temp_f20_4;
            func_151110(temp_16_7, tmp_a1);
            ((V1B0 *)temp_16_7)->v15(1.0f);
        }
        break;
    }
    sp1D0.e = 0;
    sp1D0.f = factory_FactoryGridDirToAngle_4ff990(arg0->f2E4);
    sp1D0.g = 0;
    sp1D0.h = 0;
    arg0->fx64 = (s32) ((arg0->fx64 + 1) & 0xF);
    temp_2_19 = factory_FactoryBeltTileGroupFindById_5040d0(arg0, 0x17);
    if (temp_2_19 != 0) {
        var_17_4 = 0;
        while (var_17_4 < arg0->f29A) {
            var_16_4 = 0;
            while (var_16_4 < arg0->f298) {
                temp_4_2 = (struct S *)((u8 *)(arg0->f294 + (var_17_4 * arg0->f298 * 6)) + (var_16_4 * 6));
                if (((((u16) temp_4_2->f4 & 0x8000) != 0) ^ 1) && (temp_4_2->f0 == 0x17)) {
                    temp_21_6 = ((struct S *)((struct S *)factory_FactoryBeltTileGroupGetObj_4ff180(temp_2_19, temp_4_2->f2)))->f26;
                    factory_FactoryBeltTileRemoveAt_500f20(arg0, var_16_4, var_17_4);
                    factory_FactoryBeltTilePlaceAt_501ad0(arg0, 0x18, var_16_4, var_17_4, temp_21_6);
                }
                var_16_4 += 1;
            }
            var_17_4 += 1;
        }
    }
    var_6 = (struct S *)((s32) arg0->fD4);
    var_5 = 0;
    while (var_5 < arg0->fD8) {
        if (var_6->f8 & 2) {
            var_4 = (struct S *)((s32) var_6->f10);
            var_3_6 = 0;
            while (var_3_6 < var_6->fC) {
                var_4->f3C = 0;
                var_3_6 += 1;
                var_4 = (struct S *)((void *)((u8 *)var_4 + (0x40)));
            }
        }
        var_5 += 1;
        var_6 = (struct S *)((void *)((u8 *)var_6 + (0x68)));
    }
    if (!(func_13D3D0((void *)sp230, (void *)sp240, var_6) <= 400.0f)) {
        sp1F0.a = 0;
    }
    var_21_2 = (struct S *)((s32) arg0->fD4);
    if (var_21_2 != NULL) {
        var_22_2 = 0;
        while (var_22_2 < arg0->fD8) {
            if (!(var_21_2->f8 & 2)) {
                var_18_2 = (struct S *)((s32) var_21_2->f10);
                var_30 = 0;
                while (var_30 < var_21_2->fC) {
                    if (var_18_2->f25 >= 3) {
                        var_16_5 = 0;
                        var_17_5 = 0;
                        sp268[0] = var_18_2->f30 * arg0->f2B4;
                        temp_3_5 = arg0->f2B4;
                        sp268[1] = var_18_2->fx32 * temp_3_5;
                        sp268[2] = ((var_18_2->f34 + 1) * temp_3_5) - 1;
                        sp268[3] = ((var_18_2->f36 + 1) * temp_3_5) - 1;
                        while (factory_FactoryPartDefGetFineGridPoint_4fe4e0(var_21_2, (void *)&sp260, (void *)sp268, var_18_2->f26, var_16_5) != 0) {
                            temp_2_20 = (struct S *)(factory_FactoryFineGridCellAt_503880(arg0, sp260.a, sp260.b));
                            if (temp_2_20 != NULL) {
                                temp_5_8 = temp_2_20->f0;
                                if (temp_5_8 == 0x18) {
                                    temp_2_21 = (struct S *)(factory_FactoryBeltTileGroupGetObjById_5035f0(arg0, temp_5_8, temp_2_20->f2));
                                    if (temp_2_21 != NULL) {
                                        temp_17_4 = temp_2_21->f26;
                                        if (temp_17_4 == (sp260.c & 3)) {
                                            factory_FactoryBeltTileRemoveAt_500f20(arg0, sp260.a, sp260.b);
                                            factory_FactoryBeltTilePlaceAt_501ad0(arg0, 0x17, sp260.a, sp260.b, temp_17_4);
                                            if (var_18_2->f25 == 3) {
                                                var_18_2->f25 = 4;
                                                var_18_2->f24 = 0;
                                            }
                                        }
                                    }
                                    var_17_5 = 1;
                                }
                            }
                            var_16_5 += 1;
                        }
                        if (!var_17_5) {
                            var_18_2->f25 = 3;
                        }
                    }
                    if (var_18_2->f25 >= 5) {
                        var_23 = 0;
                        while (factory_FactoryPartDefGetGridPoint_4fe4c0(var_21_2, (void *)&sp258, (struct S *)((u8 *)var_18_2 + 0x30), var_18_2->f26, var_23) != 0) {
                            var_17_6 = 1;
                            while (var_17_6) {
                                var_17_6 = 0;
                                sp258.a += (s16) factory_FactoryGridDirDx_4ff9f0(sp258.c & 3);
                                temp_2_22 = sp258.b + (s16) factory_FactoryGridDirDy_4ff9b0(sp258.c & 3);
                                sp258.b = (s16) temp_2_22;
                                temp_2_23 = (struct S *)(factory_FactoryGridCellAt_5037f0(arg0, sp258.a, (s16) temp_2_22));
                                if (temp_2_23 != NULL) {
                                    temp_2_24 = (struct S *)(factory_FactoryPartGroupGetObjById_5035b0(arg0, temp_2_23->f0, temp_2_23->f2));
                                    if (temp_2_24 != NULL) {
                                        temp_4_3 = temp_2_23->f0;
                                        switch (temp_4_3) { /* switch 7; irregular */
                                        case 15:    /* switch 7 */
                                            if (!((temp_2_24->f26 - (sp258.c & 3)) & 1)) {
                                            case 17: /* switch 7 */
                                                var_17_6 = 1;
                                                temp_2_24->f3C = 1;
                                            }
                                            break;
                                        case 16:    /* switch 7 */
                                            temp_6_4 = sp258.c & 3;
                                            temp_4_4 = (temp_2_24->f26 - temp_6_4) & 3;
                                            switch (temp_4_4) { /* switch 8; irregular */
                                            case 2: /* switch 8 */
                                                var_17_6 = 1 & 0xFF;
                                                sp258.c = ((sp258.c & ~3) | (temp_6_4 + 3)) & 3;
                                                temp_2_24->f3C = 1;
                                                break;
                                            case 1: /* switch 8 */
                                                var_17_6 = 1 & 0xFF;
                                                sp258.c = ((sp258.c & ~3) | (temp_6_4 + 1)) & 3;
                                                temp_2_24->f3C = 1;
                                                break;
                                            }
                                            break;
                                        }
                                        var_17_6 = (var_17_6 & 0xFF & ((temp_2_24->f25 >= 5) & 0xFF)) != 0;
                                    }
                                }
                            }
                            var_23 += 1;
                        }
                    }
                    var_30 += 1;
                    var_18_2 = (struct S *)((void *)((u8 *)var_18_2 + (0x40)));
                }
            } else {
                var_7 = (struct S *)((s32) var_21_2->f10);
                var_6_2 = 0;
                while (var_6_2 < var_21_2->fC) {
                    temp_5_7 = var_7->f25;
                    if (temp_5_7 >= 3) {
                        if (var_7->f3C != 0) {
                            if (temp_5_7 == 3) {
                                var_7->f25 = 4;
                                var_7->f24 = 0;
                            }
                        } else if (temp_5_7 != 3) {
                            var_7->f25 = 3;
                            var_7->f24 = 0;
                        }
                    }
                    var_6_2 += 1;
                    var_7 = (struct S *)((void *)((u8 *)var_7 + (0x40)));
                }
            }
            sp1F0.b = (void *)(var_21_2);
            factory_FactoryPartGroupStep_4fea10(var_21_2, (void *)&sp1D0);
            var_22_2 += 1;
            var_21_2 = (struct S *)((void *)((u8 *)var_21_2 + (0x68)));
        }
    }
    sp1F0.a = 1;
    if (((factory_FactoryBlueprintIsListOpen_4e9f20() != 0) || (factory_FactoryMaterialIsInputActive_4e9f00() != 0)) && (((s64) (factory_FactoryBeltTotalLength_4ffa30(arg0) << 0x30) >> 0x30) >= 0xC8)) {
        sp1F0.a = 0;
    }
    var_17_7 = (void *)(arg0->fCC);
    if (var_17_7 != NULL) {
        var_16_6 = 0;
        while (var_16_6 < arg0->fD0) {
            sp1F0.b = (void *)(var_17_7);
            factory_FactoryBeltTileGroupSetVisible_4ff110(var_17_7, (void *)&sp1D0);
            var_16_6 += 1;
            var_17_7 = (void *)((u8 *)var_17_7 + (0x14));
        }
    }
    temp_2_25 = (struct S *)(factory_FactoryGetFloor_503c00(arg0));
    if (temp_2_25 != NULL) {
        temp_2_26 = func_1E49B0(func_201A90(), temp_2_25->f0, 0);
        if (temp_2_26 != 0) {
            var_18_3 = *(s32 **)((u8 *)temp_2_25 + 8);
            temp_22 = *(s32 *)((u8 *)temp_2_25 + 0xC);
            var_17_8 = 0;
            while (var_17_8 < temp_22) {
                temp_2_27 = (struct S *)(func_1E71D0(temp_2_26, *var_18_3));
                if (temp_2_27 != NULL) {
                    func_194350(temp_2_27, (void *)sp170);
                    func_1CBD00((void *)sp160, (void *)sp1A0, (void *)sp230);
                    var_3_7 = (func_1CBA90((void *)sp160, (void *)sp190) > 0.0f);
                    temp_2_27->fx32 = (s16) ((var_3_7 & 0xFF) != 0);
                }
                var_17_8 += 1;
                var_18_3 = (s32 *)((u8 *)var_18_3 + (4));
            }
        }
    }
    arg0->f2CC = (s32) arg0->f2C8;
    arg0->f2C8 = (s32) arg0->f4;
    if (*(u8 *)&arg0->f302 != 0) {
        func_1D05C0(temp_2, 1, 1.0f);
    }
    arg0->f302 = 0U;
}
