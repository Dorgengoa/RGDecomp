#pragma opt_loop_invariants off
#include "types.h"

typedef struct N24c0d0 {
    struct N24c0d0 *m00;
    u8 pad04[0x8];
    s32 m0C;
} N24c0d0;

typedef struct It24c0d0 {
    N24c0d0 *m00;
    N24c0d0 *m04;
    s32 m08;
} It24c0d0;

s32 EventCastGetKind_24c0d0(It24c0d0 *it, s32 a, s32 b)
{
    s32 err;
    u8 *p;
    N24c0d0 *cur;
    N24c0d0 *nxt;

    if (it->m04 != 0) {
        err = -1;
    } else {
        err = 0;
        it->m04 = it->m00;
        it->m08 = 0;
    }
    if (err != 0) {
        p = 0;
        goto ret;
    }
    cur = it->m04;
    goto entry;
loop:
    if (a != b) {
        cur = it->m04;
    } else {
        it->m04 = 0;
        goto zero8;
    }
entry:
    if (cur == 0) {
        p = 0;
        goto check;
    }
    b = cur->m0C;
    p = (u8 *)cur + 0x10;
    nxt = cur->m00;
    it->m04 = nxt;
    if (nxt == 0) {
        it->m08 = 1;
    }
check:
    if (p != 0) {
        goto loop;
    }
    it->m04 = 0;
zero8:
    it->m08 = 0;
ret:
    if (p == 0) {
        return -1;
    }
    return *(s32 *)(p + 0x8);
}
