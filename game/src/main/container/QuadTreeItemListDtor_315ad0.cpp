#include "types.h"

class VE315ad0 {
public:
    u8 pad000[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * dt(s16 a0) { return VCM(void *, (void *, s16), 0x6C, a0); }
};

struct Rep315ad0 {
    VE315ad0 *m00;
    s32 m04;
};

struct Node315ad0 {
    struct Rep315ad0 *m00;
    u8 pad004[0x4];
    struct Node315ad0 *m08;
};

struct Obj315ad0 {
    struct Node315ad0 *m00;
};

extern "C" {
extern void OperatorDelete_100840(void *);
}

extern "C" void *QuadTreeItemListDtor_315ad0(Obj315ad0 *o, s16 flag)
{
    Node315ad0 *n;
    Node315ad0 *nx;
    Rep315ad0 *r;
    s32 c;
    s32 ok;

    if (o != 0) {
        n = o->m00;
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
        if (flag > 0) {
            OperatorDelete_100840(o);
        }
    }
    return o;
}
