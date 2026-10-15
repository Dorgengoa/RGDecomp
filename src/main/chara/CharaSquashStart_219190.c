#include "types.h"

/* `bgtzl` past `n = 1` with the following store duplicated into the delay
   slot => `if (n <= 0) n = 1;` then the two stores. */

extern void CharaSquashResetThunk_219300(void *p, s32 n, f32 v);

void CharaSquashStart_219190(void *p, s32 n, f32 v)
{
    CharaSquashResetThunk_219300(p, n, v);
    if (n <= 0) {
        n = 1;
    }
    *(f32 *)p = v;
    *(s32 *)((u8 *)p + 4) = n;
}
