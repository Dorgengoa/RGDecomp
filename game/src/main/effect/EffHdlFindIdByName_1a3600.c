/* rgp:protos */
#define RGP_SELF_EffHdlFindIdByName_1a3600 1
#define RGP_SELF_StringReplace_106f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Str_001a3600 {
    s32 w[3];
} Str_001a3600;

typedef struct Alloc_001a3600 {
    s8 c;
} Alloc_001a3600;

extern s32 strlen(const char *);
/*rgp*/
extern void StringReplace_106f90(Str_001a3600 *, s32, s32, const char *, const char *, Alloc_001a3600);
/*rgp*/
/*rgp*/

void EffHdlFindIdByName_1a3600(s32 *out, u8 *m, const char *str)
{
    Str_001a3600 s __attribute__((aligned(16)));
    void *it;
    Alloc_001a3600 al __attribute__((aligned(16)));
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
    StrMapFind_1a4bb0(&it, m + 0x24, &s);
    if ((s.w[0] & 1) != 0) {
        OperatorDelete_100840((void *)s.w[2]);
    }
    if (it == (void *)(m + 0x28)) {
        *out = 0;
    } else {
        *out = *(s32 *)((u8 *)it + 0x18);
    }
}
