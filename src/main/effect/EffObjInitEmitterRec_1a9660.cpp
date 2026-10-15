#include "types.h"

struct B_001A9660 {
    u8 pad000[0x4];
    s32 f04;
    u8 pad008[0xB8];
    s32 fC0;
    s32 fC4;
    s32 fC8;
};

class C_001A9660 {
public:
    /* +0x008 */ virtual void s008();
    /* +0x00C */ virtual void s00C();
    /* +0x010 */ virtual void v10(B_001A9660 *b);
};

struct N_001A9660 {
    struct N_001A9660 *f00;
    C_001A9660 *f04;
};

struct A_001A9660 {
    u8 pad000[0x4];
    N_001A9660 *f04;
};

extern "C" void XformPairInit_19a240(B_001A9660 *b);
extern "C" s32 Rand_133710(void);

extern "C" void EffObjInitEmitterRec_1a9660(A_001A9660 *a, B_001A9660 *b)
{
    N_001A9660 *n;

    XformPairInit_19a240(b);
    b->fC8 = 0;
    b->fC0 = 0;
    b->fC4 = 0;
    XformPairInit_19a240(b);
    b->f04 = Rand_133710();
    n = a->f04;
    while (n != 0) {
        n->f04->v10(b);
        n = n->f00;
    }
}
