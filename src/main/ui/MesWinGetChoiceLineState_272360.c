#include "types.h"

typedef struct Obj {
    u8 pad0[0x1C39];
    s8 mode;
    u8 pad1C3A[0x1C40 - 0x1C3A];
    s32 count;
    u8 pad1C44[0x1CE8 - 0x1C44];
    s8 tbl[1];
} Obj;

extern s32 MesWinGetChoiceIndex_271b50(Obj *);

s32 MesWinGetChoiceLineState_272360(Obj *a, s32 i)
{
    s32 v;

    if (i < a->count) {
        return 0;
    }
    v = a->tbl[i];
    if (v < 0) {
        if (MesWinGetChoiceIndex_271b50(a) >= 0) {
            switch (a->mode) {
            case -1:
                return 0;
            case 1:
                return (i == MesWinGetChoiceIndex_271b50(a)) ? 2 : 0;
            case 2:
                return (i == MesWinGetChoiceIndex_271b50(a)) ? 0 : 3;
            default:
                return i != MesWinGetChoiceIndex_271b50(a);
            }
        } else {
            return 0;
        }
    }
    return v;
}
