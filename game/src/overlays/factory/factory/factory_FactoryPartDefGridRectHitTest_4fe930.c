/* rgp:protos */
#define RGP_SELF_factory_FactoryPartDefGridRectHitTest_4fe930 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Box {
    s16 f00;
    s16 f02;
    s16 f04;
    s16 f06;
} Box;

/*rgp*/

s32 factory_FactoryPartDefGridRectHitTest_4fe930(void *w, s32 x, s32 y, void *d, void *e)
{
    Box b __attribute__((aligned(16)));
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
