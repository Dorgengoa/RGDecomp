/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x0051E0B0 -- C++ virtual dispatch, vptr at +0x1B0, slot 0x44 =
 * virtual #15.  [[jalr-is-cpp-virtual]] */

class VE {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;  
      
      
      
      
    void s15(f32 t, int rgp_fwd2 = 0, int rgp_fwd3 = 0, int rgp_fwd4 = 0) { VCM(void, (void *, int, int, int, f32), 0x44, rgp_fwd2, rgp_fwd3, rgp_fwd4, t); }          /* slot 0x44 */
};

struct H {
    VE *obj;
    u8  pad004[0x14];
    s16 f18;
    s16 f1A;
};

extern "C" void insect_InsectBattleEffectNodeStep_51e0b0(H *h, int rgp_a1, int rgp_a2, int rgp_a3)
{
    VE *o;

    o = h->obj;
    if (o != 0) {
        o->s15(1.0f, (int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    }
    if (h->f18 >= 0) {
        h->f18 = h->f18 - 1;
    }
    if (h->f1A >= 0) {
        h->f1A = h->f1A - 1;
    }
}
