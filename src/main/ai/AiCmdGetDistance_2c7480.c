#include "types.h"

typedef unsigned int u128 __attribute__((mode(TI)));

typedef struct Slot {
    u8 b[8];
} Slot;

typedef struct Vec {
    f32 x, y, z, w;
} Vec;

typedef struct Chr {
    u8 pad000[0x180];
    Vec pos;
    u8 pad190[0x4C8 - 0x190];
    f32 radius;
} Chr;

typedef struct Info {
    s16 x0;
    s16 id;
} Info;

extern s32 D_004DB920[0x100];
extern f32 D_0047D240;

extern s32 ScriptSlotGetInt_2cc9c0(Slot *s);
extern Chr *ObjRecGetLiveObject_1c4a90(s32 a, s32 b);
extern s32 ModelGetRootFrame_1511a0(Chr *c);
extern s32 GetCharaResMgr_1fdb60(void);
extern Info *CharaResFindById_1f0530(s32 a, s32 b);
extern s32 ModelGetFrame_1511f0(Chr *c, s32 n);
extern void FrameGetWorldPos_148f30(s32 h, Vec *v);
extern f32 VecDistance_13d3d0(Vec *a, Vec *b);
extern void ScriptSlotStoreFloatRef_2cc8e0(Slot *args, f32 v);

s32 AiCmdGetDistance_2c7480(Slot *args, s32 argc) {
    Vec pa;
    Vec pb;
    s32 world;
    Slot *self;
    s32 mode;
    f32 dist;
    s32 ia;
    s32 ib;
    Chr *ca;
    Chr *cb;
    s32 ha;
    s32 hb;
    Info *info;
    s32 id;
    f32 ra;
    f32 rb;

    if (argc < 3) {
        return 0;
    }
    world = D_004DB920[0];
    dist = -1.0f;
    self = args;
    args++;
    mode = 0;
    ia = ScriptSlotGetInt_2cc9c0(args++);
    ib = ScriptSlotGetInt_2cc9c0(args++);
    if (argc == 4) {
        mode = ScriptSlotGetInt_2cc9c0(args);
    }
    if (ia < 0 || ib < 0) {
        return 1;
    }
    ca = ObjRecGetLiveObject_1c4a90(world, ia);
    cb = ObjRecGetLiveObject_1c4a90(world, ib);
    if (ca == 0) {
        return 1;
    }
    if (cb == 0) {
        return 1;
    }
    ha = ModelGetRootFrame_1511a0(ca);
    hb = ModelGetRootFrame_1511a0(cb);
    info = CharaResFindById_1f0530(GetCharaResMgr_1fdb60(), ib);
    id = -1;
    if (info != 0) {
        id = info->id;
    }
    if (id >= 0x2F09 && id < 0x2F0F) {
        hb = ModelGetFrame_1511f0(cb, 9);
    }
    if (ha != 0) {
        FrameGetWorldPos_148f30(ha, &pa);
    } else {
        *(u128 *)&pa = *(u128 *)&ca->pos;
    }
    if (hb != 0) {
        FrameGetWorldPos_148f30(hb, &pb);
    } else {
        *(u128 *)&pb = *(u128 *)&cb->pos;
    }
    ra = D_0047D240 * ca->radius;
    rb = D_0047D240 * cb->radius;
    if (id >= 0x2F09 && id < 0x2F0F) {
        rb = 30.0f;
    }
    switch (mode) {
    case 0:
        dist = VecDistance_13d3d0(&pa, &pb);
        break;
    case 1:
        dist = VecDistance_13d3d0(&pa, &pb) - (ra + rb);
        break;
    case 2:
        pb.y = 0;
        pa.y = 0;
        dist = VecDistance_13d3d0(&pa, &pb);
        break;
    case 3:
        pb.y = 0;
        pa.y = 0;
        dist = VecDistance_13d3d0(&pa, &pb) - (ra + rb);
        break;
    }
    ScriptSlotStoreFloatRef_2cc8e0(self, dist);
    return 1;
}
