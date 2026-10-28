/* rgp:protos */
#define RGP_SELF_ScriptArgsToVec4_26a220 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* clone group cg06-001: three walking-cursor calls with stride 8 feeding the
   x/y/z of a Vec4 whose w is the literal 1.0f (mwcc stores that as a plain
   `lui`+`sw` of 0x3F800000).  The cursor is a POST-INCREMENT -- retail's
   `daddu $4,$16,$0` + `addiu $16,$4,8` is `g(p++)` with sizeof(elem) == 8,
   not `g(base + k)`. */

typedef struct Vec4f {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} Vec4f;

typedef struct Pair {
    s32 a;
    s32 b;
} Pair;

/*rgp*/

void ScriptArgsToVec4_26a220(Vec4f *out, Pair *p)
{
    out->x = TaggedGetFloat_26a280(p++);
    out->y = TaggedGetFloat_26a280(p++);
    out->z = TaggedGetFloat_26a280(p++);
    out->w = 1.0f;
}
