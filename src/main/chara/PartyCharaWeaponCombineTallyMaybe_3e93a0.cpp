#include "types.h"

class VT {
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
    virtual void *f70(s16);
};

struct H90 {
    u8 pad0[0xC];
    VT *mC;
    void *m10;
};

struct H40 {
    u8 pad0[8];
    VT *m8;
};

struct H8 {
    u8 pad0[0x40];
    H40 *m40;
    u8 pad44[0x90 - 0x44];
    H90 *m90;
};

struct Rec {
    s16 id;
    u8 c2;
    u8 c3;
    u8 c4;
    u8 c5;
};

struct E4 {
    s16 id;
    u16 f0 : 2;
    u16 f1 : 10;
    u16 f2 : 4;
};

struct T10 {
    u8 pad0[0x16A0];
    s16 n;
    E4 e[1];
};

struct A0 {
    u8 pad0[8];
    H8 *m8;
    u8 padC[4];
    T10 *m10;
    s32 m14;
};

extern "C" {
s32 CharaMgrPoolFindByDataId_3a8a70(s32, s32, s32, s32, s32, s32, s32);
s32 CharaIsInParty_3ae1d0(s32);
u8 *ListFindByKey_407ee0(void *, s32);
extern const s32 D_00466AD0[0x100];
}

extern "C" s32 PartyCharaWeaponCombineTallyMaybe_3e93a0(A0 *arg0)
{
    Rec *p2;
    T10 *t;
    Rec *base;
    s32 id;
    s32 r;
    E4 *e;
    s32 key;
    u8 *x;
    s32 i;
    s32 k;
    u8 *q;
    s32 n;
    s32 count;
    Rec *p;
    const s32 *ids;
    s32 j;
    void *o;

    count = 0;
    ids = D_00466AD0;
    base = (Rec *)arg0->m8->m90->m10;
    p = base;
    for (;;) {
        id = *ids;
        p->id = -1;
        p->c2 = 0;
        p->c3 = 0;
        p->c4 = 0;
        if (id < 0) {
            break;
        }
        r = CharaMgrPoolFindByDataId_3a8a70(arg0->m14, id, 1, 1, 0, 0, 0);
        if (r != 0 && CharaIsInParty_3ae1d0(r) != 0) {
            p->id = id;
            if ((o = arg0->m8->m90->mC->f70(id)) != NULL) {
                for (j = 0; j <= 1; j++) {
                    q = ListFindByKey_407ee0(o, j);
                    if (q != NULL) {
                        p->c2 += q[1];
                    }
                }
            }
            p++;
            count++;
        }
        ids++;
    }
    t = arg0->m10;
    n = t->n;
    e = t->e;
    for (i = 0; i < n; i++, e++) {
        x = (u8 *)arg0->m8->m40->m8->f70(e->id);
        if (x != NULL) {
            key = *(s16 *)(x + 8);
            p2 = base;
            for (k = 0; k < count; k++, p2++) {
                if (p2->id == key) {
                    p2->c3++;
                    if (e->f1 > 0) {
                        p2->c4++;
                    }
                }
            }
        }
    }
    return count;
}
