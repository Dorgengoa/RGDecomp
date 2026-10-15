#include "types.h"

typedef struct Obj001AB380 {
    u8 pad0[0x28];
    s32 unk28;
    s32 unk2C;
} Obj001AB380;

typedef struct Wrap0049D39C {
    Obj001AB380 *ptr;
    u8 pad4[8];
} Wrap0049D39C;

extern Wrap0049D39C D_0049D39C;
extern s32 D_0049D424[];
extern s32 D_0049D428[];

s32 InfoCfgKeyStartCmd_1ab380(void)
{
    Obj001AB380 *p = D_0049D39C.ptr;

    if (p == NULL) {
        return 0;
    }
    D_0049D424[0] = p->unk28 + (p->unk2C * 0x10);
    D_0049D428[0] = 0;
    return 1;
}
