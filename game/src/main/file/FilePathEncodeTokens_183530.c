/* rgp:protos */
#define RGP_SELF_FilePathEncodeTokens_183530 1
#define RGP_SELF_clr 1
#define RGP_SELF_find 1
#include "port/game_protos.h"
#line 1
#pragma optimization_level 3
#include "types.h"

typedef struct {
    s32 unk0;
    s32 off;
    s32 unk8;
    u32 count;
} Tbl;

/*rgp*/
extern s32 strlen(s8 *);

static inline s32 find(Tbl *tbl, s8 *name) {
    u32 i;
    s8 *q = (s8 *)tbl + tbl->off;
    for (i = 0; i < tbl->count; i++) {
        if (Strcasecmp_1345b8(name, q) == 0) return i;
        q += strlen(q) + 1;
    }
    return -1;
}

static inline void clr(s8 *p, u32 n) {
    if (p != 0) {
        do {
            *p = 0;
            n--;
            p++;
        } while (n != 0);
    }
}

s32 FilePathEncodeTokens_183530(s8 *arg0, Tbl *tbl, s8 *arg2)
{
    s8 buf[0x40] __attribute__((aligned(16)));
    s8 *p;
    s32 n;
    s32 ok;
    s8 *q;
    s8 *d;
    s8 c;
    s8 *s;
    s32 i;
    s8 *out;

    clr(buf, 0x40);
    out = arg0;
    s = arg2;
    ok = 1;
    d = buf;
    for (;;) {
        c = *s;
        if (c == '/' || c == '.' || c == 0 || c == '_' || c == '-') {
            if (c != 0 && s[1] == 0) {
                *d++ = c;
            }
            *d = 0;
            i = find(tbl, buf);
            if (i < 0) {
                ok = 0;
                break;
            }
            if (i < 0x80) {
                *out++ = i;
            } else {
                out[0] = (i & 0x7F) | 0x80;
                out[1] = i >> 7;
                out += 2;
            }
            d = buf;
            if (*s == 0) break;
            *d = *s;
            d++;
            s++;
            c = *s;
            if (c == 0) break;
        }
        *d = c;
        s++;
        d++;
    }
    *out = 0;
    return ok;
}
