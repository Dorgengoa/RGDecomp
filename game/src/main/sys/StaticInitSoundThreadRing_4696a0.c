/* rgp:protos */
#define RGP_SELF_StaticInitSoundThreadRing_4696a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Elem004696a0 {
    s32 unk0;
    u8 pad4[0x2C - 0x4];
} Elem004696a0;

extern Elem004696a0 D_0049DD7C;
extern Elem004696a0 D_0049E87C;
extern s8 D_0049DD70;
extern s32 D_0049DD74;
extern s32 D_0049DD78;

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
