/* rgp:protos */
#define RGP_SELF_MenuCursorObjSetModel_386290 1
#include "port/game_protos.h"
#line 1
#include "types.h"

struct T386290 { u8 pad000[0x4]; void *f04; };

extern f32 D_0047D5D0;
/*rgp*/

void MenuCursorObjSetModel_386290(struct T386290 *p, void *a)
{
    u8 buf[16] __attribute__((aligned(16)));
    u8 *d;
    u32 n;

    p->f04 = a;
    if (a == 0) return;
    d = buf;
    n = 0x10;
    if (d != 0) {
        do {
            *d = 0;
            n--;
            d++;
        } while (n != 0);
    }
    *(f32 *)&buf[0] = D_0047D5D0;
    *(f32 *)&buf[4] = D_0047D5D0;
    *(f32 *)&buf[8] = D_0047D5D0;
    ModelSetScale_150ff0(a, buf);
}
