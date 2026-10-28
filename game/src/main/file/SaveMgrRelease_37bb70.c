/* rgp:protos */
#define RGP_SELF_SaveMgrRelease_37bb70 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

extern void *D_004831D0;
extern s32 D_004831D4;
extern s32 D_004831D8;
extern s32 D_004831F8;
extern u8 D_004831F0;

void SaveMgrRelease_37bb70(void)
{
    void *p;

    if (D_004831D0 != 0) {
        sceMcEndThunk_12c870();
    }
    p = GetGameData_1fede0();
    if (p != 0) {
        GameDataReleaseWorld_3e53e0(p);
    }
    D_004831D0 = 0;
    D_004831D4 = 0;
    D_004831D8 = 0;
    D_004831F8 = 0;
    D_004831F0 = 0;
}
