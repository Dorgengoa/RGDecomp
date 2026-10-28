/* rgp:protos */
#define RGP_SELF_Vec4VectorPushBack_249120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct Vec4 { f32 x; f32 y; f32 z; f32 w; };
struct T249120 { u8 pad000[0x48C]; u8 f48C[4]; struct Vec4 *f490_dummy; };

/*rgp*/

struct T2 { u8 pad000[0x490]; s32 f490; struct Vec4 *f494; };

void Vec4VectorPushBack_249120(struct T2 *p, struct Vec4 *src)
{
    struct Vec4 v __attribute__((aligned(16)));

    v = *src;
    Vec4VectorInsertN_250530((u8 *)p + 0x48C, &p->f494[p->f490], 1, &v);
}
