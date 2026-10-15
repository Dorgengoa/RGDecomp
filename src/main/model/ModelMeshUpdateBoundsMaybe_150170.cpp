#include "types.h"
#pragma opt_common_subs off

class Obj {
public:
    u8 pad00[0x20];
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x4];
    f32 unk30;
    f32 unk34;
    f32 unk38;
    u8 pad3C[0x14];
    virtual void v08();
    virtual s32 v0C(s32);
};

class Obj2 : public Obj {
public:
    u8 pad54[0x100 - 0x54];
    u8 unk100[0x20];
    f32 unk120;
    u8 pad124[0x4];
    s32 unk128;
    s32 unk12C;
    bool On() {
        if (unk128 <= 0) return false;
        if (unk12C == 0) return false;
        return true;
    }
    bool On2() {
        bool r = false;
        if (unk128 > 0 && unk12C != 0) r = true;
        return r;
    }
    bool On3() {
        if (unk128 > 0 && unk12C != 0) return true;
        return false;
    }
};

struct Sub {
    s32 m0;
    s32 m4;
    s32 m8;
};

struct Node {
    Node *next;
    u8 pad4[0xC];
    Sub sub;
};

struct Tbl {
    s32 m0;
    s32 *tbl;
};

struct Tbl2 {
    s32 m0;
    Obj2 **tbl;
};

struct Arg0 {
    u8 pad0[0x104];
    Tbl *p104;
};

struct Arg1 {
    u8 pad0[0xC];
    Tbl2 *unkC;
    u8 pad10[0x34];
    Node *unk44;
};

extern "C" void ModelCalcNodesBoundsMaybe_1531c0(void *arg0, void *arg1, Tbl *arg2, s32 arg3, u32 arg4, s32 arg5);

extern "C" void ModelMeshUpdateBoundsMaybe_150170(Arg0 *arg0, Arg1 *arg1)
{
                void * arg_h0;

    Node *node;
    Tbl2 *t2;
    Sub *sub;
    Obj2 *o;
    s32 n;
    bool ok;
    f32 f;

    node = arg1->unk44;
    t2 = arg1->unkC;
    while (node != NULL) {
        sub = &node->sub;
        if (arg0->p104->tbl[node->sub.m4] == 0) {
            return;
        }
        o = t2->tbl[sub->m8];
        if (o == NULL) {
            return;
        }
        if (o->v0C(2) != 0) {
            n = o->unk128;
            ok = false;
            if (n > 0) {
                if (o->unk12C != 0) {
                    ok = true;
                } else {
                    ok = ok;
                }
            }
            if (ok & 0xFF) {
                ModelCalcNodesBoundsMaybe_1531c0(&o->unk20, o->unk100, arg0->p104, sub->m4, o->unk12C, n);
                f = o->unk120;
                o->unk20 += f;
                o->unk24 += f;
                o->unk28 += f;
                o->unk30 -= f;
                o->unk34 -= f;
                o->unk38 -= f;
            }
        }
        node = node->next;
    }
}
