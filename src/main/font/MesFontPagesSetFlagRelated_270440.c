#include "types.h"

typedef struct Ent_FUN_00270440 {
    u8 pad000[0x2B];
    u8 f2B;
} Ent_FUN_00270440;

extern Ent_FUN_00270440 *D_004C3140[];

void MesFontPagesSetFlagRelated_270440(s32 flag)
{
    s32 i;
    u8 v;
    Ent_FUN_00270440 *e;

    v = flag != 0;
    for (i = 4; i < 8; i++) {
        e = D_004C3140[i];
        if (e != 0) {
            e->f2B = v;
        }
    }
}
