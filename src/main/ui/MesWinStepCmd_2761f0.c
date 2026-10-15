#include "types.h"

typedef struct {
    u16 id;
    u8 pad2[6];
} Cmd;

typedef struct {
    u8 pad0[0x5A];
    s16 x5A;
    u8 pad5C[0x68];
    Cmd cmd[1];
} Obj;

extern void MesWinAddShownEnd_271670(Obj *, s32);
extern s32 MesWinGetShownEnd_271680(Obj *);
extern void MesWinSetPageWait_272200(Obj *, s32);
extern s32 MesWinGetPage_272230(Obj *);
extern f32 MesWinGetTypeCursor_272b00(Obj *);
extern void MesWinSetTypeCursor_272b10(Obj *, f32);
extern void MesWinScrollOnPageEnd_2763c0(Obj *);
extern void MesWinScrollOnNewline_276520(Obj *);

s32 MesWinStepCmd_2761f0(Obj *p)
{
    s32 id;

    id = p->cmd[MesWinGetShownEnd_271680(p)].id;
    MesWinAddShownEnd_271670(p, 1);
    switch (id) {
    case 0xFF00:
        p->x5A++;
        if (MesWinGetPage_272230(p) == 0) {
            MesWinSetTypeCursor_272b10(p, 1.0f + MesWinGetTypeCursor_272b00(p));
        }
        if (MesWinGetPage_272230(p) > 0) {
            MesWinScrollOnNewline_276520(p);
        }
        return 0;
    case 0xFF03:
        MesWinSetPageWait_272200(p, 1);
        MesWinScrollOnPageEnd_2763c0(p);
        return 1;
    case 0xFF01:
        MesWinSetTypeCursor_272b10(p, 1.0f + MesWinGetTypeCursor_272b00(p));
        MesWinScrollOnPageEnd_2763c0(p);
        return 2;
    case 0xFF02:
        MesWinSetTypeCursor_272b10(p, 1.0f + MesWinGetTypeCursor_272b00(p));
        return 0;
    default:
        if (id >= 0xF900 && id <= 0xF9FF) {
            goto do_x;
        }
        if (id >= 0xF800 && id <= 0xF8FF) {
            goto do_x;
        }
        if (id >= 0xF700 && id <= 0xF7FF) {
        do_x:
            MesWinSetTypeCursor_272b10(p, 1.0f + MesWinGetTypeCursor_272b00(p));
            return 0;
        }
        return 0;
    }
}
