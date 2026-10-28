/* rgp:protos */
#define RGP_SELF_StrPrefixLen_24e570 1
#include "port/game_protos.h"
#line 1
#include "types.h"

extern s32 strlen(const char *s);

s32 StrPrefixLen_24e570(char *a, char *b)
{
    s32 n;
    s32 i;

    n = strlen(b);
    for (i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return -1;
        }
    }
    return n;
}
