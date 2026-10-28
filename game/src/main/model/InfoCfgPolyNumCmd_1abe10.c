/* rgp:protos */
#define RGP_SELF_InfoCfgPolyNumCmd_1abe10 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_1abe10;
struct O1abe10 { u8 pad000[0x4C0]; s32 m4C0; s32 m4C4; };
extern struct { struct O1abe10 *v; s32 pad[3]; } D_0049D418;
/*rgp*/

s32 InfoCfgPolyNumCmd_1abe10(E8_1abe10 *p0, s32 p1)
{
    struct O1abe10 *o;
    s32 v;

    o = D_0049D418.v;
    if (o == 0) {
        return 0;
    }
    o->m4C0 = 0;
    o->m4C4 = 0;
    if (p1 > 0) {
        v = VariantGetInt_15f780(p0++);
        o->m4C0 = o->m4C0 + v;
    }
    if (p1 == 2) {
        v = VariantGetInt_15f780(p0);
        o->m4C4 = o->m4C4 + v;
    }
    return 1;
}
