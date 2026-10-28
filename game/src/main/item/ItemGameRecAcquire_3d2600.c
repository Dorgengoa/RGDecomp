/* rgp:protos */
#define RGP_SELF_ItemGameRecAcquire_3d2600 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 6;
} __attribute__((aligned(4))) BF;

typedef struct {
    u8 pad0[0x14];
    s16 x14;
    u8 pad16[2];
    BF *x18;
} O;

/*rgp*/
/*rgp*/
/*rgp*/
extern u8 *D_004838F0;

s32 ItemGameRecAcquire_3d2600(O *arg0)
{
    s32 id;
    BF *p;
    s32 z;

    if (D_004838F0 == NULL) {
        return 0;
    }
    if (arg0->x18 != NULL && arg0->x18->b0) {
        return 1;
    }

    id = GameRecFindFreeInsectSlot_3ce390(*(s32 *)(D_004838F0 + 0x174));
    p = ((BF *)GameRecGetInsectSlot_3ce350(*(s32 *)(D_004838F0 + 0x174), id));
    if (p == NULL) {
        return 0;
    }
    GameRecInsectSlotClear_3d2780(p);
    z = 0;
    arg0->x14 = id;
    arg0->x18 = p;
    p->b0 = 1;
    arg0->x18->b1 = z;

    return 1;
}
