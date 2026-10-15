#include "types.h"

typedef struct Obj003a6190 {
    u8 unk0;
    u8 pad1;
    struct {
        u8 bit0 : 1;
        u8 bit1 : 1;
        u8 bit2 : 1;
        u8 unused : 5;
    } unk2;
} Obj003a6190;

s32 StatusEntryIsRunning_3a6190(Obj003a6190 *arg0)
{
    s32 result;
    s32 orv;

    result = (arg0->unk0 != 0);
    if (result) {
        orv = arg0->unk2.bit0 || arg0->unk2.bit1;
        if (!orv) {
            result = !arg0->unk2.bit2;
        } else {
            result = orv ^ 1;
        }
    }
    return result;
}
