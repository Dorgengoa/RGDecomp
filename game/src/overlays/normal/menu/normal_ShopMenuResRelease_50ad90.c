/* rgp:protos */
#define RGP_SELF_normal_ShopMenuResRelease_50ad90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x0050AD90 -- releases the two live handles in the gp table at
 * 0x00480640 and the single one at 0x004845FC. */
typedef struct E {
    s32 f00;
    s32 f04;
} E;

extern E     D_00480640[1];       /* gp - 0x4B30 */
extern void *D_004845FC;          /* gp - 0xB74  */

/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ShopMenuResRelease_50ad90(void)
{
    void *h;
    s32   i;

    h = GetLoaderMgr_1f59d0();
    for (i = 0; i < 2; i++) {
        if (D_00480640[i].f04 != 0) {
            if (D_00480640[i].f00 != -1) {
                LoaderReleaseById_1cd340(h, D_00480640[i].f00);
                D_00480640[i].f00 = -1;
                D_00480640[i].f04 = 0;
            }
        }
    }
    if (D_004845FC != NULL) {
        HeapHandleFree_1cdae0(h, D_004845FC);
        D_004845FC = NULL;
    }
    return 1;
}
