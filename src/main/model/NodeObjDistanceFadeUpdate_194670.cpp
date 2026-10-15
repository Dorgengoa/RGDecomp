#include "types.h"

struct B194670 {
    u8    pad00[0x34];
    void *m34;
    s32   m38;
    u8    pad3C[0x68 - 0x3C];
};

struct Obj194670 : public B194670 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5(f32 t);
};

struct Node194670 {
    Node194670 *next;
    u8          pad04[0xC];
    Obj194670  *m10;
};

struct P194670 {
    u8           pad00[0x94];
    Node194670  *m94;
};

extern "C" void NodeDistanceFadeUpdate_185e10(void);

extern "C" void NodeObjDistanceFadeUpdate_194670(P194670 *p, f32 t)
{
    Node194670 *n;
    Obj194670 *o;

    n = p->m94;
    if (t <= 0.0f) return;
    NodeDistanceFadeUpdate_185e10();
    while (n != 0) {
        o = n->m10;
        o->m34 = p;
        o->m38 = 0;
        o->v5(t);
        o->m34 = 0;
        o->m38 = 0;
        n = n->next;
    }
}
