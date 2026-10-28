#include "types.h"

struct Obj {
    u8 pad0[0x860];
    u8 unk860;
    u8 pad861[0xA2E - 0x861];
    s16 unkA2E;
    u8 padA30[2];
    s16 unkA32;
    u8 padA34[2];
    s16 unkA36;
    s16 unkA38;
    u8 padA3A[0xB5C - 0xA3A];
    s32 unkB5C;
    s16 unkB60;
    s16 unkB62;
};

static inline bool f1(Obj *o)
{
    bool r = false;

    if (o->unkB60 >= 0 && o->unkB5C != 0) {
        r = true;
    }
    return r;
}

static inline bool f2(Obj *o)
{
    return o->unkB60 >= 0 && o->unkB5C != 0 && (o->unkB62 & 8) != 0;
}

extern "C" s32 CharaIsActionFreeMaybe_2105e0(Obj *o)
{
    s16 t;

    if (o->unkA38 != 0) {
        t = o->unkA36;
        if (t == 2) {
            return 0;
        }
        if (t == 30) {
            return 0;
        }
        if (t == 31) {
            return 0;
        }
    }
    if (o->unkA2E != 0) {
        return 0;
    }
    if (o->unkA32 != 0) {
        return 0;
    }
    if (o->unk860 != 0) {
        return 0;
    }
    if (f1(o) && !f2(o)) {
        return 0;
    }
    return 1;
}
