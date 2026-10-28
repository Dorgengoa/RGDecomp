/* rgp:protos */
#define RGP_SELF_EffAttachIntegrateColor_197830 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 f0; s32 f4; } A_00197830;
typedef struct { u8 pad[0x10]; s32 f10; } E_00197830;
typedef struct { u8 pad[0x40]; s32 f40; u8 pad2[0xB4 - 0x44]; u8 *fB4; } B_00197830;

extern s32 D_00481360;
extern s32 D_0047E170;
/*rgp*/
/*rgp*/
/*rgp*/

void EffAttachIntegrateColor_197830(A_00197830 *a, B_00197830 *b, f32 v)
{
    E_00197830 *e;

    e = (E_00197830 *)(b->fB4 + a->f4 * 16);
    VecAddScaled_13bdd0(&b->f40, e, v);
    VecAddScaled_13bdd0(e, &e->f10, v);
    VecMax_13dfe0(&b->f40, &b->f40, &D_00481360);
    VecMin_13df90(&b->f40, &b->f40, &D_0047E170);
}
