/* rgp:protos */
#define RGP_SELF_LightStateGetPacket_1428f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct P001428f0 {
    s32 w0;
    s32 w4;
} P001428f0;

typedef struct S001428f0 {
    u8 pad[0xF20];
    s32 flag;                 /* +0xF20 */
    u8 pad2[0x36B4 - 0xF24];
    P001428f0 *p;             /* +0x36B4 */
} S001428f0;

s32 LightStateGetPacket_1428f0(S001428f0 *s, s32 *out)
{
    P001428f0 *p;

    if (s->flag == 0) {
        return 0;
    }
    p = s->p;
    *out = p->w0;
    return p->w4;
}
