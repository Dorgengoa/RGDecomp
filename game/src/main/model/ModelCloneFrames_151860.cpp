/* rgp:protos */
#line 1
#include "types.h"

typedef rg_u128 u128;

struct Mat {
    u128 q[4];
};

struct ObjBase {
    u8 pad0[0xE0];
};

class Obj : public ObjBase {
public:
    VC_VPTR_MEMBER;
    
    void reset() { VCM0(void, 0x10); }
    u8 padE4[0xC];
};

struct Entry {
    char *name;
};

struct List {
    s32 n;
    Entry **items;
};

struct Names {
    char *name;
};

struct Node {
    u8 pad0[4];
    Names *m4;
    u8 pad8[0x20];
    s8 m28;
};

struct SelfBase {
    u8 pad0[0x104];
    List *m104;
    Mat *m108;
    s32 m10C;
    s32 *m110;
    u8 pad114[0x180 - 0x114];
    u8 m180[0x10];
    u8 m190[0x10];
    u8 m1A0[0x10];
};

class Self : public SelfBase {
public:
    VC_VPTR_MEMBER;
    void update() { VCM0(void, 0xC); }
};

struct NewList {
    s32 n;
    Obj **items;
};

extern "C" {
s32 ConstructNewArray_100710(void *, void *, void *, s32, s32);
void FrameSetParent_149e90(Node *, Node *);
void ModelFrameSetScaleLink_14a4e0(Node *, void *);
void ModelFrameSetRotLink_14a500(Node *, void *);
void ModelFrameSetPosLink_14a530(Node *, void *);
s32 FrameDupXformSlots_14a5f0(Node *, s32);
s32 FrameDupName_14a700(Obj *, s32);
void FrameCopyUnlinked_14a790(Node *, Obj *);
void *MemStackNew_14e1b0(s32, s32);
NewList * MemStackNew_14e230(s32, void *);
s32 ParallelArray3Alloc_152ea0(NewList *, s32, s32);
Node *ArrayGetChecked_152fd0(void *, s32);
void ParallelArray3Clear_153010(NewList *);
void ModelFrameCtor_150a90(void);
}

static inline bool streq(s8 *a, s8 *b)
{
    s8 c;

    if (*a != *b) {
        return false;
    }
    while ((c = *a) != 0 || *b != 0) {
        if (c != *b) {
            return false;
        }
        a++;
        b++;
    }
    return true;
}

#pragma opt_loop_invariants off
extern "C" s32 ModelCloneFrames_151860(Self *self, s32 heap) {
    s32 i;
    s32 ok;
    List *list;
    s32 n;
    NewList *nl;
    Mat *mats;
    Obj *objs;

    Obj *o;

    Node *src;
    s32 *old;
    s32 j;
    Node *a;
    Node *b;
    Names *names;
    char *name;
    List *lst;
    s32 k;
    s32 kk;
    s32 cnt;
    Entry *e;
    char *s;
    char *t;
    s32 eq;
    Node *c;

    list = self->m104;
    if (list == 0) {
        return 1;
    }
    n = list->n;
    if (n == 0) {
        return 1;
    }
    nl = MemStackNew_14e230(0x10, (void *)heap);
    if (nl != 0) {
        ParallelArray3Clear_153010(nl);
    }
    if (nl == 0) {
        return 0;
    }
    if (ParallelArray3Alloc_152ea0(nl, n, heap) == 0) {
        return 0;
    }
    mats = 0;
    if (self->m108 != 0) {
        mats = (Mat *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0x40 + 0x10, heap), 0, 0, 0x40, n);
    }
    ok = 1;
    objs = (Obj *)ConstructNewArray_100710(MemStackNew_14e1b0(n * 0xF0 + 0x10, heap), (void *)ModelFrameCtor_150a90, 0, 0xF0, n);
    if (objs == 0) {
        return 0;
    }
    for (i = 0; i < n; i++) {
        if (mats != 0) {
            Mat *sm = &self->m108[i];
            Mat *dst = &mats[i];
            dst->q[0] = sm->q[0];
            dst->q[1] = sm->q[1];
            dst->q[2] = sm->q[2];
            dst->q[3] = sm->q[3];
        }
        o = &objs[i];
        nl->items[i] = o;
        src = ArrayGetChecked_152fd0(self->m104, i);
        if (src != 0) {
            FrameCopyUnlinked_14a790(src, o);
            ok &= ((unsigned char)FrameDupName_14a700(o, heap));
        } else {
            o->reset();
        }
    }
    self->m108 = mats;
    if (self->m10C > 0) {
        old = self->m110;
        if (old != 0) {
            self->m110 = (s32 *)MemStackNew_14e1b0(self->m10C * 4, heap);
            for (j = 0; j < self->m10C; j++) {
                self->m110[j] = old[j];
            }
        }
    }
    for (i = 0; i < n; i++) {
        a = ArrayGetChecked_152fd0(self->m104, i);
        b = ArrayGetChecked_152fd0(nl, i);
        if (a == 0 || b == 0) {
            continue;
        }
        names = a->m4;
        if (a->m28 != 0) {
            names = 0;
        }
        if (names != 0) {
            name = names->name;
            lst = self->m104;
            if (name == 0 || lst == 0) {
                kk = -1;
            } else {
                cnt = lst->n;
                for (k = 0; k < cnt; k++) {
                    e = lst->items[k];
                    if (e == 0) {
                        continue;
                    }
                    s = e->name;
                    if (s == 0) {
                        continue;
                    }
                    if (streq((s8 *)s, (s8 *)name)) {
                        kk = k;
                        goto found;
                    }
                }
                kk = -1;
            }
        found:
            c = ArrayGetChecked_152fd0(nl, kk);
            if (c != 0) {
                FrameSetParent_149e90(b, c);
                ok &= FrameDupXformSlots_14a5f0(b, heap);
            }
        } else {
            ModelFrameSetPosLink_14a530(b, self->m180);
            ModelFrameSetRotLink_14a500(b, self->m190);
            ModelFrameSetScaleLink_14a4e0(b, self->m1A0);
        }
    }
    if (ok != 0) {
        self->m104 = (List *)nl;
    }
    self->update();
    return ok;
}
