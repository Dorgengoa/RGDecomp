/* rgp:protos */
#define RGP_SELF_EventVoiceChanSetProtected_24e740 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

void EventVoiceChanSetProtected_24e740(void *arg0, s32 arg1, s8 arg2, s32 pd3, s32 arg4) {
    s32 sentinel;
    s32 var8;
    void *node;
    void *next;
    void *result;

    var8 = arg4;
    if (!(*(void **)((u8 *)arg0 + 4) == 0)) {
        sentinel = -1;
    } else {
        sentinel = 0;
        *(void **)((u8 *)arg0 + 4) = *(void **)((u8 *)arg0 + 0);
        *(s32 *)((u8 *)arg0 + 8) = 0;
    }
    if (sentinel != 0) {
        result = 0;
    } else {
        goto cond;
loop:
        if (arg1 == var8) {
            goto done;
        }
cond:
        node = *(void **)((u8 *)arg0 + 4);
        if (node == 0) {
            result = 0;
        } else {
            var8 = *(s32 *)((u8 *)node + 0xC);
            result = (u8 *)node + 0x10;
            next = *(void **)node;
            *(void **)((u8 *)arg0 + 4) = next;
            if (next == 0) {
                *(s32 *)((u8 *)arg0 + 8) = 1;
            }
        }
        if (result != 0) {
            goto loop;
        }
done:
        *(void **)((u8 *)arg0 + 4) = 0;
        *(s32 *)((u8 *)arg0 + 8) = 0;
    }
    if (result != 0) {
        *(s8 *)((u8 *)result + 0x20) = arg2;
    }
}
