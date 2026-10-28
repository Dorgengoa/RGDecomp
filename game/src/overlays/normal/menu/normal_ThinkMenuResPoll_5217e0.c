/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuResPoll_5217e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005217E0 -- two-slot poll loop over the 0x38-byte normal_D_00528110 array. */

typedef struct Slot { u8 pad00[0x38]; } Slot;

extern Slot normal_D_00528110[];

extern s8    D_00484940;          /* gp - 0x830 */
extern void *D_0048491C;          /* gp - 0x854 */
extern void *D_00484970;          /* gp - 0x800 */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ThinkMenuResPoll_5217e0(void)
{
    s32 i;
    Slot *s;
    void *out;
    void *r;

    for (i = 0; i < 2; i++) {
        s = &normal_D_00528110[i];
        if (LoadHandleGetId_28b220(s) != -1) {
            if (((unsigned char)LoadHandleIsPending_28b210(s)) != 0) {
                if (LoadHandleGetStatus_28b2e0(s) == 1) {
                    r = LoadHandleGetData_28b270(s, &out);
                    if (i == 1) {
                        normal_ThinkMenuLayoutBuild_521400(r);
                    } else {
                        LoadHandleRegisterData_28b320(s, D_00484970, 0x32E, D_0048491C);
                    }
                    LoadHandleFree_28b230(s);
                }
            }
        }
    }
    if (((unsigned char)LoadHandlesAllReady_28b070(normal_D_00528110, 2)) == 1) {
        D_00484940 = 1;
        return 1;
    }
    return 0;
}
