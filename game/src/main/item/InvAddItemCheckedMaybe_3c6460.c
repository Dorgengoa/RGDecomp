/* rgp:protos */
#define RGP_SELF_InvAddItemCheckedMaybe_3c6460 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

s32 InvAddItemCheckedMaybe_3c6460(void *a, void *b, void *c, void *d, s32 *out)
{
    s32 n;

    n = 0;
    InvAddItemCoreMaybe_3c6540(a, b, d, c, -1, 1, &n);
    if (out != 0) {
        *out = n;
    }
    if (n > 0) {
        return 0;
    }
    return 1;
}
