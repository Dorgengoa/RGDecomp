/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuResRequest_5218d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005218D0 -- teardown counterpart of 0x005217E0.  The `== -1` test is
 * SHARED after the if/else (retail materialises -1 in both arms and tests once),
 * and D_00484968 must be declared as an 8-byte array so its indexed load keeps
 * the gp-relative `addiu $2,$28,-0x808` base instead of a lui/%lo pair. */

typedef struct Slot { u8 pad00[0x38]; } Slot;

extern Slot normal_D_00528110[];

extern void *D_00484968[2];       /* gp - 0x808 */
extern void *D_00484970;          /* gp - 0x800 */
extern void *D_0048491C;          /* gp - 0x854 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ThinkMenuResRequest_5218d0(void)
{
    s32 i;
    s32 r;

    LoadHandleArrayReset_28b160(normal_D_00528110, 2);
    for (i = 0; i < 2; i++) {
        if (i == 0) {
            r = LoadHandleRequestAlloc_28b3e0(&normal_D_00528110[i], &D_00484970, D_00484968[i], 0,
                            D_0048491C, 0);
        } else {
            r = LoadHandleRequestFile_28b550(&normal_D_00528110[i], D_00484968[i], 0, 0);
        }
        if (r == -1) {
            break;
        }
    }
    LoaderQueueSeparatorGlobal_28afd0();
    return 0;
}
