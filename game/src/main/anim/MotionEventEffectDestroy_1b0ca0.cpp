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

extern "C" void EffInstDestroyByHandle_1a0b00(void *h, void *v);

extern "C" s32 MotionEventEffectDestroy_1b0ca0(A1B0 *a, B1B0 *b)
{
    void *h;
    bool done;

    done = !b->IsSet();
    if (!done) {
        h = a->m4->m53C;
        if (h != 0) {
            EffInstDestroyByHandle_1a0b00(h, b->m30);
            b->m30 = 0;
        }
    }
    return 1;
}
