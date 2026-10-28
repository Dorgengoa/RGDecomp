#include "types.h"

typedef struct {
    f32 a;
    f32 b;
    s16 c;
    s16 d;
    s16 e;
    s16 f;
    s32 g;
} Key;

typedef struct {
    s32 a;
    s32 b;
    s32 count;
    Key *keys;
} Track;

class Node {
public:
    Node *next;
    Node *prev;
    s32 heap;
    s32 id;
    Track t;
    VC_VPTR_MEMBER; void init() { VCM0(void, 0x8); }
};

typedef struct {
    u8 pad[0x1C];
    u8 *p[4];
    u8 pad2[4];
} Desc;

typedef struct {
    u8 pad[0x4D8];
    s32 m4D8;
    u8 pad4DC[0x14];
    s32 m4F0;
    s32 m4F4;
    s32 m4F8;
    s32 m4FC;
    s32 m500;
    s32 m504;
    f32 m508;
    f32 m50C;
    s32 m510;
    s32 m514;
    s32 m518;
    Node *m51C;
    f32 m520;
    f32 m524;
    f32 m528;
    f32 m52C;
    s32 m530;
    s32 m534;
    s32 m538;
    s32 m53C;
    u8 m540;
    u8 p541[3];
    u8 *m544;
    u8 m548[0x20];
    u8 m568[8];
    u8 m570[4];
    void *m574;
    u8 m578[4];
    void *m57C;
    u8 m580[4];
    void *m584;
    u8 m588[4];
    void *m58C;
} Obj;

extern "C" {
s32 ConstructNewArray_100710(s32, void (*)(void), s32, s32, s32);
s32 MemStackNew_14e1b0(s32, s32);
void *MemStackNew_14e230(s32, s32);
void ModelObjCopy_1acc00(Obj *, Obj *, s32);
void MotionEventListBindHandlers_1b4700(u8 *, Desc *);
void MotionEventListCopy_1b47f0(u8 *, u8 *, s32);
void *memset(void *, s32, u32);
void ParamScriptSeEntryCtor_1afa20(void);
extern u8 D_00471020[];
extern s32 D_0047E180;
void ModelObjExCopy_1aff40(Obj *src, Obj *dst, s32 heap);
}

void ModelObjExCopy_1aff40(Obj *src, Obj *dst, s32 heap) {
    Desc desc __attribute__((aligned(16)));
    s32 base;
    Node *s;
    s32 id;
    Track *st;
    Node *n;
    Track *dt;
    Node *p;
    s32 cnt;
    s32 v;
    s32 i;

    base = 0;
    if (heap != 0) {
        base = *(s32 *)(heap + 0x2C);
    }
    ModelObjCopy_1acc00(src, dst, heap);
    dst->m4F0 = src->m4F0;
    dst->m4F4 = src->m4F4;
    dst->m4F8 = src->m4F8;
    dst->m4FC = src->m4FC;
    dst->m500 = src->m500;
    dst->m504 = src->m504;
    dst->m508 = src->m508;
    dst->m50C = src->m50C;
    dst->m510 = src->m510;
    dst->m514 = src->m514;
    dst->m518 = src->m518;
    if (heap == 0) {
        dst->m51C = src->m51C;
    } else {
        dst->m51C = 0;
        for (s = src->m51C; s != 0; s = s->next) {
            id = s->id;
            st = &s->t;
            n = (Node *)MemStackNew_14e230(0x24, heap);
            if (n != 0) {
                *(u8 **)((u8 *)n + 0x20) = D_00471020;
                n->t.count = 0;
                n->t.keys = 0;
                n->init();
            }
            if (n == 0) {
                dt = 0;
            } else {
                n->init();
                n->heap = heap;
                n->id = id;
                if (dst->m51C == 0) {
                    dst->m51C = n;
                } else {
                    p = dst->m51C;
                    while (p != 0) {
                        if (p->next == 0) {
                            break;
                        }
                        p = p->next;
                    }
                    p->next = n;
                    if (n != 0) {
                        n->prev = p;
                    }
                }
                dt = &n->t;
            }
            *dt = *st;
            cnt = st->count;
            if (cnt > 0 && st->keys != 0) {
                v = ConstructNewArray_100710(MemStackNew_14e1b0(cnt * 0x14 + 0x10, heap), ParamScriptSeEntryCtor_1afa20, 0, 0x14, cnt);
                dt->keys = (Key *)v;
                if (v != 0) {
                    for (i = 0; i < st->count; i++) {
                        dt->keys[i] = st->keys[i];
                    }
                } else {
                    dt->count = 0;
                }
            }
        }
    }
    MotionEventListCopy_1b47f0(src->m568, dst->m568, heap);
    dst->m574 = dst;
    dst->m57C = dst;
    dst->m584 = dst;
    dst->m58C = dst;
    memset(&desc, 0, 0x30);
    desc.p[0] = dst->m570;
    desc.p[1] = dst->m578;
    desc.p[2] = dst->m580;
    desc.p[3] = dst->m588;
    MotionEventListBindHandlers_1b4700(dst->m568, &desc);
    dst->m520 = src->m520;
    dst->m524 = src->m524;
    dst->m528 = src->m528;
    dst->m52C = src->m52C;
    dst->m534 = src->m534;
    dst->m53C = src->m53C;
    if (dst->m53C != 0) {
        s32 t = D_0047E180;
        D_0047E180 = t + 1;
        dst->m538 = t;
    }
    dst->m540 = 1;
    dst->m544 = src->m548;
    if (heap != 0) {
        dst->m4D8 = src->m4D8 = *(s32 *)(heap + 0x2C) - base;
    }
}
