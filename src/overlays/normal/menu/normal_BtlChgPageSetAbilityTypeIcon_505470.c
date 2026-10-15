/* NORMAL 0x00505470-0x005056A8: four local row tables and widget lookup.
 * The owner must be forwarded to the accessor thunk. It remains live in $4
 * across the table-copy loops; declaring the thunk argument-free loses it.
 * Source pointer, destination pointer, then counter are both declared and
 * initially assigned in that order. This order and the owner argument form
 * a verified cross; changing only one part does not reproduce retail.
 * Widget IDs arrive as 32-bit arguments; callers explicitly narrow to u16
 * where their retail instructions do so. No inherited pragma.
 */
#include "types.h"


typedef struct Pair00505470 { s16 a; s16 b; } Pair00505470;
extern Pair00505470 D_00525800[5];
extern Pair00505470 D_00525820[5];
extern Pair00505470 D_00525840[5];
extern Pair00505470 D_00525860[5];

typedef struct W00505470 {
    s16 f0;
    s16 f2;
    s16 f4;
    s16 f6;
    s16 f8;
    s16 fA;
    s16 fC;
    s16 fE;
} W00505470;

typedef struct R00505470 {
    u8 pad000[0x20];
    W00505470 *f020;
} R00505470;

extern void      *normal_UiPageGetLayout_289b60(void *a);
extern R00505470 *func_290460(void *a, s32 b);

s32 normal_BtlChgPageSetAbilityTypeIcon_505470(void *a, s32 b, s32 c)
{
    Pair00505470 t90[5];
    Pair00505470 t70[5];
    Pair00505470 t50[5];
    Pair00505470 t30[5];
    Pair00505470 *s;
    Pair00505470 *d;
    s32 i;
    s32 n;
    void *v;
    R00505470 *r;
    W00505470 *w;

    s = D_00525800;
    d = t90;
    i = 5;
    do {
        d->a = s->a;
        d->b = s->b;
        s++;
        d++;
    } while (--i > 0);
    s = D_00525820;
    d = t70;
    i = 5;
    do {
        d->a = s->a;
        d->b = s->b;
        s++;
        d++;
    } while (--i > 0);
    s = D_00525840;
    d = t50;
    i = 5;
    do {
        d->a = s->a;
        d->b = s->b;
        s++;
        d++;
    } while (--i > 0);
    s = D_00525860;
    d = t30;
    i = 5;
    do {
        d->a = s->a;
        d->b = s->b;
        s++;
        d++;
    } while (--i > 0);

    switch (c) {
    case 1:
        n = 1;
        break;
    case 2:
        n = 0;
        break;
    case 3:
        n = 2;
        break;
    case 4:
        n = 3;
        break;
    case 5:
        n = 4;
        break;
    case 11:
        n = 5;
        break;
    case 12:
        n = 6;
        break;
    case 13:
        n = 7;
        break;
    case 14:
    default:
        n = 9;
        break;
    }

    v = normal_UiPageGetLayout_289b60(a);
    if (v == 0) {
        return 0;
    }
    r = func_290460(v, b);
    if (r == 0) {
        return 0;
    }
    w = r->f020;
    if (w == 0) {
        return 0;
    }
    w->f0 = 0;
    w->f2 = 0;
    w->fC = ((s16 *)t50)[n];
    w->f4 = w->fC;
    w->fE = ((s16 *)t30)[n];
    w->f6 = w->fE;
    w->f8 = ((s16 *)t90)[n];
    w->fA = ((s16 *)t70)[n];
    return 0;
}
