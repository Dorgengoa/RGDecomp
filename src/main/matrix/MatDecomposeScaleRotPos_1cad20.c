#include "types.h"
#include "libvu0.h"

typedef unsigned __int128 u128;

#pragma vu0_mmi_reg_binding on
extern u128 vf0_1cad20 asm("vf0");
extern u128 vf4_1cad20 asm("vf4");

extern void MatToRotPos_1cade0(void *rot, void *tmp, void *mtx);

/* |row.xyz| */
static inline f32 RowLength(void *v)
{
    f32 r;
    vf4_1cad20 = *(u128 *)v;
    vf4_1cad20 = _vmul(vf4_1cad20, 0xE, vf4_1cad20, vf4_1cad20);
    vf4_1cad20 = _vaddbc(vf4_1cad20, 0x8, vf4_1cad20, vf4_1cad20, 4);
    vf4_1cad20 = _vaddbc(vf4_1cad20, 0x8, vf4_1cad20, vf4_1cad20, 2);
    Vu0Length(r, x);
    return r;
}

/* Decompose mtx: scale = row lengths (w = 0), rot via MatToRotPos_1cade0, pos = (row3.xyz, 1). */
void MatDecomposeScaleRotPos_1cad20(f32 *scale, void *rot, void *pos, u8 *mtx)
{
    u8 tmp[16];
    scale[0] = RowLength(mtx);
    scale[1] = RowLength(mtx + 0x10);
    scale[2] = RowLength(mtx + 0x20);
    ((s32 *)scale)[3] = 0;
    MatToRotPos_1cade0(rot, tmp, mtx);
    vf4_1cad20 = *(u128 *)(mtx + 0x30);
    vf4_1cad20 = _vmul(vf4_1cad20, 0x1, vf0_1cad20, vf0_1cad20);
    *(u128 *)pos = vf4_1cad20;
}
