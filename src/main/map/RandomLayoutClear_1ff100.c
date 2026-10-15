#include "types.h"

struct U1FF100 { s16 f0; };
struct T1FF100 { u8 pad000[0x18]; u8 *f18; };

extern struct T1FF100 *GetGameData_1fede0(void);

void RandomLayoutClear_1ff100(void)
{
    struct T1FF100 *r;
    struct U1FF100 *q;

    r = GetGameData_1fede0();
    q = (struct U1FF100 *)(r->f18 + 0x1C0);
    if (q != 0) {
        q->f0 = 0;
    }
}
