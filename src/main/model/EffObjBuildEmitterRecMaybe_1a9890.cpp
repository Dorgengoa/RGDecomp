#include "types.h"

typedef struct Info {
    u8 pad0[8];
    s32 x8;
    u8 padC[0x2C - 0xC];
    f32 x2C;
} Info;

typedef struct Node {
    struct Node *next;
    Info *x4;
} Node;

typedef struct Src {
    u8 pad0[8];
    s32 x8;
    u8 padC[0x54 - 0xC];
    s32 x54;
    u8 pad58[4];
    f32 x5C;
    u8 pad60[4];
    Node *x64;
} Src;

typedef struct Ent {
    s32 x0;
    s32 *x4;
    s32 x8;
    s32 xC;
    s32 x10;
} Ent;

typedef struct Dst {
    u8 pad0[8];
    s32 x8;
    u8 padC[0xB4 - 0xC];
    s32 xB4;
    u8 padB8[0x100 - 0xB8];
    s32 x100;
    s32 *x104;
    Ent *x108;
} Dst;

extern "C" {
extern Ent *ConstructNewArray_100710(s32, void *, s32, s32, s32);
extern s32 MemStackAllocQw_14d950(s32, s32);
extern s32 MemStackNew_14e1b0(s32, s32);
extern void EffEmitterRecCtorMaybe_1a9ae0(void);
}

extern "C" s32 EffObjBuildEmitterRecMaybe_1a9890(Src *arg0, s32 arg1, Dst *arg2) {
    s32 n;
    s32 v;
    bool ok;
    Node *p;
    s32 cnt;
    s32 i;
    s32 k;
    f32 s;
    s32 m;
    s32 arr;
    s32 mem;
    Ent *e;
    s32 ptr;
    s32 j;

    n = arg0->x8;
    v = MemStackNew_14e1b0(n << 4, arg1);
    arg2->x8 = n;
    arg2->xB4 = v;
    if (v == 0 && n > 0) {
        ok = 0;
    } else {
        ok = 1;
    }
    if (!ok) {
        return 0;
    }
    p = arg0->x64;
    if (p == NULL) {
        return 0;
    }
    p = p->next;
    cnt = 1;
    while (p != NULL) {
        p = p->next;
        cnt++;
    }
    if (cnt == 0) {
        return 0;
    }
    arg2->x104 = (s32 *)MemStackNew_14e1b0(cnt * 4, arg1);
    if (arg2->x104 == NULL) {
        return 0;
    }
    arg2->x100 = cnt;
    for (i = 0; i < cnt; i++) {
        arg2->x104[i] = 0;
    }
    arg2->x108 = ConstructNewArray_100710(MemStackNew_14e1b0(cnt * 0x14 + 0x10, arg1), EffEmitterRecCtorMaybe_1a9ae0, 0, 0x14, cnt);
    if (arg2->x108 == NULL) {
        return 0;
    }
    p = arg0->x64;
    i = 0;
    while (p != NULL) {
        k = p->x4->x8 + 0xC;
        s = arg0->x5C + (f32)arg0->x54;
        m = (s32)(2.0f + s * p->x4->x2C);
        arr = MemStackNew_14e1b0(m * 4, arg1);
        mem = MemStackAllocQw_14d950(arg1, k * m);
        if (mem != 0) {
            e = &arg2->x108[i];
            e->xC = m;
            e->x0 = mem;
            e->x4 = (s32 *)arr;
            e->x8 = k << 4;
            e->x10 = 0;
            ptr = e->x0;
            for (j = 0; j < e->xC; j++) {
                e->x4[j] = ptr;
                ptr += e->x8;
            }
        } else {
            return 0;
        }
        p = p->next;
        i++;
    }
    return 1;
}
