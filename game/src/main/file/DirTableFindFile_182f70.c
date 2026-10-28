/* rgp:protos */
#define RGP_SELF_DirTableFindFile_182f70 1
#define RGP_SELF_fill 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E182f70 {
    __extension__ unsigned int key : 18;
    unsigned int offLo : 14;
    unsigned int  : 0, offHi : 8;
    unsigned int len : 24;
} __attribute__((aligned(4))) E182f70;

typedef struct H182f70 {
    u8 pad0[0x14];
    s32 m14;
    u8 pad18[8];
    s32 m20;
    s32 m24;
    s32 m28;
} H182f70;

typedef struct R182f70 {
    s32 m0;
    u32 m4;
    s32 m8;
    s32 mC;
    s32 m10;
} R182f70;

/*rgp*/
/*rgp*/

static inline void fill(R182f70 *out, E182f70 *e, s32 unit)
{
    out->m0 = e->key;
    out->m4 = (e->offHi << 14) | e->offLo;
    out->m8 = e->len * unit;
    out->m10 = 0;
    out->mC = 0;
}

s32 DirTableFindFile_182f70(s32 *arg0, R182f70 *out, void *rgp_a2)
{
    H182f70 *h;
    u8 *names;
    E182f70 *ents;
    s32 n;
    s32 lo;
    s32 hi;
    s32 mid;
    E182f70 *e;
    u8 buf[0x100] __attribute__((aligned(16)));

    h = *(H182f70 **)(arg0 + 1);
    if (h == NULL) {
        return 0;
    }
    names = (u8 *)h + h->m14;
    ents = (E182f70 *)((u8 *)h + h->m28);
    if (FilePathEncodeTokens_183530(buf, h, (void *)rgp_a2) == 0) {
        return 0;
    }
    n = 0;
    {
        u8 c;
        do {
            c = buf[n];
            n++;
        } while (c != 0);
    }
    lo = 0;
    hi = h->m24 - 1;
    while (lo < hi) {
        mid = (lo + hi) / 2;
        if (StrCmpU8_1834b0(names + ents[mid].key, buf) < 0) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    if (StrCmpU8_1834b0(names + ents[(u32)lo].key, buf) == 0) {
        fill(out, &ents[lo], h->m20);
        out->m4 = out->m4 + *arg0;
        return 1;
    }
    return 0;
}
