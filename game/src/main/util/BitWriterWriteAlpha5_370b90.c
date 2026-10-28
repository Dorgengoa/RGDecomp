/* rgp:protos */
#define RGP_SELF_BitWriterWriteAlpha5_370b90 1
#define RGP_SELF_code 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

static inline s8 code(s8 c) {
    if (c == 0) return 0;
    if (c >= 'A' && c <= 'Z') return c - 0x3F;
    if (c >= 'a' && c <= 'z') return c - 0x5F;
    return 1;
}

s32 BitWriterWriteAlpha5_370b90(s16 *arg0, s8 *arg1, s32 arg2)
{
    s32 n;
    s8 *p;
    s32 i;
    s8 c;
    s32 bit;
    s32 j;
    s16 old;

    if (arg1 == NULL) return 0;
    n = 0;
    p = arg1;
    for (i = 0; i < arg2; i++) {
        c = code(*p++);
        bit = 1;
        j = 0;
        do {
            old = *arg0;
            *arg0 = old + 1;
            BitWriterSetBit_370cc0(arg0, old, (c & bit) != 0);
            j++;
            n++;
            bit <<= 1;
        } while (j < 5);
    }
    return n;
}
