/* rgp:protos */
#define RGP_SELF_BitWriterWriteAlnum6_370a30 1
#define RGP_SELF_enc 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

static inline s8 enc(s8 c) {
    if (c == 0) return 0;
    if (c >= 0x41 && c < 0x5B) return c - 0x3F;
    if (c >= 0x61 && c < 0x7B) return c - 0x45;
    if (c >= 0x30 && c < 0x3A) return c + 6;
    return 1;
}

s32 BitWriterWriteAlnum6_370a30(s16 *arg0, s8 *arg1, s32 arg2)
{
    s32 n;
    s8 *p;
    s32 i;
    s32 mask;
    s32 k;
    s16 t;
    s8 v;

    if (arg1 == NULL) {
        return 0;
    }
    p = arg1;
    n = 0;
    for (i = 0; i < arg2; i++) {
        v = enc(*p++);
        for (mask = 1, k = 0; k < 6; k++, n++, mask <<= 1) {
            t = *arg0;
            *arg0 = t + 1;
            BitWriterSetBit_370cc0(arg0, t, (v & mask) != 0);
        }
    }
    return n;
}
