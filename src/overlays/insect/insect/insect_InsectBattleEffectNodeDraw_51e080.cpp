#include "types.h"
/* insect 0x0051E080 -- C++ virtual dispatch, vptr at +0x1B0.
 * `lw $25,0x1B0($4) / lw $25,0x24($25) / jalr $25` is virtual #7
 * (slot 0x24 = 8 + 4*7).  [[jalr-is-cpp-virtual]] */

class VE {
public:
    u8 pad000[0x1B0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06();
    virtual void s07();               /* slot 0x24 */
};

struct H { VE *obj; };

extern "C" void insect_InsectBattleEffectNodeDraw_51e080(H *h)
{
    VE *o;

    o = h->obj;
    if (o != 0) {
        o->s07();
    }
}
