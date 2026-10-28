#include "types.h"

struct T00194F80;
struct Base00194F80 { u8 pad000[0x34]; struct T00194F80 *f34; s32 f38; u8 pad03C[0x2C]; };
struct E00194F80 : Base00194F80 {
    VC_VPTR_MEMBER;
    
    
    void v3() { VCM0(void, 0x14); }
};
struct N00194F80 { struct N00194F80 *f00; u8 pad004[0xC]; struct E00194F80 *f10; };
struct T00194F80 { u8 pad000[0x94]; struct N00194F80 *f94; };

extern "C" void NodeObjResetMatrix_194f80(struct T00194F80 *p)
{
    struct N00194F80 *n;
    struct E00194F80 *e;

    n = p->f94;
    while (n != 0) {
        e = n->f10;
        if (e != 0) {
        e->v3();
        e->f34 = 0;
        e->f38 = 0;
        }
        n = n->f00;
    }
}
