/* rgp:protos */
#define RGP_SELF_ImgGetEntryCount_159250 1
#define RGP_SELF_kind 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 memcmp(const void *, const void *, u32);
extern char D_00458B18[];
extern char D_00458B20[];
extern char D_00458B28[];
extern char D_00458B30[];

static inline s32 kind(s32 *s) {
    if (s == NULL) {
        return 0;
    }
    if (memcmp(s, D_00458B20, 2) != 0) {
        return 0;
    }
    if (memcmp(s, D_00458B28, 3) == 0) {
        return 1;
    }
    if (memcmp(s, D_00458B30, 3) == 0) {
        return 2;
    }
    if (memcmp(s, D_00458B18, 3) == 0) {
        return 3;
    }
    return 0;
}

s32 ImgGetEntryCount_159250(s32 *arg0) {
    s32 k;

    if (arg0 == NULL) {
        return 0;
    }
    k = kind(arg0);
    if (k == 0) {
        return 0;
    }
    if ((u32)(k - 1) < 2) {
        return arg0[1];
    }
    if (k == 3) {
        return arg0[2];
    }
    return 0;
}
