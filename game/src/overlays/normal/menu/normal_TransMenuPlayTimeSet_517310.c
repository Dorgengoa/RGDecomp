/* rgp:protos */
#define RGP_SELF_normal_TransMenuPlayTimeSet_517310 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00517310 -- the four out-parameters land at sp+0x2C/0x28/0x24/0x20
 * and three of them are stored back with `sd`, so those fields are 64-bit. */

typedef struct Obj {
    u8  pad00[8];
    s64 f08;
    s16 f10;
    u8  pad12[0x28 - 0x12];
    s64 f28;
    u8  pad30[0x48 - 0x30];
    s64 f48;
} Obj;

extern void *D_004846E8;          /* gp - 0xA88 */

/*rgp*/
/*rgp*/
/*rgp*/

void normal_TransMenuPlayTimeSet_517310(s32 id)
{
    Obj *p;
    s32  a;
    s32  b;
    s32  c;
    s32  d;

    p = ((Obj *)UiGetWidgetSubItem_28f2b0(D_004846E8, id, 0));
    if (p != NULL) {
        PlayTimeGet_28aeb0(&a, &b, &c, &d);
        if (a > 99) {
            p->f10 = 3;
            UiSetSpriteX_28fcd0(D_004846E8, 0x754C, 0xE7, 4);
        } else {
            p->f10 = 2;
            UiSetSpriteX_28fcd0(D_004846E8, 0x754C, 0xF1, 4);
        }
        p->f08 = a;
        p->f28 = b;
        p->f48 = c;
    }
}
