/* rgp:protos */
#define RGP_SELF_MinimapIsCellExploredXZ_3254f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/

int MinimapIsCellExploredXZ_3254f0(void *a, void *b, void *c, f32 x, f32 y)
{
    u8 buf[16] __attribute__((aligned(16)));
    u8 *d;
    u32 n;

    d = buf;
    n = 0x10;
    if (d != 0) {
        do {
            *d = 0;
            n--;
            d++;
        } while (n != 0);
    }
    *(f32 *)&buf[0] = x;
    *(f32 *)&buf[8] = y;
    return MinimapIsCellExplored_325550(a, buf, b, c);
}
