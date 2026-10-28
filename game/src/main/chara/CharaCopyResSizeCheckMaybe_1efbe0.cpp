/* rgp:protos */
#line 1
#include "types.h"
#pragma opt_propagation off

class CEF {
public:
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * get(s16 a0) { return VCM(void *, (void *, s16), 0x70, a0); }
};

class CEG {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void fin() { VCM0(void, 0x58); }
};

extern "C" {
extern void MemStackHeapFree_14dcb0(s32, s32);
extern s32 MemStackHeapAllocFront_14dd10(s32, s32);
extern void Character2ResetMaybe_1aef80(u8 *);
extern void ModelObjExCopy_1aff40(s32, u8 *, u8 *);
extern void RecStackPop_1c4140(s32, s32);
extern s32 RecStackPush_1c4240(s32, s32);
extern u8 *RecStackGetSlot_1c4330(s32, s32);
extern void ModelObjExCtor_1c4920(u8 *, int, int, int);
extern s32 CharaDataGetNodeModel_1ed540(s32, s16, s32);
extern s32 GetCharaDataMgr_1fdb70(void);
extern void *GetWorldDataMgr_1fedf0(void);
extern u8 D_00470F50[];
}

extern "C" s32 CharaCopyResSizeCheckMaybe_1efbe0(u8 *arg0, s32 arg1, s64 arg2)
{
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(u8[0x784])) + (0x590) + (0x78c)];
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
    ModelObjExCtor_1c4920((*(u8 (*)[0x784])(rgp_blk1 + 0x0)), 0, 0, 0);
    *(u8 **)((*(u8 (*)[0x784])(rgp_blk1 + 0x0)) + 0x1B0) = D_00470F50;
    Character2ResetMaybe_1aef80((*(u8 (*)[0x784])(rgp_blk1 + 0x0)));
    ModelObjExCopy_1aff40(k, (*(u8 (*)[0x784])(rgp_blk1 + 0x0)), q);
    res = *(s32 *)(q + 0x2C) + 0x500;
    res = res + 0x791;
    ((CEG *)(*(u8 (*)[0x784])(rgp_blk1 + 0x0)))->fin();
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
