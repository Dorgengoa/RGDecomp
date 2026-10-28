/* rgp:protos */
#define RGP_SELF_EventObjSetRot_2e7240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 m[16]; } M_002e7240;
typedef struct {
    u8 pad[0xC];
    f32 fC, f10, f14;
    u8 pad2[0xC];
    f32 f24, f28, f2C, f30, f34, f38, f3C, f40, f44;
} T_002e7240;

/*rgp*/

void EventObjSetRot_2e7240(T_002e7240 *p, f32 *src)
{
    M_002e7240 m __attribute__((aligned(16)));

    p->fC = src[0];
    p->f10 = src[1];
    p->f14 = src[2];
    MatFromRot_1cb180(&m, src);
    p->f24 = m.m[0];
    p->f28 = m.m[1];
    p->f2C = m.m[2];
    p->f30 = m.m[4];
    p->f34 = m.m[5];
    p->f38 = m.m[6];
    p->f3C = m.m[8];
    p->f40 = m.m[9];
    p->f44 = m.m[10];
}
