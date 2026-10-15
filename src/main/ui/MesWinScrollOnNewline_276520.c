#include "types.h"
#pragma divbyzerocheck on

typedef struct Obj {
    u8 pad0[0x44];
    s32 x44;
    u8 pad48[0x56 - 0x48];
    s16 x56;
    u8 pad58[2];
    s16 x5A[19];
    s32 x80;
} Obj;

extern s32 D_0045F208[4];
extern s32 MesWinGetFrameType_272b20(Obj *);
extern s32 MesWinGetPage_272230(Obj *);
extern s32 MesWinGetScrollY_271700(Obj *);
extern void MesWinSetScrollTarget_2716e0(Obj *, s32);

void MesWinScrollOnNewline_276520(Obj *arg0) {
    s32 b;
    s32 a;
    s16 d;

    if (MesWinGetFrameType_272b20(arg0) == 9) {
        b = arg0->x5A[MesWinGetPage_272230(arg0) + 1];
        a = arg0->x5A[MesWinGetPage_272230(arg0)];
        if ((a == 1 && b == 1 && arg0->x5A[0] == 1) ||
            (a == 1 && b == 2 && arg0->x5A[0] == 2) ||
            (a == 1 && b == 3 && arg0->x5A[0] == 2) ||
            (a == 2 && b == 2 && arg0->x5A[0] == 1) ||
            (a == 2 && b == 2 && arg0->x5A[0] == 2) ||
            (a == 2 && b == 3 && arg0->x5A[0] == 1) ||
            (a == 2 && b == 3 && arg0->x5A[0] == 2) ||
            (a == 3 && b == 2 && arg0->x5A[0] == 1) ||
            (a == 3 && b == 2 && arg0->x5A[0] == 2) ||
            (a == 3 && b == 3 && arg0->x5A[0] == 1) ||
            (a == 3 && b == 3 && arg0->x5A[0] == 2)) {
            MesWinSetScrollTarget_2716e0(arg0, MesWinGetScrollY_271700(arg0) - (s16)(D_0045F208[0] + 4));
        } else if ((a == 2 && b == 1 && arg0->x5A[0] == 1) ||
                   (a == 3 && b == 1 && arg0->x5A[0] == 1)) {
            MesWinSetScrollTarget_2716e0(arg0, MesWinGetScrollY_271700(arg0) - (s16)(D_0045F208[0] + 4) * 2);
        }
    } else {
        d = D_0045F208[0] + 4;
        if (arg0->x56 / d - ((arg0->x80 - arg0->x44) / d + 1) <= 0) {
            MesWinSetScrollTarget_2716e0(arg0, MesWinGetScrollY_271700(arg0) - d);
        }
    }
}
