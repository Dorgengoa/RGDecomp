#include "types.h"

struct T3A1770 { u8 pad000[0xB94]; u8 *fB94; };

extern s32 StatusEntryIsRunning_3a6190(u8 *e);

u8 *CharaSysStatusGet_3a1770(struct T3A1770 *p, s32 i, s32 flag)
{
    u8 *e;

    if (i < 0 || i >= 0x20) return 0;
    e = p->fB94 + i * 8 + 4;
    if (flag != 0) {
        if (StatusEntryIsRunning_3a6190(e) == 0) {
            return 0;
        }
    }
    return e;
}
