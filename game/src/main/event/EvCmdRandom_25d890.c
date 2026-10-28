/* rgp:protos */
#define RGP_SELF_EvCmdRandom_25d890 1
#include "port/game_protos.h"
#line 1
/* main s27m: CLOSED by the s26 post-incremented-PARAMETER lever (E8 *arg0, arg0++ at each call). */
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct { u8 b[8]; } E8;
s32 EvCmdRandom_25d890(E8 *arg0)
{
    f32 temp_f20;
    s32 temp_16;

    if (*(s32 *)arg0 == 1) {
        temp_f20 = TaggedGetFloat_26a280(arg0++);
        ScriptSetRefFloat_26a1c0(arg0, (temp_f20 * (f32) Rand_133710()) / 2147483648.0f);
    } else {
        temp_16 = ScriptGetInt_26a2a0(arg0++);
        ScriptSetRefInt_26a1e0(arg0, (s32) (((f32) temp_16 * (f32) Rand_133710()) / 2147483648.0f));
    }
    return 1;
}
