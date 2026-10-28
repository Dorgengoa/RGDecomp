/* rgp:protos */
#define RGP_SELF_McBuildIconPath_376400 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
extern void *strcat(void *, void *);

extern u8 D_00463A18[];
extern u8 D_00463A28[];

void McBuildIconPath_376400(s32 arg0, s32 arg1, s32 arg2)
{
    McBuildSaveDirPath_376460(arg0, arg1);
    if (arg2 == 0) {
        strcat((void *)arg0, D_00463A18);
    } else {
        strcat((void *)arg0, D_00463A28);
    }
}
