#include "types.h"

class V {
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual s32 f70(s32);
};

typedef struct {
    u8 pad0[8];
    V *unk8;
    u8 padC[4];
    V *unk10;
} Holder;

typedef struct {
    u8 pad0[0x60];
    Holder *unk60;
} Obj;

typedef struct {
    u8 pad0[8];
    s32 unk8[2];
} E1;

typedef struct {
    s16 unk0;
    u8 pad2[0x2E - 2];
    s16 unk2E;
    s32 unk30;
} E2;

typedef struct {
    s16 b : 10;
} R;

typedef struct {
    s32 a;
    s32 b;
} Iter;

extern "C" {
void *IterNext_370040(Iter *);
void IterReset_3700f0(Iter *);
void IterInit_370170(Iter *, void *);
R *TableFindMaxKey_401580(s32);
}

static inline void *NextA(Iter *p) { return IterNext_370040(p); }
extern "C" s32 WorldSubsysLinkIds_400b80(u8 *arg0, Obj *arg1)
{
    Iter it;
    void *e;
    s32 i;
    s32 *p;
    s32 r;
    R *q;
    u8 *t;

    if (arg1 == NULL) {
        return 0;
    }
    t = arg0;
    if (t != NULL) {
        t += 0x88;
    }
    IterInit_370170(&it, t);
    while ((e = NextA(&it)) != NULL) {
        for (i = 0; i < 2; i++) {
            p = &((E1 *)e)->unk8[i];
            *p = arg1->unk60->unk8->f70(*(s16 *)p);
        }
    }
    IterReset_3700f0(&it);
    while ((e = IterNext_370040(&it)) != NULL) {
        r = arg1->unk60->unk10->f70(((E2 *)e)->unk0);
        ((E2 *)e)->unk30 = r;
        if (r != 0 && (q = TableFindMaxKey_401580(r)) != NULL) {
            ((E2 *)e)->unk2E = q->b;
        } else {
            ((E2 *)e)->unk2E = 0;
        }
    }
    return 1;
}
