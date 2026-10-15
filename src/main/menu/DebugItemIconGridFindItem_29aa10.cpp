#include "types.h"

typedef struct A29aa10 {
    u8 pad00[8];
    s32 f8;
} A29aa10;

typedef struct B29aa10 {
    u8 pad00[0x40];
    A29aa10 *f40;
} B29aa10;

typedef struct M29aa10 {
    u8 pad00[8];
    B29aa10 *f8;
} M29aa10;

typedef struct R29aa10 {
    u8 pad00[0x2C];
    s16 f2C;
} R29aa10;

typedef struct It29aa10 {
    s32 f0;
    s16 f4;
    s16 f6;
} It29aa10;

extern "C" M29aa10 *GetGameData_1fede0(void);
extern "C" void IterInit_370170(It29aa10 *it, s32 x);
extern "C" R29aa10 *IterNext_370040(It29aa10 *it);

extern "C" R29aa10 *DebugItemIconGridFindItem_29aa10(s32 a, s32 b)
{
    It29aa10 it;
    M29aa10 *m;
    R29aa10 *r;
    s32 x;
    s32 cnt;
    s32 idx;
    bool ok;

    m = GetGameData_1fede0();
    if (m == 0) {
        return 0;
    }
    x = m->f8->f40->f8;
    if (x != 0) {
        x += 0x88;
    }
    IterInit_370170(&it, x);
    cnt = it.f4;
    if (b < 8) {
        idx = 0x7D0;
        idx += (a / 8 + 1) * 0x64;
        idx += (a % 8) + (b * 8) + 1;
    } else if (b >= 0x18) {
        idx = 0xBB8;
        idx += (a / 8 + 1) * 0x64;
        idx += (a % 8) + ((b % 8) * 8) + 1;
    } else {
        idx = 0x3E8;
        idx += (a / 8 + 1) * 0x64;
        if (b >= 0x10) {
            idx += 0x190;
        }
        idx += (a % 8) + ((b % 8) * 8) + 1;
    }
    goto entry;
body:
    if (r->f2C == idx) goto post;
    cnt--;
entry:
    r = IterNext_370040(&it);
    ok = !r;
    if (ok) goto post;
    if (cnt > 0) goto body;
post:
    if (cnt <= 0) {
        return 0;
    }
    return r;
}
