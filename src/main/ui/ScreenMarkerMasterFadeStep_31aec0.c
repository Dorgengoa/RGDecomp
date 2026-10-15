#include "types.h"

struct Obj {
    u8 pad000[0x150];
    f32 m150;
    f32 m154;
};

void ScreenMarkerMasterFadeStep_31aec0(struct Obj *o)
{
    if (o->m154) {
        o->m150 = o->m150 + o->m154;
        if (o->m154 > 0.0f) {
            if (o->m150 >= 1.0f) {
                o->m150 = 1.0f;
                o->m154 = 0.0f;
            }
        }
        if (o->m154 < 0.0f) {
            if (o->m150 <= 0.0f) {
                o->m150 = 0.0f;
                o->m154 = 0.0f;
            }
        }
    }
}
