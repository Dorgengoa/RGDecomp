/* rgp:protos */
#define RGP_SELF_CharaCmdMapParts_22d710 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* p0 is unused.  `sltu $2,$0,$2` is the boolean of the last call's result. */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

struct Obj0 {
    s32 m00;
};

s32 CharaCmdMapParts_22d710(struct Obj0 *p0, s32 p1, s32 argc)
{
    s32 a;
    s32 b;
    s32 c;
    s32 o;

    if (argc != 3) {
        return 0;
    }
    a = ((s32)GetMapMgr_201a90());
    b = ScriptArgGetStr_302cb0(p1);
    c = ScriptArgGetStr_302cb0(p1 + 5);
    o = MapFindObjInAreaByName_1e4470(a, b, c);
    if (o == 0) {
        return 1;
    }
    *(s16 *)(o + 0x32) = ScriptArgGetInt_302d70(p1 + 0xA) != 0;
    return 1;
}
