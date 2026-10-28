/* rgp:protos */
#define RGP_SELF_DListRemove_42e4e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma opt_common_subs off

s32 DListRemove_42e4e0(void *arg0, void *arg1)
{
    s32 ok;
    void *t;
    void **t2;

    ok = (arg1 != NULL) && (*(void **)((u8 *)arg1 + 8) == arg0);
    if (!ok) {
        return 0;
    }
    if (*(void **)((u8 *)arg0 + 0) == arg1) {
        *(void **)((u8 *)arg0 + 0) = *(void **)((u8 *)arg1 + 4);
    }
    if (*(void **)((u8 *)arg0 + 4) == arg1) {
        *(void **)((u8 *)arg0 + 4) = *(void **)((u8 *)arg1 + 0);
    }
    t = *(void **)((u8 *)arg1 + 0);
    if (t != NULL) {
        *(void **)((u8 *)t + 4) = *(void **)((u8 *)arg1 + 4);
    }
    t2 = *(void **)((u8 *)arg1 + 4);
    if (t2 != NULL) {
        *t2 = *(void **)((u8 *)arg1 + 0);
    }
    *(void **)((u8 *)arg1 + 8) = NULL;
    *(void **)((u8 *)arg1 + 0) = NULL;
    *(void **)((u8 *)arg1 + 4) = NULL;
    *(u16 *)((u8 *)arg0 + 8) -= 1;
    *(u16 *)((u8 *)arg0 + 0xA) = 1;
    while (*(u16 *)((u8 *)arg0 + 0xA) < *(u16 *)((u8 *)arg0 + 8)) {
        *(u16 *)((u8 *)arg0 + 0xA) *= 2;
    }
    return 1;
}
