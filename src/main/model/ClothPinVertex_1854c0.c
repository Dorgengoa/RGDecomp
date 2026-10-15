#include "types.h"

typedef struct E001854C0 {
    u8 pad0[0xC];
    f32 fC;                   /* +0xC */
} E001854C0;

typedef struct S001854C0 {
    u8 pad0[0x4];
    s32 f4;                   /* +0x4 */
    u8 pad8[0xC];
    E001854C0 *f14;           /* +0x14 */
} S001854C0;

void ClothPinVertex_1854c0(S001854C0 *p, s32 i)
{
    if (i < 0 || i >= p->f4) {
        return;
    }
    p->f14[i].fC = 1.0f;
}
