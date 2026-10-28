/* rgp:protos */
#define RGP_SELF_CharaCanFollowLeaderMaybe_20ffc0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 CharaCanFollowLeaderMaybe_20ffc0(void *arg0)
{
    s32 f;
    s16 a32;
    s16 a36;
    s32 v;

    f = *(s32 *)((u8 *)arg0 + 0xA44);
    if (f & 0x20000) {
        return 0;
    }
    if (f & 0x10000) {
        return 0;
    }
    a32 = *(s16 *)((u8 *)arg0 + 0xA32);
    if (a32 == 6) {
        return 0;
    }
    if (a32 == 7) {
        return 0;
    }
    a36 = *(s16 *)((u8 *)arg0 + 0xA36);
    if (a36 == 30) {
        return 0;
    }
    if (a36 == 31) {
        return 0;
    }
    v = *(s16 *)((u8 *)arg0 + 0xB60) >= 0;
    if (v != 0) {
        v = *(s32 *)((u8 *)arg0 + 0xB5C) != 0;
    }
    if (v != 0) {
        v = (*(s16 *)((u8 *)arg0 + 0xB62) & 0x20) != 0;
    }
    return v ^ 1;
}
