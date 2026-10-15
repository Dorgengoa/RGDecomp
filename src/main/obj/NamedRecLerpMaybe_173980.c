#include "types.h"

typedef struct { u8 pad[0x24]; f32 f24, f28; u8 pad2[0x30 - 0x2C]; } E_00173980;
typedef struct { s32 f0; s32 f4; E_00173980 *f8; } T_00173980;

f32 NamedRecLerpMaybe_173980(T_00173980 *p, s32 i, f32 t)
{
    E_00173980 *arr;
    E_00173980 *e;
    s32 r;
    f32 a;
    f32 b;

    arr = p->f8;
    if (arr == 0) {
        r = 0;
    } else {
        if (i >= 0) {
            if (i >= p->f4) {
                r = 0;
            } else {
                r = 1;
            }
        } else {
            r = 0;
        }
    }
    if (r) {
        e = &arr[i];
    } else {
        e = 0;
    }
    if (e == 0) return 0.0f;
    a = e->f24;
    b = e->f28;
    return a + t * (b - a);
}
