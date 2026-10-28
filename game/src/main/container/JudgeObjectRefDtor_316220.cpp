/* rgp:protos */
#line 1
#include "types.h"

class VE316220 {
public:
    u8 pad000[0xB0];
    VC_VPTR_MEMBER;
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void * dt(s16 a0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { return VCM(void *, (void *, s16, int, int), 0x6C, a0, rgp_fwd2, rgp_fwd3); }
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

extern "C" void *JudgeObjectRefDtor_316220(Obj316220 *o, s16 flag, int rgp_a2, int rgp_a3)
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
                            r->m00->dt(-1, (int)(long)(rgp_a2), (int)(long)(rgp_a3));
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
