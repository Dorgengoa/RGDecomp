/* rgp:protos */
#define RGP_SELF_EvCmdMenuWinReset_265310 1
#include "port/game_protos.h"
#line 1
#include "vec.h"

/* Twin of EvCmdMenuWinShowScreenCapture_265070.  Two levers, both measured there:
   - the gp defaults are written through NAMED `Vec4 *` locals (plain member
     writes bunch the loads and cost 8 bad words);
   - the guard tests $2 with a PLAIN `bnez` and copies the handle into $16 in
     its delay slot, which is the ASSIGNMENT-IN-CONDITION form.  Naming the
     result first and then testing it gives `daddu $16,$2 / bnel $16,$0`,
     one word longer. */

typedef struct Cmd { s32 a, b; } Cmd;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

extern f32 D_0047E900, D_0047E904, D_0047E908, D_0047E90C;
extern f32 D_0047E910, D_0047E914, D_0047E918, D_0047E91C;

s32 EvCmdMenuWinReset_265310(Cmd *p0)
{
    Vec4 a, b;
    Vec4 *qa = &a;
    Vec4 *qb = &b;
    void *h;

    if ((h = MenuWinGet_2653e0(ScriptGetInt_26a2a0((s32)p0))) == 0) {
        return 0;
    }
    MenuWinInit_26c450(h);
    qa->x = D_0047E900;
    qa->y = D_0047E904;
    qa->z = D_0047E908;
    qa->w = D_0047E90C;
    qb->x = D_0047E910;
    qb->y = D_0047E914;
    qb->z = D_0047E918;
    qb->w = D_0047E91C;
    MenuWinSetDrawMode_26c3e0(h, 0);
    MenuWinSetBlendMode_26c270(h, 1);
    MenuWinSetPos_26c3b0(h, &a);
    MenuWinSetColor_26c380(h, &b);
    MenuWinSetSize_26c320(h, 0x200, 0x1C0);
    return 1;
}
