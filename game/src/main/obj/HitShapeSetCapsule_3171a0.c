/* rgp:protos */
#define RGP_SELF_HitShapeSetCapsule_3171a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4_FUN_003171a0 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) Vec4_FUN_003171a0;

typedef struct Obj_FUN_003171a0 {
    u8 m00;                     /* +0x00 */
    u8 pad01[7];
    s32 m08;                    /* +0x08 */
    u8 pad0C[0x10 - 0x0C];
    Vec4_FUN_003171a0 m10;      /* +0x10 */
    Vec4_FUN_003171a0 m20;      /* +0x20 */
} Obj_FUN_003171a0;

void HitShapeSetCapsule_3171a0(Obj_FUN_003171a0 *o, Vec4_FUN_003171a0 *a, Vec4_FUN_003171a0 *b, s32 d, f32 t)
{
    o->m00 = 2;
    o->m08 = d;
    o->m10 = *a;
    o->m20 = *b;
    o->m20.w = t;
    o->m10.w = t;
}
