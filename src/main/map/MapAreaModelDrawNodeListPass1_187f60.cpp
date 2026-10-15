#include "types.h"

class C_00187F60 {
    u8 pad000[0x68];
public:
    /* +0x008 */ virtual void s008();
    /* +0x00C */ virtual void s00C();
    /* +0x010 */ virtual void s010();
    /* +0x014 */ virtual void s014();
    /* +0x018 */ virtual void s018();
    /* +0x01C */ virtual void s01C();
    /* +0x020 */ virtual void s020();
    /* +0x024 */ virtual void s024();
    /* +0x028 */ virtual void v28();
};

struct E_00187F60 {
    u8 pad000[0x32];
    s16 f32;
};

struct Obj_00187F60 {
    u8 pad000[0x534];
    s32 f534;
    E_00187F60 **f538;
};

extern "C" void MapAreaModelDrawNodeListPass1_187f60(Obj_00187F60 *o)
{
    E_00187F60 **arr;
    E_00187F60 *e;
    s32 n;
    s32 i;

    arr = o->f538;
    n = o->f534;
    for (i = 0; i < n; i++) {
        e = arr[i];
        if (e == 0) {
            continue;
        }
        if (e->f32 != 0) {
            ((C_00187F60 *)e)->v28();
        }
    }
}
