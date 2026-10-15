#include "types.h"
/* insect 0x0051E0B0 -- C++ virtual dispatch, vptr at +0x1B0, slot 0x44 =
 * virtual #15.  [[jalr-is-cpp-virtual]] */

class VE {
public:
    u8 pad000[0x1B0];
    virtual void s00(); virtual void s01(); virtual void s02();
    virtual void s03(); virtual void s04(); virtual void s05();
    virtual void s06(); virtual void s07(); virtual void s08();
    virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(f32 t);          /* slot 0x44 */
};

struct H {
    VE *obj;
    u8  pad004[0x14];
    s16 f18;
    s16 f1A;
};

extern "C" void insect_InsectBattleEffectNodeStep_51e0b0(H *h)
{
    VE *o;

    o = h->obj;
    if (o != 0) {
        o->s15(1.0f);
    }
    if (h->f18 >= 0) {
        h->f18 = h->f18 - 1;
    }
    if (h->f1A >= 0) {
        h->f1A = h->f1A - 1;
    }
}
