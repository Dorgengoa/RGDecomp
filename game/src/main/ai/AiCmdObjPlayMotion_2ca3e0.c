/* rgp:protos */
#define RGP_SELF_AiCmdObjPlayMotion_2ca3e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct E8 { s32 a; s32 b; } E8;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(char *, char *);
/*rgp*/

extern struct { s32 v; s32 pad[3]; } D_004DB920;
extern s32 D_004DB92C;
extern f32 D_0047D240;

s32 AiCmdObjPlayMotion_2ca3e0(E8 *p0)
{
    s32 h;
    s32 a;
    char *b;
    s32 c;
    s32 r;

    h = D_004DB920.v;
    a = ScriptSlotGetInt_2cc9c0(p0++);
    b = ((char *)ScriptSlotGetCodeAddr_2cc980(p0++));
    c = ScriptSlotGetInt_2cc9c0(p0);
    r = ((s32)ObjRecGetLiveObject_1c4a90(h, a));
    if (r == 0) {
        return 0;
    }
    if (((char *)ModelObjGetMotionName_1add90(r)) != 0) {
        if (strcmp(((char *)ModelObjGetMotionName_1add90(r)), b) == 0) {
            return 1;
        }
    }
    if (r != 0) {
        CharaPlayMotion_212590(D_004DB92C, r, b, c, D_0047D240);
    }
    return 1;
}
