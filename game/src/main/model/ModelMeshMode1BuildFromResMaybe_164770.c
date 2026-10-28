/* rgp:protos */
#define RGP_SELF_DupBuf 1
#define RGP_SELF_IsValid 1
#define RGP_SELF_ModelMeshMode1BuildFromResMaybe_164770 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef rg_u128 u128;

typedef struct Hdr {
    u8 pad0[0x6C];
    u16 x6C;
} Hdr;

typedef struct Src {
    s32 a;
    s32 b;
    s32 c;
    void *p0;
    void *p1;
    void *p2;
    void *p3;
    s32 pad1C;
    u128 q20;
    u128 q30;
} Src;

typedef struct Blk {
    s32 pad0;
    s32 a;
    s32 b;
    s32 c;
    void *p0;
    void *p1;
    void *p2;
    void *p3;
} Blk;

typedef struct Obj {
    u8 pad0[0x20];
    u128 q20;
    u128 q30;
    u8 pad40[0x20];
    s32 x60;
    s32 x64;
    s32 x68;
    s32 pad6C;
    u8 x70[0x10];
    u8 x80[0x10];
    u8 x90[0x10];
    Blk blk;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memcpy(void *, const void *, u32);

static inline u8 IsValid(Hdr **h) {
    u8 r = 0;
    if (*h != 0 && (*h)->x6C == 1) {
        r = 1;
    }
    return r;
}

static inline void *DupBuf(s32 heap, void *src, s32 bits, s32 n) {
    s32 size;
    s32 blocks;
    void *p;
    if (n <= 0) {
        return 0;
    }
    size = n * bits / 8;
    blocks = size / 16;
    if (size % 16 != 0) {
        blocks++;
    }
    p = MemStackAllocQw_14d950(heap, blocks);
    if (p == 0) {
        return 0;
    }
    memcpy(p, src, size);
    return p;
}

s32 ModelMeshMode1BuildFromResMaybe_164770(Obj *arg0, Hdr **arg1, s32 arg2, s32 arg3) {
    Blk *b;
    Src *s;

    if (arg1 == 0 || (u8)IsValid(arg1) == 0) {
        return 0;
    }
    b = &arg0->blk;
    s = ((Src *)ModelResGetVertexBufMaybe_14cd90(arg1));
    if (s == 0) {
        return 0;
    }
    arg0->x60 = 0x20;
    arg0->x64 = 0x20;
    arg0->x68 = 0x20;
    VecSetOnes_13e180(arg0->x70);
    ModelResGetPosScale_14ccb0(arg1, arg0->x80);
    ModelResGetUvScale_14cbd0(arg1, arg0->x90);
    b->a = s->a;
    b->b = s->b;
    b->c = s->c;
    if (arg3 != 0) {
        b->p0 = DupBuf(arg2, s->p0, 32, b->c * 6);
        b->p1 = DupBuf(arg2, s->p1, arg0->x64, b->c * 6);
        b->p2 = DupBuf(arg2, s->p2, arg0->x68, b->c * 4);
        b->p3 = DupBuf(arg2, s->p3, 8, b->c * 4);
    } else {
        b->p0 = s->p0;
        b->p1 = s->p1;
        b->p2 = s->p2;
        b->p3 = s->p3;
    }
    arg0->q20 = s->q30;
    *(s32 *)((u8 *)arg0 + 0x2C) = 0x3F800000;
    arg0->q30 = s->q20;
    *(s32 *)((u8 *)arg0 + 0x3C) = 0x3F800000;
    return 1;
}
