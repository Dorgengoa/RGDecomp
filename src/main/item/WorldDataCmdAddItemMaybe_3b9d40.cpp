#include "types.h"

typedef struct Arg { s32 a; s32 b; } Arg;

class VA {
public:
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
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual u8 *Find(s16);
};

class VB {
public:
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
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual void v51();
    virtual void v52();
    virtual void v53();
    virtual void v54();
    virtual void v55();
    virtual void v56();
    virtual void v57();
    virtual void v58();
    virtual void v59();
    virtual void v60();
    virtual void v61();
    virtual void v62();
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void Set(s8 *);
};

struct R40 { u8 pad[8]; VA *m8; };
struct R8 { u8 pad[0x40]; R40 *m40; };
struct R94 { u8 pad[8]; R8 *m8; u8 padc[0xc]; s32 m18; };
struct G {
    u8 pad[0x94];
    R94 *m94;
    u8 pad98[2];
    u8 b0 : 1;
    u8 b1 : 1;
    u8 b2 : 1;
    u8 b3 : 5;
};

extern "C" s8 *SlotGetInt_15f720(Arg *);
extern "C" s64 VariantGetInt_15f780(Arg *);
extern "C" void InvAddItemAtSlot_3c64c0(s32, s64, s64, s32, s32);
extern "C" s32 InvGetCageItem_3c8040(s32, s32);
extern "C" VB *InsectItemCreateWithRandomName_3cff30(s32, s16);
extern "C" s32 atoi(const s8 *);
extern G *D_004830F8;

extern "C" s32 WorldDataCmdAddItemMaybe_3b9d40(Arg *p)
{
    G *g;
    s64 a;
    s64 b;
    s8 *str;
    VB *vb;
    s32 i;
    s32 h;
    s32 cnt;
    u8 *r;

    g = D_004830F8;
    if (!g->b2) {
        return 1;
    }
    a = VariantGetInt_15f780(p++);
    b = VariantGetInt_15f780(p++);
    str = SlotGetInt_15f720(p);
    r = g->m94->m8->m40->m8->Find(b);
    r = (u8 *)(s32)r;
    if (r == 0) {
        return 1;
    }
    if (*(s8 *)(r + 2) == 0x14) {
        vb = 0;
        for (i = 0; i < 3; i++) {
            h = InvGetCageItem_3c8040(g->m94->m18, i);
            if (h == 0) continue;
            vb = InsectItemCreateWithRandomName_3cff30(h, *(s16 *)r);
            if (vb != 0) break;
        }
        if (vb != 0) {
            vb->Set(str);
        }
    } else {
        cnt = 1;
        if (str != 0 && *str == 0x2A) {
            cnt = atoi(str + 1);
        }
        InvAddItemAtSlot_3c64c0(g->m94->m18, b, a, cnt, 0);
    }
    return 1;
}
