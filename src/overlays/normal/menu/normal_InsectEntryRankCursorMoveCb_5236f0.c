#include "types.h"
/* normal 0x005236F0 -- three readouts on one row, whose y is nudged by
 * `5 - D_004807C4` clamped at zero. */
typedef struct Ret {
    u8    pad000[0x20];
    void *f20;
} Ret;

typedef struct N {
    u8  pad000[0x12];
    s16 f12;
} N;

extern s32 D_004807C4;            /* gp - 0x49AC */
extern u8  D_00528180[];

extern Ret *func_290460(void *p, s32 id);
extern void func_28B8E0(void *p, s32 a, s32 b, s32 c);
extern void func_28FBF0(void *p, s32 id, s32 a, s32 y);
extern void func_28F850(void *p, s32 id, s32 a, s32 y);
extern void func_290F60(void *p, s32 id, s32 a, s32 y);

s32 normal_InsectEntryRankCursorMoveCb_5236f0(N *p)
{
    Ret *r;
    s32  n;

    r = func_290460(D_00528180, 3);
    if (r == NULL) {
        return 0;
    }
    if (r->f20 == NULL) {
        return 0;
    }
    func_28B8E0(r->f20, 0xFA, 0xAA, 6);
    n = 5 - D_004807C4;
    if (n < 0) {
        n = 0;
    }
    func_28FBF0(D_00528180, 3, 0, p->f12 + 4 + n);
    func_28F850(D_00528180, 3, 0, p->f12 + 4 + n);
    func_290F60(D_00528180, 2, 0x84, (p->f12 + n) * 27 + 0x78);
    return 1;
}
