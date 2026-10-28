/* rgp:protos */
#define RGP_SELF_InsectCageMgrAddId_39b060 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Foo0039b060 {
    u8 pad0[0x94];
    s16 arr94[6];
    s16 unkA0;
} Foo0039b060;

void InsectCageMgrAddId_39b060(Foo0039b060 *arg0, s32 arg1)
{
    s16 count;
    s32 i;

    count = arg0->unkA0;
    if (count < 6) {
        for (i = 0; i < count; i++) {
            if (arg0->arr94[i] == arg1) {
                return;
            }
        }
        arg0->arr94[count] = arg1;
        arg0->unkA0 = arg0->unkA0 + 1;
    }
}
