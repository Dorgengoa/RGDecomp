/* rgp:protos */
#define RGP_SELF_StrCmpU8_1834b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 StrCmpU8_1834b0(u8 *a, u8 *b) {
    u8 ca;
    u8 cb;

    for (;;) {
        ca = *a;
        cb = *b;
        if (cb < ca) {
            return 1;
        }
        if (ca < cb) {
            return -1;
        }
        if (ca == 0 && cb == 0) {
            return 0;
        }
        if (ca == 0) {
            return -1;
        }
        if (cb == 0) {
            return 1;
        }
        a++;
        b++;
    }
}
