/* MATCH (s41m). Stale pre-match note follows -- PARKED: 1 round trip: mechanical conversion; not rescored after batch1 -- needs a follow-up score. */
#include "types.h"

extern s32 NodeObjIsInView_194200(void *);

s32 MapAreaModelCollectVisibleObjsMaybe_188060(void *arg0, void **arg1, s32 arg2)
{
    s32 cnt;
    void **tbl;
    s32 n;
    s32 i;
    void *p;

    n = 0;
    i = 0;
    tbl = *(void ***)((u8 *)arg0 + 0x540);
    cnt = *(s32 *)((u8 *)arg0 + 0x53C);
    while (i < cnt) {
        if (n >= arg2) {
            break;
        }
        p = tbl[i];
        if ((p != NULL) && (*(s16 *)((u8 *)p + 0x32) != 0) && (NodeObjIsInView_194200(p) != 0)) {
            *arg1 = p;
            n += 1;
            arg1 += 1;
        }
        i += 1;
    }
    return n;
}
