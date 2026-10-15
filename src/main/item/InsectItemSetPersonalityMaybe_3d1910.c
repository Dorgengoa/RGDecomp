#include "types.h"
typedef struct T003D1910 {
    u8 pad[0x26];
    s8 b26;
} T003D1910;

typedef struct S003D1910 {
    u8 pad[0x18];
    T003D1910 *f18;
} S003D1910;

void InsectItemSetPersonalityMaybe_3d1910(S003D1910 *s, s32 n)
{
    if (n < 0) {
        n = 0;
    }
    if (n > 4) {
        n = 4;
    }
    s->f18->b26 = n;
}
