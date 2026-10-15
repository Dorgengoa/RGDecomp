#include "types.h"

typedef struct Struct002768f0 {
    u8 pad0[0x5A];
    s16 unk5A;
    u8 pad5C[0x1DF4 - 0x5C];
    s32 unk1DF4;
} Struct002768f0;

extern s32 MesWinFindPageStart_270840(Struct002768f0 *a, s32 b);
extern void MesWinSetShownStart_2716b0(Struct002768f0 *a, s32 b);
extern void MesWinSetPageFrames_271ed0(Struct002768f0 *a, s32 b);
extern s32 MesWinIsPageWait_2721f0(void);
extern void MesWinSetPageWait_272200(Struct002768f0 *a, s32 b);
extern void MesWinAddPage_272210(Struct002768f0 *a, s32 b);
extern s32 MesWinGetPage_272230(Struct002768f0 *a);
extern f32 MesWinGetTypeCursor_272b00(Struct002768f0 *a);
extern void MesWinSetTypeCursor_272b10(Struct002768f0 *a, f32 b);
extern void MesWinScrollOnAdvance_276830(Struct002768f0 *a);
extern void ScenePlaySe_277690(s32 a);

void MesWinAdvance_2768f0(Struct002768f0 *arg0)
{
    s32 temp_4;

    if (MesWinIsPageWait_2721f0() != 0) {
        MesWinSetPageWait_272200(arg0, 0);
        MesWinAddPage_272210(arg0, 1);
        arg0->unk5A = 0;
        MesWinSetPageFrames_271ed0(arg0, 0);
        MesWinSetShownStart_2716b0(arg0, MesWinFindPageStart_270840(arg0, MesWinGetPage_272230(arg0)));
        MesWinSetTypeCursor_272b10(arg0, MesWinGetTypeCursor_272b00(arg0) - 1.0f);
        MesWinScrollOnAdvance_276830(arg0);
        temp_4 = arg0->unk1DF4;
        if (temp_4 >= 0) {
            ScenePlaySe_277690(temp_4);
        }
    }
}
