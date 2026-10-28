/* rgp:protos */
#define RGP_SELF_HitShapeSetWorldCapsule_317170 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Vec4_FUN_00317170 {
    f32 x, y, z, w;
} __attribute__((aligned(16))) Vec4_FUN_00317170;

typedef struct Obj_FUN_00317170 {
    u8 m00;                     /* +0x00 */
    u8 pad01[7];
    s32 m08;                    /* +0x08 */
    u8 pad0C[0x10 - 0x0C];
    Vec4_FUN_00317170 m10;      /* +0x10 */
    Vec4_FUN_00317170 m20;      /* +0x20 */
} Obj_FUN_00317170;

void HitShapeSetWorldCapsule_317170(Obj_FUN_00317170 *o, Vec4_FUN_00317170 *a, Vec4_FUN_00317170 *b, s32 d, f32 t)
{
    o->m00 = 3;
    o->m08 = d;
    o->m10 = *a;
    o->m20 = *b;
    o->m20.w = t;
    o->m10.w = t;
}
