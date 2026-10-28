/* rgp:protos */
#define RGP_SELF_MesSlotDraw_277d30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { s32 f0; void *f4; u8 pad[0x40]; s32 f48; } T_00277d30;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesSlotDraw_277d30(T_00277d30 *p)
{
    void *a;
    void *b;
    void *c;

    a = p->f4;
    if (a == 0) return;
    b = MesWinGetState_276a80(a);
    if (b == 0) return;
    c = GetDrawCtx_15de80();
    DrawListAddTexLoad_1418c0(c, p->f48, 1.0f);
    MesWinDraw_270cb0(p->f4);
}
