#include "types.h"

struct Obj0 { s32 m00; };

extern s32 BufWriteU32_370f10(s32, s32, s32);

s32 SerialWriteChunkHeader_370e50(s32 p0, s32 p1, s32 p2, s32 p3, struct Obj0 *p4)
{
    s32 n;
    s32 q;
    s32 t;
    s32 r;

    if (p0 != 0) {
        if (p1 > 0) {
            goto ok;
        }
    }
    return 0;
ok:
    n = 0;
    q = p0;
    t = BufWriteU32_370f10(q, p1, p2);
    n = n + t;
    q = q + t;
    t = BufWriteU32_370f10(q, p1, p3);
    n = n + t;
    q = q + t;
    r = BufWriteU32_370f10(q, p1, 0);
    if (p4 != 0) {
        if (r > 0) {
            p4->m00 = p0 + n;
            *(s32 *)(p0 + n) = 0;
        }
    }
    return n + r;
}
