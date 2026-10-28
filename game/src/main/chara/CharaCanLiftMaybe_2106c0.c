/* rgp:protos */
#define RGP_SELF_CharaCanLiftMaybe_2106c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 CharaCanLiftMaybe_2106c0(u8 *arg0) {
    s16 t;
    s16 u;

    if (*(s16 *)(arg0 + 0xA38) != 0) {
        t = *(s16 *)(arg0 + 0xA36);
        if (t == 16) {
            return 0;
        }
        if (t == 17) {
            return 0;
        }
        if (t == 15) {
            return 0;
        }
        if (t == 17) {
            return 0;
        }
        if (t == 19) {
            return 0;
        }
        if (t == 25) {
            return 0;
        }
        if (t == 26) {
            return 0;
        }
        if (t == 27) {
            return 0;
        }
        if (t == 28) {
            return 0;
        }
        if (t == 30) {
            return 0;
        }
        if (t == 31) {
            return 0;
        }
    }
    switch (*(s16 *)(arg0 + 0xA32)) {
    case 2:
    case 3:
        return 1;
    }
    return 0;
}
