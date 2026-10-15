#include "types.h"
#pragma opt_propagation off

class CEF {
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
    virtual void *get(s16);
};

class CEG {
public:
    u8 pad[0x1B0];
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
    virtual void fin();
};

extern "C" {
extern void MemStackHeapFree_14dcb0(s32, s32);
extern s32 MemStackHeapAllocFront_14dd10(s32, s32);
extern void Character2ResetMaybe_1aef80(u8 *);
extern void ModelObjExCopy_1aff40(s32, u8 *, u8 *);
extern void RecStackPop_1c4140(s32, s32);
extern s32 RecStackPush_1c4240(s32, s32);
extern u8 *RecStackGetSlot_1c4330(s32, s32);
extern void ModelObjExCtor_1c4920(u8 *);
extern s32 CharaDataGetNodeModel_1ed540(s32, s16, s32);
extern s32 GetCharaDataMgr_1fdb70(void);
extern void *GetWorldDataMgr_1fedf0(void);
extern u8 D_00470F50[];
}

extern "C" s32 CharaCopyResSizeCheckMaybe_1efbe0(u8 *arg0, s32 arg1, s64 arg2)
{
    u8 sp60[0x784];
    s32 h;
    CEF *c;
    s16 *r;
    s32 k;
    s32 idx;
    u8 *q;
    s32 res;
    s32 z;

    h = GetCharaDataMgr_1fdb70();
    c = *(CEF **)(*(u8 **)((u8 *)GetWorldDataMgr_1fedf0() + 0x64) + 0xC);
    r = (s16 *)c->get(arg2);
    if (r == NULL) {
        return 0;
    }
    r = *(s16 **)((u8 *)r + 0x20);
    if (r == NULL) {
        return 0;
    }
    k = CharaDataGetNodeModel_1ed540(h, *r, 0);
    if (k == 0) {
        return 0;
    }
    idx = RecStackPush_1c4240(arg1, 0);
    q = RecStackGetSlot_1c4330(arg1, idx);
    if (q == NULL) {
        return 0;
    }
    ModelObjExCtor_1c4920(sp60);
    *(u8 **)(sp60 + 0x1B0) = D_00470F50;
    Character2ResetMaybe_1aef80(sp60);
    ModelObjExCopy_1aff40(k, sp60, q);
    res = *(s32 *)(q + 0x2C) + 0x500;
    res = res + 0x791;
    ((CEG *)sp60)->fin();
    RecStackPop_1c4140(arg1, idx);
    if (*(s32 *)(arg0 + 0xD00) == 0) {
        return 0;
    }
    z = MemStackHeapAllocFront_14dd10(*(s32 *)(arg0 + 0xD00), res);
    if (z == 0) {
        return 0;
    }
    MemStackHeapFree_14dcb0(*(s32 *)(arg0 + 0xD00), z);
    return res;
}
