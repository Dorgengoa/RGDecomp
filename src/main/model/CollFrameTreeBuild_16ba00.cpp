#include "types.h"

typedef struct Handle {
    s32 x00;
    u8 pad04[0x1C];
} Handle;

typedef struct Src {
    s32 x00;
    u8 pad04[8];
    s32 child;
    s32 parent;
    u8 pad14[0xC];
    f32 m[4][4];
} Src;

struct Node {
    s32 x00;
    u8 pad004[0xDC];
    virtual void v0();
    virtual void v1();
    virtual void init();
    u8 pad0E4[0x10];
    void *xF4;
    u8 pad0F8[8];
};

struct VObj {
    u8 pad00[0x30];
    virtual void w00();
    virtual void w01();
    virtual void w02();
    virtual void w03();
    virtual void w04();
    virtual void w05();
    virtual void w06();
    virtual void w07();
    virtual void w08();
    virtual void w09();
    virtual void w10();
    virtual void w11();
    virtual void w12();
    virtual void w13();
    virtual void w14();
    virtual void w15();
    virtual void setup();
};

extern "C" {
void *ConstructNewArray_100710(void *, void *, s32, s32, s32);
void FrameSetParent_149e90(Node *, Node *);
void ModelFrameSetMatrix_14a190(Node *, f32 (*)[4]);
void ModelResGetMeshInfo_14c440(Handle *, void *, s32);
Src *ArrayGetChecked_14c7f0(void *, s32);
s32 ModelResGetFrameCount_14c850(void *);
s32 MemStackStrDup_14cff0(s32, s32);
void *MemStackNew_14e1b0(s32, s32);
u8 *MemStackNew_14e230(s32, s32);
void CollFrameCtor_16be30(void);
void CollMeshBuildFromRes_16c740(u8 *, void *, Handle *, s32);
void *memset(void *, s32, u32);
extern u8 D_00470250[];
extern u8 D_004702C0[];
Node *CollFrameTreeBuild_16ba00(void *model, s32 heap);
}

static inline bool hValid(Handle *h) {
    return h->x00 ? true : false;
}

static inline u8 *create(void *model, Handle *h, s32 heap) {
    u8 *c;
    if (model == 0) {
        return 0;
    }
    if (!hValid(h)) {
        return 0;
    }
    c = MemStackNew_14e230(0x60, heap);
    if (c != 0) {
        *(u8 **)(c + 0x30) = D_004702C0;
        *(s32 *)(c + 0x0) = 0;
        *(s32 *)(c + 0x4) = 0;
        memset(c + 0x10, 0, 0x20);
        *(u8 **)(c + 0x30) = D_00470250;
        *(s32 *)(c + 0x0) = 0;
        *(s32 *)(c + 0x4) = 0;
        memset(c + 0x10, 0, 0x20);
        *(s32 *)(c + 0x40) = 0;
        *(s32 *)(c + 0x44) = 0;
        *(s32 *)(c + 0x48) = 0;
        *(s32 *)(c + 0x4C) = 0;
        *(s32 *)(c + 0x50) = 0;
        *(s32 *)(c + 0x54) = 0;
        *(s32 *)(c + 0x58) = 0;
    }
    if (c == 0) {
        return 0;
    }
    ((VObj *)c)->setup();
    CollMeshBuildFromRes_16c740(c, model, h, heap);
    return c;
}

Node *CollFrameTreeBuild_16ba00(void *model, s32 heap) {
    f32 M[4][4];
    Handle h;
    s32 n;
    Src *src;
    f32 (*m)[4];
    bool ok;
    s32 cnt;
    Node *arr;
    Node *nodes;
    s32 i;
    s32 flag;
    Node *dst;
    s32 j;
    s32 k;


    if (model == 0) {
        return 0;
    }
    n = ModelResGetFrameCount_14c850(model);
    if (n == 0) {
        return 0;
    }
    arr = (Node *)ArrayGetChecked_14c7f0(model, 0);
    m = ((Src *)arr)->m;
    flag = 0;
    if (m[0][0] != 1.0f || m[0][1] != 0.0f || m[0][2] != 0.0f || m[0][3] != 0.0f) {
        flag = 1;
    }
    if (m[1][0] != 0.0f || m[1][1] != 1.0f || m[1][2] != 0.0f || m[1][3] != 0.0f) {
        flag = 1;
    }
    if (m[2][0] != 0.0f || m[2][1] != 0.0f || m[2][2] != 1.0f || m[2][3] != 0.0f) {
        flag = 1;
    }
    if (m[3][0] != 0.0f || m[3][1] != 0.0f || m[3][2] != 0.0f || m[3][3] != 1.0f) {
        flag = 1;
    }
    cnt = n + 1;
    arr = (Node *)ConstructNewArray_100710(MemStackNew_14e1b0((cnt << 8) + 0x10, heap), (void *)CollFrameCtor_16be30, 0, 0x100, cnt);
    nodes = arr;
    if (flag != 0) {
        arr->init();
        nodes = arr + 1;
    }
    for (i = 0; i < n; i++) {
        src = ArrayGetChecked_14c7f0(model, i);
        dst = &nodes[i];
        dst->init();
        for (j = 0; j < 4; j++) {
            for (k = 0; k < 4; k++) {
                M[k][j] = src->m[k][j];
            }
        }
        dst->x00 = MemStackStrDup_14cff0(src->x00, heap);
        ModelFrameSetMatrix_14a190(dst, M);
        if (src->parent < 0) {
            FrameSetParent_149e90(dst, 0);
        } else {
            FrameSetParent_149e90(dst, &nodes[src->parent]);
        }
        if (src->child >= 0) {
            ModelResGetMeshInfo_14c440(&h, model, src->child);
            if (hValid(&h)) {
                dst->xF4 = create(model, &h, heap);
            }
        }
    }
    if (flag != 0) {
        FrameSetParent_149e90(nodes, arr);
    }
    return arr;
}
