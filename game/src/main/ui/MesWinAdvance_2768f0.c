/* rgp:protos */
#define RGP_SELF_MesWinAdvance_2768f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Struct002768f0 {
    u8 pad0[0x5A];
    s16 unk5A;
    u8 pad5C[0x1DF4 - 0x5C];
    s32 unk1DF4;
} Struct002768f0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesWinAdvance_2768f0(Struct002768f0 *arg0)
{
    s32 temp_4;

    if (((signed char)MesWinIsPageWait_2721f0((void *)arg0)) != 0) {
        MesWinSetPageWait_272200(arg0, 0);
        MesWinAddPage_272210(arg0, 1);
        arg0->unk5A = 0;
        MesWinSetPageFrames_271ed0(arg0, 0);
        MesWinSetShownStart_2716b0(arg0, MesWinFindPageStart_270840(arg0, ((short)MesWinGetPage_272230(arg0))));
        MesWinSetTypeCursor_272b10(arg0, MesWinGetTypeCursor_272b00(arg0) - 1.0f);
        MesWinScrollOnAdvance_276830(arg0);
        temp_4 = arg0->unk1DF4;
        if (temp_4 >= 0) {
            ScenePlaySe_277690(temp_4);
        }
    }
}
