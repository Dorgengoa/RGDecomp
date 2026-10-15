#include "types.h"

struct GObj {
    u8 pad000[0x1B0];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
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
};

typedef unsigned __int128 u128;
typedef struct { s32 w[24]; } S96;
typedef struct { u128 q[6]; } Q96;

extern u8 D_00463FE8[];
extern u8 D_00464000[];
extern u8 D_00464018[];
extern u8 D_004DB1B0[];
extern u8 *D_00482374;
extern u8 D_004E92C0[];
extern s16 D_00463E20[];
extern u8 D_004E9510[];
extern u8 D_004E9530[];
extern u8 D_004E9320[];
extern u8 D_00470F50[];
extern s16 D_0047FBD0;
extern s16 D_0047FBD4;
extern s16 D_0047FBD8;
extern s32 D_00483298;
extern s8  D_0048329C;
extern u8  D_00483338[2];
extern s32 D_00483340[2];
extern s16 D_00483334;
extern s32 D_004832B8;
extern s32 D_004832BC;
extern s32 D_004832A8;
extern s32 D_004832AC;
extern GObj *D_004832F8;
extern s32 D_004832FC;
extern s32 D_00483304;
extern s32 D_00483300;
extern s32 D_004832D0;
extern s32 D_004832D8;
extern s32 D_004832E4;
extern s16 D_004832E8;
extern s8  D_004833E8;
extern s32 D_004833E0[2];
extern s32 D_004802C4;

extern "C" {
void TaskStatePushAll_27c220(void);
void TaskSetEnabled_27c2a0(s32, void *);
void UiSetWidgetVisible_290010(void *, s32, s32, s32);
void memcpy(void *, void *, s32);
void *GetGameData_1fede0(void);
void *InvFindInCategoryRange_3c8370(s32, s16, s32, s32, s32, s32);
s32 InvObjCastToCage_3d3c80(void *);
void InsectCageItemIconReset_386070(void *);
void *GetNpcDataHeap_1fdd70(void);
void MemStackHeapAlloc_14db10(void *, s32, s32, s32);
s32 MemStackAllocQw_14d950(void *, s32);
void MemStackReturnToOwnerMaybe_14dad0(void *);
void MemStackInit_14d810(void *, s32, s32);
u32 strlen(void *);
void strcpy(void *, void *);
s32 MemStackNew_14e1b0(s32, void *);
s32 ConstructNewArray_100710(s32, void *, s32, s32, s32);
void MemStackCtor_14e030(void);
void MenuObjCtor_38be10(void);
void *MemStackNew_14e230(s32, void *);
void ModelObjExCtor_1c4920(void *);
s32 MemStackAllocAligned64_14da10(void *, s32);
void InsectCageMsgListInit_384880(void *, void *);
void GuardEffectCtor_2d90f0(void *);
void InsectCageModelObjCtorMaybe_38bdd0(void *);
void Character2Ctor_1ef2d0(void *);
void BitArray16Ctor_3842e0(void *);
void MenuObjSetInit_384e10(void *);
void LoadHandleArrayReset_28b160(s32, s32);
s32 LoadHandleRequestFile_28b550(void *, s32, s32, s32);
void LoaderQueueSeparatorGlobal_28afd0(void);
void InsectCageMenuOpen_38b9a0(void);
}

