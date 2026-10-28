/* rgp:protos */
#define RGP_SELF_EvCmdNpcObjFindByNpcId_259b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_259b30;
struct T259b30 { s16 m00; };
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdNpcObjFindByNpcId_259b30(E8_259b30 *p0)
{
    s32 h;
    s32 a;
    s32 i;
    s32 k;
    struct T259b30 *e;

    h = ((s32)GetNpcObjTable_312860());
    a = ScriptGetInt_26a2a0(p0++);
    i = 0;
    while (i < 0x20) {
        k = i + 0xC0;
        e = ((struct T259b30 *)NpcObjFindDefById_2fb490(h, k));
        if (e != 0) {
            if (e->m00 == a) {
                ScriptSetRefInt_26a1e0(p0, k);
                return 1;
            }
        }
        i = i + 1;
    }
    ScriptSetRefInt_26a1e0(p0, -1);
    return 1;
}
