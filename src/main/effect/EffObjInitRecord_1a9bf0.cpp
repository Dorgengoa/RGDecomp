#include "types.h"

struct B_001A9BF0 {
    u8 pad000[0x4];
    s32 f04;
};

class C_001A9BF0 {
public:
    /* +0x008 */ virtual void s008();
    /* +0x00C */ virtual void s00C();
    /* +0x010 */ virtual void v10(B_001A9BF0 *b);
};

struct N_001A9BF0 {
    struct N_001A9BF0 *f00;
    C_001A9BF0 *f04;
};

struct A_001A9BF0 {
    u8 pad000[0x4];
    N_001A9BF0 *f04;
};

extern "C" void XformPairInit_19a240(B_001A9BF0 *b);
extern "C" s32 Rand_133710(void);

extern "C" void EffObjInitRecord_1a9bf0(A_001A9BF0 *a, B_001A9BF0 *b)
{
    N_001A9BF0 *n;

    XformPairInit_19a240(b);
    b->f04 = Rand_133710();
    n = a->f04;
    while (n != 0) {
        n->f04->v10(b);
        n = n->f00;
    }
}
