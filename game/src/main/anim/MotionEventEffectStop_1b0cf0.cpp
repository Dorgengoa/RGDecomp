#include "types.h"

typedef struct W1B0 {
    u8    pad000[0x53C];
    void *m53C;
} W1B0;

typedef struct A1B0 {
    u8     pad000[0x4];
    W1B0  *m4;
} A1B0;

struct B1B0 {
    u8     pad000[0x30];
    void  *m30;
    bool IsSet() const { return m30 != 0; }
};

extern "C" void EffInstStop_1a0db0(void *h, void *v);

extern "C" s32 MotionEventEffectStop_1b0cf0(A1B0 *a, B1B0 *b)
{
    void *h;
    bool done;

    done = !b->IsSet();
    if (!done) {
        h = a->m4->m53C;
        if (h != 0) {
            EffInstStop_1a0db0(h, b->m30);
            b->m30 = 0;
        }
    }
    return 1;
}
