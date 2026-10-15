#include "types.h"

struct U3CB150 { s16 f0; };
struct S3CB150 { u8 pad000[0x10]; struct U3CB150 *f10; };
struct T3CB150 { u8 pad000[0x24]; struct S3CB150 *f24; };

s32 PartyGetLocationGroupIdMaybe_3cb150(struct T3CB150 *p)
{
    struct S3CB150 *s;
    struct U3CB150 *u;

    s = p->f24;
    if (s != 0) {
        u = s->f10;
    } else {
        u = 0;
    }
    if (u == 0) {
        return -1;
    }
    return u->f0;
}
