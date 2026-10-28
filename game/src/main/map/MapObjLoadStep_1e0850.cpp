/* rgp:protos */
#line 1
#include "types.h"

class VC {
public:
    u8 pad[0x1B0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void v50() { VCM0(void, 0x50); }
};

struct Big {
    u8 pad0[0x1B0];
    void *vp;
    u8 pad1B4[0x4DC - 0x1B4];
    s32 f4DC;
    u8 pad4E0[0x538 - 0x4E0];
    s32 f538;
    s32 f53C;
};

struct Obj {
    s16 f0;
    s16 f2;
    s32 f4;
    s32 f8;
    Big *c;
    s32 f10;
    s16 f14;
    s16 state;
};

struct Init {
    s32 a;
    void *b;
    s32 h0;
    s32 h1;
    s32 h2;
    s32 f14;
    s32 f18;
    u8 pad1C[0x2C - 0x1C];
    void *p2C;
    s32 n30;
    s32 pad34;
    void *p38;
    s32 n3C;
    u8 buf40[0x20];
    u8 buf60[0x28];
};

extern "C" {
extern Big *MemStackNew_14e230(s32, s32);
extern void ModelObjPlayMotionByName_1867a0(Big *, void *, s32);
extern void InfoCfgParseAll_1afd00(Big *, Init *);
extern void ModelObjExCtor_1c4920(Big *, int, int, int);
extern void LoadHandlePoll_1ccb00(Obj *);
extern void LoaderReleaseHandle_1ccb70(Obj *);
extern void MapObjRelease_1e0a90(Obj *);
extern s32 GetEffectMgr_2d9040(void);
extern void *memset(void *, s32, u32);
extern u8 D_0045B428[];
extern u8 D_0045B438[];
extern u8 D_0045B440[];
extern u8 D_00470F50[];
extern s32 D_0047E180;
}

extern "C" void MapObjLoadStep_1e0850(Obj *obj, s32 heap)
{
    Big *b;
    __attribute__((aligned(16))) unsigned char rgp_blk1[(0x0 + sizeof(Init)) + (0x88) + (0x90)];
    s32 v;
    Big *c;
    s32 t;

    if (obj->state != 1) {
        return;
    }
    LoadHandlePoll_1ccb00(obj);
    if (heap == 0) {
        goto fail;
    }
    if (obj->f2 == -1) {
        goto fail;
    }
    if (obj->f2 == 0) {
        return;
    }
    b = MemStackNew_14e230(0x790, heap);
    if (b != 0) {
        ModelObjExCtor_1c4920(b, 0, 0, 0);
        b->vp = D_00470F50;
    }
    obj->c = b;
    if (b == 0) {
        goto fail;
    }
    memset(&(*(Init *)(rgp_blk1 + 0x0)), 0, sizeof((*(Init *)(rgp_blk1 + 0x0))));
    (*(Init *)(rgp_blk1 + 0x0)).p2C = (*(Init *)(rgp_blk1 + 0x0)).buf40;
    (*(Init *)(rgp_blk1 + 0x0)).n30 = 8;
    (*(Init *)(rgp_blk1 + 0x0)).p38 = (*(Init *)(rgp_blk1 + 0x0)).buf60;
    (*(Init *)(rgp_blk1 + 0x0)).n3C = 8;
    (*(Init *)(rgp_blk1 + 0x0)).a = obj->f4;
    (*(Init *)(rgp_blk1 + 0x0)).b = D_0045B428;
    (*(Init *)(rgp_blk1 + 0x0)).h0 = heap;
    (*(Init *)(rgp_blk1 + 0x0)).h1 = heap;
    (*(Init *)(rgp_blk1 + 0x0)).h2 = heap;
    (*(Init *)(rgp_blk1 + 0x0)).f14 = obj->f10;
    (*(Init *)(rgp_blk1 + 0x0)).f18 = 0;
    ((VC *)obj->c)->v50();
    v = GetEffectMgr_2d9040() + 0x58;
    c = obj->c;
    c->f53C = v;
    if (v != 0) {
        t = D_0047E180;
        D_0047E180 = t + 1;
        c->f538 = t;
    }
    InfoCfgParseAll_1afd00(obj->c, &(*(Init *)(rgp_blk1 + 0x0)));
    obj->c->f4DC = (*(Init *)(rgp_blk1 + 0x0)).f14;
    obj->state = 2;
    switch (obj->f14) {
    case 0:
        ModelObjPlayMotionByName_1867a0(obj->c, D_0045B438, 4);
        break;
    case 1:
        ModelObjPlayMotionByName_1867a0(obj->c, D_0045B440, 4);
        break;
    }
    LoaderReleaseHandle_1ccb70(obj);
    return;
fail:
    obj->state = -1;
    MapObjRelease_1e0a90(obj);
}
