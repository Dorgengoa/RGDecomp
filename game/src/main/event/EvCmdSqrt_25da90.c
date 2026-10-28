/* rgp:protos */
#define RGP_SELF_EvCmdSqrt_25da90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Same sqrtf idiom as AiCmdSqrt_2cc250 (see src/s31a/AiCmdSqrt_2cc250.c): the
   `c1 0x304` word is the compiler's inline sqrt.s for `sqrtf(v)`. */

typedef struct E8_FUN_0025da90 {
    u8 raw[0x8];
} E8_FUN_0025da90;

/*rgp*/
/*rgp*/
extern f32 sqrtf(f32 x);

s32 EvCmdSqrt_25da90(E8_FUN_0025da90 *arg0)
{
    f32 v;

    v = TaggedGetFloat_26a280(arg0++);
    ScriptSetRefFloat_26a1c0(arg0, sqrtf(v));
    return 1;
}
