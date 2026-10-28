/* rgp:protos */
#define RGP_SELF_StrCopyBounded_42cad0 1
#define RGP_SELF_slen 1
#include "port/game_protos.h"
#line 1
#include "types.h"

static inline u32 slen(s8 *s) {
    s8 *p;

    if (s == NULL) {
        return 0;
    }
    p = s;
    while (*p != 0) {
        p++;
    }
    return p - s;
}

u32 StrCopyBounded_42cad0(s8 *dst, s8 *src, u32 size) {
    u32 len;
    u32 i;
    s8 *d;
    s8 *s;
    u32 n;

    if (dst == NULL || src == NULL) {
        return 0;
    }
    len = slen(src);
    if (len >= size) {
        len = size - 1;
    }
    if (dst == src) {
        dst[len] = 0;
        return len;
    }
    if (len != 0) {
        d = dst;
        if (d < src) {
            for (i = 0; i <= len - 1; i++) {
                *d++ = *src++;
            }
        } else {
            n = len - 1;
            d += n;
            src += n;
            for (i = 0; i <= n; i++) {
                *d = *src;
                src--;
                d--;
            }
        }
    }
    dst[len] = 0;
    return len;
}
