/* rgp:protos */
#define RGP_SELF_BtlEffSetRowCollectRefsMaybe_3f9da0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
typedef struct B3f9 { u8 pad0[9]; s8 n : 6; u8 pad2 : 2; u8 padA[2]; u8 *p; } B3f9;

s32 BtlEffSetRowCollectRefsMaybe_3f9da0(u8 *arg0, B3f9 * arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;
    s32 n;
    u8 *p;

    if (*(s32 *)(arg0 + 4) == 0) {
        return 0;
    }
    if (arg1 == NULL) {
        return arg4;
    }
    n = arg1->n;
    p = arg1->p;
    if (p != NULL) {
        if (n > 0) goto ok;
    }
    return arg4;
ok:
    for (i = 0; i < n; i++, p += 0x14) {
        arg4 = BtlEffRowCollectRefsMaybe_3f9d00(arg0, *(s32 *)(p + 0x10), arg2, arg3, arg4);
    }
    return arg4;
}
