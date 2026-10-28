/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuYesNoCursorMoveCb_5200b0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005200B0 -- writes the two rodata heights into the 0x20-stride
 * record array; `sll $3,$3,5` is the stride-32 index off p->f10. */

typedef struct Rec {
    u8  pad00[0x8];
    s16 f08;
    u8  pad0A[0x16];
} Rec;                                          /* 0x20 */

typedef struct Box {
    u8  pad00[0x10];
    s16 f10;
} Box;

extern void *D_00484920;          /* gp - 0x850 */
extern s16 normal_D_00526858;
extern s16 normal_D_0052685A;

/*rgp*/

s32 normal_ThinkMenuYesNoCursorMoveCb_5200b0(Box *p)
{
    Rec *r;

    r = ((Rec *)UiGetWidgetSprite_28fe10(D_00484920, 0x753E, 0));
    if (r == NULL) {
        return 0;
    }
    r[0].f08 = normal_D_00526858;
    r[1].f08 = normal_D_00526858;
    r[p->f10].f08 = normal_D_0052685A;
    return 1;
}
