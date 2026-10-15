#include "types.h"
extern void MatToRotPos_1cade0(s32, s32 *, s32);
void MatGetEulerRot_1cb160(s32 p0, s32 p1)
{
    s32 v[4];
    MatToRotPos_1cade0(p0, v, p1);
}
