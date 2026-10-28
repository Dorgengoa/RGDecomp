/* rgp:protos */
#define RGP_SELF_EffectSetRotById_2e0960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Clone of EffectSetParamIntVecById_2e0280's shape (see src/s31a/EffectSetParamIntVecById_2e0280.c): fetch a
   command record via EffectFindHandleById_2dd6c0 into a local 5-word raw buffer, copy the
   idx/arg words out unconditionally, bail if idx == -1, otherwise finish
   the raw word copy (word3+word4, then word0+word1, each via an 8-byte
   read/write so mwcc emits the ldl/ldr and sd pairs retail uses) and
   forward the buffer -- reinterpreted as the callee's real Cmd struct --
   together with the caller's Vec argument to EffectSetRot_2e09f0. */

typedef struct Raw0960 {
    s32 w[5];
} Raw0960;

typedef struct Cmd0960 {
    s16 mode;              /* 0x00 */
    u8  pad02[0x6];
    s32 idx;                /* 0x08 */
    s32 arg;                /* 0x0C */
} Cmd0960;

struct Vec0960 { f32 x, y, z, w; } __attribute__((aligned(16)));

/*rgp*/
/*rgp*/

s32 EffectSetRotById_2e0960(u8 *a0, s32 a1, struct Vec0960 *a2)
{
    Raw0960 r __attribute__((aligned(16)));
    Raw0960 info __attribute__((aligned(16)));

    r.w[3] = 0;
    EffectFindHandleById_2dd6c0(&info, a0 + 0x1674, a1);
    r.w[3] = info.w[3];
    r.w[2] = info.w[2];
    if (info.w[2] != -1) {
        *(s64 *)&r.w[3] = *(s64 *)&info.w[3];
        *(s64 *)&r.w[0] = *(s64 *)&info.w[0];
        return EffectSetRot_2e09f0(a0, (Cmd0960 *)&r, a2);
    } else {
        return 0;
    }
}
