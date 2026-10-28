#include "types.h"

class C_00187F60 {
    u8 pad000[0x68];
public:
    /* +0x008 */ VC_VPTR_MEMBER;
    /* +0x00C */ 
    /* +0x010 */ 
    /* +0x014 */ 
    /* +0x018 */ 
    /* +0x01C */ 
    /* +0x020 */ 
    /* +0x024 */ 
    /* +0x028 */ void v28() { VCM0(void, 0x28); }
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
