#include "types.h"

typedef struct Elem004696a0 {
    s32 unk0;
    u8 pad4[0x2C - 0x4];
} Elem004696a0;

extern Elem004696a0 D_0049DD7C;
extern Elem004696a0 D_0049E87C;
extern const s8 D_0049DD70;
extern const s32 D_0049DD74;
extern const s32 D_0049DD78;

void StaticInitSoundThreadRing_4696a0(void)
{
    Elem004696a0 *p;

    p = &D_0049DD7C;
    do {
        p->unk0 = 0;
        p++;
    } while (p < &D_0049E87C);
    *(s8 *)&D_0049DD70 = 1;
    *(s32 *)&D_0049DD74 = 0;
    *(s32 *)&D_0049DD78 = 0;
}
