/* rgp:protos */
#line 1
#pragma opt_loop_invariants off
#include "types.h"

class Sub {
    u8 pad[0xE0];
public:
    VC_VPTR_MEMBER;
    
    void v10() { VCM0(void, 0x10); }
};

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    u8 pad18[0x2C - 0x18];
    u8 *unk2C;
    s32 unk30;
    u8 pad34[0x38 - 0x34];
    u8 *unk38;
    s32 unk3C;
    u8 buf40[0x20];
    u8 buf60[0x28];
} Params;

typedef struct {
    u8 pad0[0x1B0];
    u8 *vt;
    u8 pad1B4[0x228 - 0x1B4];
    u8 a[4][8];
    u8 b[4][8];
    u8 pad268[0x270 - 0x268];
    u8 c[0x1C0];
    u8 d[0xC0];
} Big;

extern "C" {
u8 *MemStackNew_14e230(s32, s32);
void MotionListInit_1726f0(u8 *);
void ModelObjBaseInit_1867b0(u8 *);
void ModelObjBaseCtor_1954e0(Big *, int, int, int);
void ModelAttachSlotCtor_1954c0(u8 *);
void ModelCtor_195470(u8 *, int, int, int);
void ModelObjShadowFrameMapCtor_195450(u8 *);
void ModelObjInit_1ae420(Big *);
void InfoCfgParseThunk_1ac1e0(Big *, Params *);
void ModelObjBaseCopy_186820(Big *, u8 *, s32);
void *memset(void *, s32, u32);
extern u8 D_0046FFA0[];
extern u8 D_0046FFC0[];
extern u8 D_00470440[];
extern u8 D_00470650[];
extern u8 D_00470690[];
extern u8 D_00470ED0[];
}

extern "C" u8 *MapModelCreate_1952b0(s32 arg0, s32 arg1, s32 arg2) {
    Big big __attribute__((aligned(16)));
    Params prm __attribute__((aligned(16)));
    u8 *q;
    u8 *r;
    u8 *p;

    p = MemStackNew_14e230(0x200, arg2);
    if (p != NULL) {
        *(u8 **)(p + 0x1B0) = D_0046FFC0;
        *(u8 **)(p + 0xF0) = D_0046FFA0;
        ((Sub *)(p + 0x10))->v10();
        *(u8 **)(p + 0x1B0) = D_00470440;
        *(u8 **)(p + 0x1B0) = D_00470690;
        MotionListInit_1726f0(p + 0x1F0);
        *(u8 **)(p + 0x1B0) = D_00470650;
    }
    if (p == NULL) {
        return 0;
    }
    ModelObjBaseInit_1867b0(p);
    ModelObjBaseCtor_1954e0(&big, 0, 0, 0);
    q = big.a[0];
    big.vt = D_00470ED0;
    do {
        ModelAttachSlotCtor_1954c0(q);
        q += 8;
        r = big.b[0];
    } while (q < r);
    do {
        ModelAttachSlotCtor_1954c0(r);
        r += 8;
    } while (r < big.b[4]);
    ModelCtor_195470(big.c, 0, 0, 0);
    ModelObjShadowFrameMapCtor_195450(big.d);
    ModelObjInit_1ae420(&big);
    memset(&prm, 0, sizeof(prm));
    prm.unk2C = prm.buf40;
    prm.unk30 = 8;
    prm.unk38 = prm.buf60;
    prm.unk3C = 8;
    prm.unk14 = -1;
    prm.unk0 = arg0;
    prm.unk4 = arg1;
    prm.unk8 = arg2;
    prm.unkC = arg2;
    prm.unk10 = 0;
    InfoCfgParseThunk_1ac1e0(&big, &prm);
    ModelObjBaseCopy_186820(&big, p, 0);
    return p;
}
