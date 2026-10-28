/* rgp:protos */
#define RGP_SELF_MesWinScrollOnPageEnd_2763c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Obj {
    u8 pad0[0x5A];
    s16 x5A[1];
    s16 x5C[1];
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_0045F208[4];

void MesWinScrollOnPageEnd_2763c0(Obj *arg0)
{
    s32 b;
    s16 a;

    if (((short)MesWinGetPage_272230(arg0)) > 0 && ((short)MesWinGetFrameType_272b20(arg0)) == 9) {
        b = arg0->x5C[((short)MesWinGetPage_272230(arg0))];
        a = arg0->x5A[((short)MesWinGetPage_272230(arg0))];
        if ((a == 1 && b == 1) || (a == 1 && b == 2) || (a == 2 && b == 2) || (a == 3 && b == 2)) {
            MesWinSetScrollTarget_2716e0(arg0, MesWinGetScrollY_271700(arg0) - (s16)(D_0045F208[0] + 4));
            return;
        }
        if ((a == 2 && b == 1) || (a == 3 && b == 1)) {
            MesWinSetScrollTarget_2716e0(arg0, MesWinGetScrollY_271700(arg0) - (s16)(D_0045F208[0] + 4) * 2);
        }
    }
}
