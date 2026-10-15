#include "types.h"

struct S1F1120 { u8 pad000[0x66]; u8 f66_b0 : 1; u8 f66_b1 : 1; u8 f66_r : 6; };

extern struct S1F1120 *CharaResFindById_1f0530(void *a, void *c);

void CharaResDeferReleaseById_1f1120(void *a, s32 unused, void *c)
{
    struct S1F1120 *q;

    q = CharaResFindById_1f0530(a, c);
    if (q != 0) {
        q->f66_b1 = 1;
    }
}
