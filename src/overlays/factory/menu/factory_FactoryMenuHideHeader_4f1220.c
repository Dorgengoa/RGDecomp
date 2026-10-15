#include "types.h"

typedef struct A {
    u8    pad00[0x64];
    void *f64;
} A;

extern void func_290010(void *w, s32 id, s32 a, s32 b);

void factory_FactoryMenuHideHeader_4f1220(A *o)
{
    func_290010(o->f64, 1, 0, -1);
}
