#include "types.h"
/* void definition ending in a virtual call: retail returns that call's $v0 */
class O3ae3e0 {
public:
    virtual void v0();
    virtual void v1(s32 a);
};

extern "C" void IconRec_3ae3e0(O3ae3e0 *o)
{
    s32 x;

    x = 4;
    o->v0();
    o->v1(x);
}
