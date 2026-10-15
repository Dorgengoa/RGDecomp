#include "types.h"

struct S16F610 { s32 a; s32 b; s32 c; s32 d; };

extern void MeshRaycastTris_16f3c0(struct S16F610 *, s32, s32, s32, s32, s32);

void MeshRaycastWrapper_16f610(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6)
{
    struct S16F610 s;

    s.a = p1;
    s.b = p0;
    s.c = 0;
    s.d = 0;
    MeshRaycastTris_16f3c0(&s, p2, p3, p4, p5, p6);
}
