/* rgp:protos */
#define RGP_SELF_normal_ShopMenuBuyRowIconsRefresh_50dae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct DAE0M {
    u8   pad00[0x10];
    s16 *f10;
} DAE0M;

typedef struct DAE0P {
    DAE0M *f00;
} DAE0P;

extern DAE0P *normal_D_00527D30[];
extern s16    normal_D_00526520[][2];

extern void *D_004845C8;          /* gp - 0xBA8 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuBuyRowIconsRefresh_50dae0(s32 a, s32 b)
{
    DAE0P **tbl;
    void   *ctx;
    DAE0M  *o;
    s32     i;
    DAE0P  *p;
    s32     r;

    ctx = GetGameData_1fede0();
    tbl = &normal_D_00527D30[a];
    for (i = 0; i < 8; i++) {
        p = tbl[i];
        if (p == NULL) {
            return 0;
        }
        o = p->f00;
        if (o == NULL) {
            return 0;
        }
        UiSetSpriteX_28fcd0(D_004845C8, 0x22, 0x25, i);
        if (SkillFlowCountByItemMaybe_3e97c0(ctx, o->f10[0], -1, 0, 1, 1, 0) > 0) {
            if (b != 0) {
                if (((unsigned char)ShopRowIsLocked_3ce690(p)) == 0) {
                    UiSetSpriteUv_28f970(D_004845C8, 0x22, 0xA6, 0x42, i);
                    continue;
                }
            }
        }
        r = ShopRowGetIcon_3ce8e0(p);
        UiSetSpriteUv_28f970(D_004845C8, 0x22, normal_D_00526520[r][0], normal_D_00526520[r][1], i);
    }
    return 1;
}
