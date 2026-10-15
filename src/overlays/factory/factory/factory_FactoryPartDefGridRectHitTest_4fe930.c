#include "types.h"

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
} Box;

extern s32 factory_FactoryPartDefGetGridRect_4fe480(void *w, Box *b, void *d, void *e, s32 i);

s32 factory_FactoryPartDefGridRectHitTest_4fe930(void *w, s32 x, s32 y, void *d, void *e)
{
    Box b;
    s32 i;

    if (d == 0) {
        return 0;
    }
    i = 0;
    while (factory_FactoryPartDefGetGridRect_4fe480(w, &b, d, e, i) != 0) {
        i++;
        if (b.f04 >= x && b.f06 >= y && b.f00 <= x && b.f02 <= y) {
            return 1;
        }
    }
    return 0;
}
