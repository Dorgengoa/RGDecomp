#include "types.h"

struct T00194FE0;
struct Base00194FE0 { u8 pad000[0x34]; struct T00194FE0 *f34; s32 f38; u8 pad03C[0x2C]; };
struct E00194FE0 : Base00194FE0 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
};
struct N00194FE0 { struct N00194FE0 *f00; u8 pad004[0xC]; struct E00194FE0 *f10; };
struct T00194FE0 { u8 pad000[0x94]; struct N00194FE0 *f94; };

extern "C" void NodeObjSyncMatrix_194fe0(struct T00194FE0 *p)
{
    struct N00194FE0 *n;
    struct E00194FE0 *e;

    n = p->f94;
    while (n != 0) {
        e = n->f10;
        if (e != 0) {
        e->f34 = p;
        e->f38 = 0;
        e->v2();
        }
        n = n->f00;
    }
}
