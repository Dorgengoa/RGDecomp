/* rgp:protos */
#define RGP_SELF_EventVoiceChanSetRequested_24f1d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

void EventVoiceChanSetRequested_24f1d0(void *arg0, s32 arg1, s32 arg2, s8 arg3, s32 pd4, s32 arg5) {
    s32 sentinel;
    s32 var9;
    void *node;
    void *next;
    void *result;

    var9 = arg5;
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
        goto test;
        for (;;) {
            if (arg1 == var9) {
                break;
            }
        test:
            node = *(void **)((u8 *)arg0 + 4);
            if (node == 0) {
                result = 0;
            } else {
                var9 = *(s32 *)((u8 *)node + 0xC);
                result = (u8 *)node + 0x10;
                next = *(void **)node;
                *(void **)((u8 *)arg0 + 4) = next;
                if (next == 0) {
                    *(s32 *)((u8 *)arg0 + 8) = 1;
                }
            }
            if (result == 0) {
                break;
            }
        }
        *(void **)((u8 *)arg0 + 4) = 0;
        *(s32 *)((u8 *)arg0 + 8) = 0;
    }
    if (result != 0) {
        *(s32 *)((u8 *)result + 0x0) = 1;
        *(s32 *)((u8 *)result + 0x8) = 0;
        *(s32 *)((u8 *)result + 0x4) = arg2;
        *(s8 *)((u8 *)result + 0x20) = arg3;
    }
}
