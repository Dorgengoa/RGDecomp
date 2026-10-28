/* rgp:protos */
#define RGP_SELF_factory_FactoryGridRotateRect_4fe650 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
} Box;

s32 factory_FactoryGridRotateRect_4fe650(void *w, Box *out, Box *b, Box *c, s32 d)
{
    if (out == 0 || c == 0 || b == 0) {
        return 0;
    }
    switch (d & 3) {
    case 0:
        out->f00 = c->f00 + b->f00;
        out->f02 = c->f02 + b->f02;
        out->f04 = c->f00 + b->f04;
        out->f06 = c->f02 + b->f06;
        return 1;
    case 1:
        out->f00 = c->f00 + b->f02;
        out->f02 = c->f06 - b->f04;
        out->f04 = c->f00 + b->f06;
        out->f06 = c->f06 - b->f00;
        return 1;
    case 2:
        out->f00 = c->f04 - b->f04;
        out->f02 = c->f06 - b->f06;
        out->f04 = c->f04 - b->f00;
        out->f06 = c->f06 - b->f02;
        return 1;
    case 3:
        out->f00 = c->f04 - b->f06;
        out->f02 = c->f02 + b->f00;
        out->f04 = c->f04 - b->f02;
        out->f06 = c->f02 + b->f04;
        return 1;
    }
    return 0;
}
