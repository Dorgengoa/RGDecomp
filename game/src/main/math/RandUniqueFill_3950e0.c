/* rgp:protos */
#define RGP_SELF_RandUniqueFill_3950e0 1
#include "port/game_protos.h"
#line 1
#pragma divbyzerocheck on
#include "types.h"

/*rgp*/

void RandUniqueFill_3950e0(s32 *arr, s32 n, s32 m)
{
    s32 i;
    u8 found;
    s32 j;

    for (i = 0; i < n; i++) {
        arr[i] = Rand_133710() % m;
        for (;;) {
            found = 0;
            for (j = i - 1; j >= 0; j--) {
                if (arr[i] == arr[j]) {
                    found = 1;
                    break;
                }
            }
            if ((u8)found != 1) {
                break;
            }
            arr[i] = Rand_133710() % m;
        }
    }
}
