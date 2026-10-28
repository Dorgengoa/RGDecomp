/* rgp:protos */
#define RGP_SELF_EventVoiceCountFreeChans_24fb70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

s32 EventVoiceCountFreeChans_24fb70(void *arg0) {
    s32 count;
    s32 sentinel;
    void *node;
    void *next;
    void *p;

    count = 0;
    if (*(void **)((u8 *)arg0 + 4) != 0) {
        sentinel = -1;
    } else {
        sentinel = 0;
        *(void **)((u8 *)arg0 + 4) = *(void **)((u8 *)arg0 + 0);
        *(s32 *)((u8 *)arg0 + 8) = 0;
    }
    if (sentinel != 0) {
        return 0;
    }
    goto test;
    do {
        if (*(s32 *)p == 0) {
            count++;
        }
test:
        node = *(void **)((u8 *)arg0 + 4);
        if (node == 0) {
            p = 0;
        } else {
            p = (u8 *)node + 0x10;
            next = *(void **)node;
            *(void **)((u8 *)arg0 + 4) = next;
            if (next == 0) {
                *(s32 *)((u8 *)arg0 + 8) = 1;
            }
        }
    } while (p != 0);
    *(void **)((u8 *)arg0 + 4) = 0;
    *(s32 *)((u8 *)arg0 + 8) = 0;
    return count;
}
