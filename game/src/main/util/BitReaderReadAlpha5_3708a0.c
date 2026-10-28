/* rgp:protos */
#define RGP_SELF_BitReaderReadAlpha5_3708a0 1
#define RGP_SELF_both 1
#define RGP_SELF_readBit 1
#define RGP_SELF_toChar 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"


typedef struct {
    s16 pos;
    u8 pad2[6];
    u8 *buf;
} Bits;

static inline s32 both(s32 a,s32 b){return b&a;}
static inline u8 readBit(Bits *r) {
    s16 p = r->pos++;
    return both((u8)(1<<(p&7)),r->buf[p>>3])!=0;
}

static inline s8 toChar(s8 c) {
    if (c == 0) {
        return 0;
    }
    if (c == 1) {
        return 0x20;
    }
    if (c >= 2 && c < 0x1C) {
        return c + 0x3F;
    }
    return 0;
}

s32 BitReaderReadAlpha5_3708a0(Bits *r, s8 *out, s32 n) {
s8 c;
s32 mask;
s32 j;
s32 i;
s32 bits;
if (out == NULL) {
        return 0;
    }
    bits = 0;
    for (i = 0; i < n; i++) {
        c = 0;
        mask = 1;
        j = 0;
        do {
            if (readBit(r)) {
                c |= (s8)mask;
            }
            j++;
            bits++;
            mask <<= 1;
        } while (j < 5);
        *out = toChar(c);
        out++;
    }
    *out = 0;
    return bits;
}
