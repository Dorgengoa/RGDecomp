#include "types.h"

typedef struct A {
    u8 pad00[0x50];
    u8 f50[0x28];
    u8 f78;
} A;

extern void func_28D820(void *p, s32 a);

void factory_FactoryMaterialFrameScroll_4f3a40(A *o)
{
    if (o->f78 != 2) {
        func_28D820(&o->f50, 0x63);
    }
}
