/* rgp:protos */
#define RGP_SELF_normal_TransHunterCloseSlide_51f550 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0051F550 -- two-arm state dispatch on D_004848C4 (gp-0x8AC).
 * beql INTO each arm => compiled switch, case order reversed in the chain. */

typedef struct Slot { u8 pad00[8]; s16 f08; } Slot;
typedef struct Node { u8 pad00[0x20]; Slot *f20; } Node;

extern void *D_00484710;          /* gp - 0xA60 */
extern s32   D_004848C4;          /* gp - 0x8AC */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_TransHunterCloseSlide_51f550(void)
{
    Node *n;
    s32 x;
    s32 y;

    switch (D_004848C4) {
    case 0:
        UiPlaceRowWidgetPairMaybe_28cf40(1, 0, 0x753D, 0x7538, D_00484710);
        UiGetWidgetPos_2910a0(D_00484710, 0x753D, &x, &y);
        if (x < 0x1F) {
            D_004848C4 = 1;
            UiFadeWidgetAlpha_290690(D_00484710, 0x7553, 0.0f, -0.05f, -1.0f);
        }
        break;
    case 1:
        UiFadeWidgetAlpha_290690(D_00484710, 0x7551, 1.0f, 0.05f, -1.0f);
        n = ((Node *)UiFindWidget_290460(D_00484710, 0x7551));
        n->f20->f08 = 0xE0;
        D_004848C4 = 4;
        break;
    }
    return 0;
}
