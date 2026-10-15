#include "types.h"

extern "C" {
s32 NavRemoveGraphById_30a3b0(s32);
s32 HandleEntryRelease_3f12f0(u8 *, u8 *, s32);
s32 HandleEntryInit_3f40a0(u8 *);
s32 EventObjMgrRemoveByIdFwdThunk_2fd970(s32);
extern u8 D_004644C8[0x400];
}

extern "C" s32 HandleEntriesReleaseExcept_3f0aa0(u8 *arg0, s32 arg1)
{
    u8 *p;
    s32 n;
    s32 i;
    bool found;
    s16 t;
    s32 *q;
    s32 v;

    p = *(u8 **)(arg0 + 0x20);
    n = *(s32 *)D_004644C8;
    for (i = 0; i < n; i++, p += 0x20) {
        found = false;
        t = *(s16 *)(p + 8);
        if (t != 3 && t != 4) {
        } else {
            q = *(s32 **)p;
            if (q != 0) {
                v = *q;
                if (v == arg1) {
                    found = true;
                }
                if (!found) {
                    NavRemoveGraphById_30a3b0(v);
                    EventObjMgrRemoveByIdFwdThunk_2fd970(v);
                }
            }
        }
        if (!found) {
            HandleEntryRelease_3f12f0(arg0, p, 1);
            HandleEntryInit_3f40a0(p);
        }
    }
    return 1;
}
