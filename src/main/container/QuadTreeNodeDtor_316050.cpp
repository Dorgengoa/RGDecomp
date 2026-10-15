#include "types.h"

class VE316050 {
public:
    u8 pad000[0xB0];
    virtual void *v00();
    virtual void *v01();
    virtual void *v02();
    virtual void *v03();
    virtual void *v04();
    virtual void *v05();
    virtual void *v06();
    virtual void *v07();
    virtual void *v08();
    virtual void *v09();
    virtual void *v10();
    virtual void *v11();
    virtual void *v12();
    virtual void *v13();
    virtual void *v14();
    virtual void *v15();
    virtual void *v16();
    virtual void *v17();
    virtual void *v18();
    virtual void *v19();
    virtual void *v20();
    virtual void *v21();
    virtual void *v22();
    virtual void *v23();
    virtual void *v24();
    virtual void *dt(s16);
};

struct Rep316050 {
    VE316050 *m00;
    s32 m04;
};

struct Node316050 {
    struct Rep316050 *m00;
    u8 pad004[0x4];
    struct Node316050 *m08;
};

struct Obj316050 {
    u8 pad000[0x14];
    struct Obj316050 *m14[4];
    struct Node316050 *m24;
};

extern "C" {
extern void *QuadTreeItemListDtor_315ad0(void *, s16);
extern void *JudgeObjectRefDtor_316220(void *, s16);
extern void OperatorDelete_100840(void *);
}

extern "C" void *QuadTreeNodeDtor_316050(Obj316050 *o, s16 flag)
{
    Obj316050 *a;
    Obj316050 *b;
    Node316050 *n;
    Node316050 *nx;
    Rep316050 *r;
    s32 i;
    s32 j;
    s32 k;
    s32 c;
    s32 ok;

    if (o != 0) {
        for (i = 0; i < 4; i++) {
            a = o->m14[i];
            if (a != 0) {
                for (j = 0; j < 4; j++) {
                    b = a->m14[j];
                    if (b != 0) {
                        for (k = 0; k < 4; k++) {
                            QuadTreeNodeDtor_316050(b->m14[k], -1);
                        }
                        QuadTreeItemListDtor_315ad0(&b->m24, -1);
                    }
                }
                if (&a->m24 != 0) {
                    n = a->m24;
                    while (n != 0) {
                        nx = n->m08;
                        JudgeObjectRefDtor_316220(n, -1);
                        n = nx;
                    }
                }
            }
        }
        if (&o->m24 != 0) {
            n = o->m24;
            while (n != 0) {
                nx = n->m08;
                if (n != 0) {
                    if (n != 0) {
                        r = n->m00;
                        ok = (r != 0) ^ 1;
                        if (ok == 0) {
                            if (r != 0) {
                                r->m04 -= 1;
                            }
                            r = n->m00;
                            c = (r != 0) ? r->m04 : 0;
                            if (c == 0) {
                                if (r != 0) {
                                    if (r->m00 != 0) {
                                        r->m00->dt(-1);
                                    }
                                    n->m00->m04 = 0;
                                    n->m00 = 0;
                                }
                            }
                            n->m00 = 0;
                        }
                    }
                }
                n = nx;
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
