#include "types.h"
/* normal 0x004F68D0 -- enables the first p->f3DE slots of the row at +0x14
 * from the caller's array, disabling anything parked at -180. */
typedef struct Item {
    f32 f00;
    s16 f04;
} Item;

typedef struct Rec {
    u8  pad000[0x8];
    s64 f08;
} Rec;

typedef struct N {
    u8  pad000[0x14];
    u8  f014[0x3CA];
    s16 f3DE;
} N;

extern void  func_290010(void *p, u16 id, s32 a, s32 b);
extern void  func_290F60(void *p, u16 id, s32 a, s32 b);
extern Rec  *func_28F2B0(void *p, u16 id, s32 a);

void normal_FieldHudAttackChainMarkersSet_4f68d0(N *p, Item *q, s32 n)
{
    Rec *r;
    u16  id;
    s32  i;

    id = 5;
    for (i = 0; i < p->f3DE; i++, q++) {
        if (q->f04 == 0) {
            func_290010(p->f014, id, 0, -1);
            id++;
        } else {
            if (q->f00 <= -180.0f) {
                func_290010(p->f014, id, 0, -1);
                id++;
            } else {
                func_290010(p->f014, id, 1, -1);
                func_290F60(p->f014, id, (s32)q->f00, 0);
                id++;
            }
        }
    }
    r = func_28F2B0(p->f014, 2, 0);
    if (r != NULL) {
        r->f08 = n;
    }
}
