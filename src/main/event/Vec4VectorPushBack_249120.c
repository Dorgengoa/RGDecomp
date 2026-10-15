#include "types.h"

struct Vec4 { f32 x; f32 y; f32 z; f32 w; };
struct T249120 { u8 pad000[0x48C]; u8 f48C[4]; struct Vec4 *f490_dummy; };

extern void Vec4VectorInsertN_250530(void *a, struct Vec4 *b, s32 c, struct Vec4 *v);

struct T2 { u8 pad000[0x490]; s32 f490; struct Vec4 *f494; };

void Vec4VectorPushBack_249120(struct T2 *p, struct Vec4 *src)
{
    struct Vec4 v;

    v = *src;
    Vec4VectorInsertN_250530((u8 *)p + 0x48C, &p->f494[p->f490], 1, &v);
}
