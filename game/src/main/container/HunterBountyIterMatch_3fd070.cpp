#include "types.h"

struct A {
    u8 pad[0xE];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 f3 : 1;
    u8 f4 : 1;
    u8 f5 : 1;
};

struct B {
    u8 pad[0x1C];
    u8 f0 : 1;
    u8 f1 : 1;
    u8 f2 : 1;
    u8 f3 : 1;
};

extern "C" bool HunterBountyIterMatch_3fd070(A *a, B *b)
{
    bool r;

    if (b == 0) {
        return false;
    }
    if (b->f0) {
        if (!a->f0) {
            return false;
        }
    } else {
        if (!a->f1) {
            return false;
        }
    }
    r = false;
    if (!b->f1) {
        if (a->f2) {
            r = true;
        }
    } else if (!b->f2) {
        if (a->f3) {
            r = true;
        }
    } else if (!b->f3) {
        if (a->f4) {
            r = true;
        }
    } else if (a->f5) {
        r = true;
    }
    return r;
}
