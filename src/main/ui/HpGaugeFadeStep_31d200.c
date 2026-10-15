#include "types.h"

struct Obj {
    u8 pad000[0x244];
    f32 m244;
    f32 m248;
};

void HpGaugeFadeStep_31d200(struct Obj *o)
{
    if (o->m248) {
        o->m244 = o->m244 + o->m248;
        if (o->m248 > 0.0f) {
            if (o->m244 >= 1.0f) {
                o->m244 = 1.0f;
                o->m248 = 0.0f;
            }
        }
        if (o->m248 < 0.0f) {
            if (o->m244 <= 0.0f) {
                o->m244 = 0.0f;
                o->m248 = 0.0f;
            }
        }
    }
}
