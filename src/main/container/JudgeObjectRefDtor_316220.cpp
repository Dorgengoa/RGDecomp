#include "types.h"

class VE316220 {
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

struct Rep316220 {
    VE316220 *m00;
    s32 m04;
};

struct Obj316220 {
    Rep316220 *m00;
};

extern "C" {
extern void OperatorDelete_100840(void *);
}

extern "C" void *JudgeObjectRefDtor_316220(Obj316220 *o, s16 flag)
{
    Rep316220 *r;
    s32 c;
    s32 ok;

    if (o != 0) {
        if (o != 0) {
            r = o->m00;
            ok = (r != 0) ^ 1;
            if (ok == 0) {
                if (r != 0) {
                    r->m04 -= 1;
                }
                r = o->m00;
                c = (r != 0) ? r->m04 : 0;
                if (c == 0) {
                    if (r != 0) {
                        if (r->m00 != 0) {
                            r->m00->dt(-1);
                        }
                        o->m00->m04 = 0;
                        o->m00 = 0;
                    }
                }
                o->m00 = 0;
            }
        }
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
