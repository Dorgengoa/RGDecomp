/* rgp:protos */
#define RGP_SELF_EvCmdCastSetObjFlags_2457c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
typedef struct { s32 a, b; } E8_2457c0;
struct O2457c0 { u8 pad000[0x60]; u8 m60; };
struct C2457c0 { s32 m00; struct O2457c0 *m04; };
extern struct C2457c0 * gEventContext;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 EvCmdCastSetObjFlags_2457c0(E8_2457c0 *p0, s32 p1)
{
    u8 *base;
    s32 h;
    s32 x;
    s32 v;
    s32 f;

    base = &gEventContext->m04->m60;
    h = EventCastFindKeyByName_24bb50(base, ScriptGetCodeAddr_249050(p0++));
    x = EventCastGetObjId_24c160(base, h, 0);
    v = ScriptGetInt_2490f0(p0++);
    f = 1;
    if (p1 >= 3) {
        f = ScriptGetInt_2490f0(p0);
    }
    if (f != 0) {
        ObjRecSetFlags_1c3e00(gEventContext->m00, 1, x, v);
    } else {
        ObjRecClearFlags_1c3dc0(gEventContext->m00, 1, x, v);
    }
    return 1;
}
