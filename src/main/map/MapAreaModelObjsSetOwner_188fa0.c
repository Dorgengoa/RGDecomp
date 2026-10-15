#include "types.h"

struct B { u8 pad000[0x34]; s32 m34; s32 m38; };
struct A { u8 pad000[0x504]; s32 m504; struct B **m508; };

void MapAreaModelObjsSetOwner_188fa0(struct A *p0)
{
    s32 n;
    struct B **arr;
    s32 i;
    struct B *e;

    n = p0->m504;
    arr = p0->m508;
    i = 0;
    while (i < n) {
        e = arr[i];
        if (e != 0) {
            e->m34 = (s32)p0;
            e->m38 = 0;
        }
        i = i + 1;
    }
}
