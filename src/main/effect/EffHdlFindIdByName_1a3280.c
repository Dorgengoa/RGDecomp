#include "types.h"

typedef struct Str_001a3280 {
    s32 w[3];
} Str_001a3280;

typedef struct Alloc_001a3280 {
    s8 c;
} Alloc_001a3280;

extern s32 strlen(const char *);
extern void StringReserve_107e80(Str_001a3280 *, s32);
extern void StringReplace_106f90(Str_001a3280 *, s32, s32, const char *, const char *, Alloc_001a3280);
extern void StrMapFind_1a4ac0(void **, void *, Str_001a3280 *);
extern void OperatorDelete_100840(void *);

void EffHdlFindIdByName_1a3280(s32 *out, u8 *m, const char *str)
{
    Str_001a3280 s;
    void *it;
    Alloc_001a3280 al;
    s32 len;
    u32 i;
    s32 *p;

    p = s.w;
    for (i = 0; i < 3; i++) {
        p[i] = 0;
    }
    len = strlen(str);
    StringReserve_107e80(&s, len);
    StringReplace_106f90(&s, 0, 0, str, str + len, al);
    StrMapFind_1a4ac0(&it, m + 0x24, &s);
    if ((s.w[0] & 1) != 0) {
        OperatorDelete_100840((void *)s.w[2]);
    }
    if (it == (void *)(m + 0x28)) {
        *out = 0;
    } else {
        *out = *(s32 *)((u8 *)it + 0x18);
    }
}
