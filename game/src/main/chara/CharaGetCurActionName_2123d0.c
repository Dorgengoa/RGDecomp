/* rgp:protos */
#define RGP_SELF_CharaGetCurActionName_2123d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
struct T2123D0 { u8 pad000[0xA14]; void *fA14; u8 padA18[0x20]; s16 fA38; };
/*rgp*/
s32 CharaGetCurActionName_2123d0(struct T2123D0 *p)
{
    void *q;
    if (p->fA38 == 0) return 0;
    q = p->fA14;
    if (q != 0) {
        return CharaTableGetName_225480(q);
    }
    return 0;
}
