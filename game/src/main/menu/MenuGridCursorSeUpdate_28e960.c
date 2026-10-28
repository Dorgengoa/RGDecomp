/* rgp:protos */
#define RGP_SELF_MenuGridCursorSeUpdate_28e960 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad[0x18];
    void *f18;
    u8 pad2[4];
    u8 f20_b0 : 1;
    u8 f20_b1 : 7;
    s8 f21;
} T_0028e960;

/*rgp*/

void MenuGridCursorSeUpdate_28e960(T_0028e960 *p)
{
    s8 t;

    t = p->f21;
    if (t > 0) {
        p->f21 = t - 1;
        return;
    }
    if (p->f20_b0 == 0) return;
    SoundPlayScaledVolume_1b9520(p->f18, 4, 0, 1.0f);
    p->f21 = 2;
    p->f20_b0 = 0;
}