void InsectCageMenuOpen_38b9a0(void)
{
    Q96 bq;
    S96 aw;
    void *ent;
    void *hh;
    void *base;
    void *o;
    u8 *fp;
    s32 *ip;
    void *r;
    s32 k;
    s32 i;
    s32 v;
    u8 *c;
    u8 *d;

    D_0047FBD0 = -1;
    D_00483298 = 0;
    D_0048329C = 0;
    TaskStatePushAll_27c220();
    TaskSetEnabled_27c2a0(0, D_00463FE8);
    TaskSetEnabled_27c2a0(0, D_00464000);
    UiSetWidgetVisible_290010(D_004DB1B0, 0x15, 0, -1);
    aw = *(S96 *)(D_00482374 + 0x10);
    bq = *(Q96 *)&aw;
    memcpy(D_004E92C0, &bq, 0x60);
    ent = GetGameData_1fede0();
    for (k = 0; k < 3; k++) {
        fp = &D_00483338[k];
        ip = &D_00483340[k];
        *fp = 0;
        *ip = 0;
        r = InvFindInCategoryRange_3c8370(*(s32 *)((u8 *)ent + 0x18), D_00463E20[k], 0, -1, 0, 0);
        if (r != 0) {
            *fp = 1;
            *ip = InvObjCastToCage_3d3c80(r);
        }
    }
    D_0047FBD4 = -1;
    D_0047FBD8 = -1;
    D_00483334 = 0;
    InsectCageItemIconReset_386070(D_004E9510);
    InsectCageItemIconReset_386070(D_004E9530);
    D_004832B8 = 0;
    D_004832BC = 0;
    hh = GetNpcDataHeap_1fdd70();
    MemStackHeapAlloc_14db10(hh, 2, 0, 0x40);
    k = MemStackAllocQw_14d950(hh, 0x21999);
    MemStackReturnToOwnerMaybe_14dad0(hh);
    MemStackInit_14d810(D_004E9320, k, 0x21999);
    if (strlen(D_00464018) < 0x10) {
        strcpy(D_004E9320, D_00464018);
    }
    base = D_004E9320;
    D_004832A8 = ConstructNewArray_100710(MemStackNew_14e1b0(0x220, base), (void *)MemStackCtor_14e030, 0, 0x58, 6);
    D_004832AC = ConstructNewArray_100710(MemStackNew_14e1b0(0x3120, base), (void *)MenuObjCtor_38be10, 0, 0x9D0, 5);
    o = MemStackNew_14e230(0x790, base);
    if (o != 0) {
        ModelObjExCtor_1c4920(o);
        *(void **)((u8 *)o + 0x1B0) = D_00470F50;
    }
    D_004832F8 = (GObj *)o;
    D_004832FC = D_004832A8 + 0x1B8;
    D_004832F8->v21();
    MemStackInit_14d810((void *)D_004832FC, MemStackAllocAligned64_14da10(base, 0x2A00), 0x2A00);
    D_00483304 = MemStackAllocQw_14d950(base, 0xF0);
    D_00483300 = 0;
    InsectCageMsgListInit_384880(&D_004832D0, base);
    if ((o = MemStackNew_14e230(0x4160, base)) != 0) {
        c = (u8 *)o + 0x10;
        do {
            GuardEffectCtor_2d90f0(c);
            c += 0x340;
        } while (c < (u8 *)o + 0x1390);
        d = (u8 *)o + 0x13B0;
        do {
            InsectCageModelObjCtorMaybe_38bdd0(d);
            d += 0x7A0;
        } while (d < (u8 *)o + 0x22F0);
        c = (u8 *)o + 0x22F0;
        do {
            Character2Ctor_1ef2d0(c);
            c += 0x790;
        } while (c < (u8 *)o + 0x3210);
        Character2Ctor_1ef2d0((u8 *)o + 0x3220);
        Character2Ctor_1ef2d0((u8 *)o + 0x39C0);
        BitArray16Ctor_3842e0((u8 *)o + 0x4155);
    }
    D_004832D8 = (s32)o;
    MenuObjSetInit_384e10(o);
    D_004832E4 = MemStackNew_14e1b0(0x188, base);
    LoadHandleArrayReset_28b160(D_004832E4, 7);
    D_004832E8 = 0;
    if (D_004833E8 == 0) {
        D_004833E0[0] = D_004802C4;
        D_004833E8 = 1;
    }
    for (i = 0; (v = D_004833E0[i]) != 0; i++) {
        if (LoadHandleRequestFile_28b550((u8 *)D_004832E4 + i * 0x38, v, 0, 0) >= 0) {
            D_004832E8 = D_004832E8 + 1;
        }
    }
    LoaderQueueSeparatorGlobal_28afd0();
}
