/* rgp:protos */
#define RGP_SELF_EvCmdObjRecGetFlags_269b40 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_269b40;
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 D_00481F78;

s32 EvCmdObjRecGetFlags_269b40(E8_269b40 *p0, s32 p1)
{
    s32 r0;
    s32 r1;
    s32 r2;

    if (p1 < 3) {
        return 0;
    }
    r0 = ScriptGetInt_26a2a0(p0++);
    r1 = ScriptGetInt_26a2a0(p0++);
    r2 = ObjRecGetFlags_1c3d90(D_00481F78, r0, r1);
    ScriptSetRefInt_26a1e0(p0, r2);
    return 1;
}
