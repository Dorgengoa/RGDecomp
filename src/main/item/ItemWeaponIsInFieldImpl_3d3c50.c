#include "types.h"
typedef struct T003d3c50 {
    u8 pad[0x24C];
    u8 f24C;
} T003d3c50;

typedef struct S003d3c50 {
    u8 pad[0x20];
    T003d3c50 *f20;
} S003d3c50;

extern S003d3c50 *D_004838E8;

s32 ItemWeaponIsInFieldImpl_3d3c50(void)
{
    T003d3c50 *p;
    u8 b;
    s32 r;

    if (D_004838E8 == 0) {
        r = 0;
    } else {
        p = D_004838E8->f20;
        b = (p->f24C & 1) != 0;
        r = b ^ 1;
    }
    return r;
}
