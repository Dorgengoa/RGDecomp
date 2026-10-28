/* rgp:protos */
#line 1
#include "types.h"
/* insect 0x0051E080 -- C++ virtual dispatch, vptr at +0x1B0.
 * `lw $25,0x1B0($4) / lw $25,0x24($25) / jalr $25` is virtual #7
 * (slot 0x24 = 8 + 4*7).  [[jalr-is-cpp-virtual]] */

class VE {
public:
    u8 pad000[0x1B0];
    VC_VPTR_MEMBER;  
      
    
    void s07(int rgp_fwd1 = 0, int rgp_fwd2 = 0, int rgp_fwd3 = 0) { VCM(void, (void *, int, int, int), 0x24, rgp_fwd1, rgp_fwd2, rgp_fwd3); }               /* slot 0x24 */
};

struct H { VE *obj; };

extern "C" void insect_InsectBattleEffectNodeDraw_51e080(H *h, int rgp_a1, int rgp_a2, int rgp_a3)
{
    VE *o;

    o = h->obj;
    if (o != 0) {
        o->s07((int)(long)(rgp_a1), (int)(long)(rgp_a2), (int)(long)(rgp_a3));
    }
}
