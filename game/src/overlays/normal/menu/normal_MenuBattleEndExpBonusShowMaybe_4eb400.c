/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndExpBonusShowMaybe_4eb400 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004EB400 -- the 0x11 sub-widget bring-up, gated on the current
 * entity's 0x20 -> 0x238 sub-object being present and its 0x1C6 flag set.
 * One argument in `$4`, saved in `$16` in func_1FEDE0's delay slot; frame -0x20
 * is entirely the save area (`sq $16` + `sd $31` at 0x10).
 *
 * Both `lw`s happen before the null test, so the 0x20 deref is UNGUARDED and
 * the `beql`/`beqz` pair is nested ifs to the shared tail.  `sh $3,0xA8($16)`
 * precedes func_290690 in source.  func_2905B0 takes FOUR floats (the same gp
 * literal three times via `mov.s`, then -1.0f); func_2904E0 takes FIVE
 * (1.0f x3, -1.0f, then 0x0047D924 in $f16).
 *
 * The three gp float operands are mwcc .lit4 POOL entries (0.05f / 1.9f /
 * -0.1f at 0x0047D844 / 0x0047D35C / 0x0047D924), NOT globals: spelled
 * `extern f32 D_0047Dxxx` the object is 10 bad words, every one of them an
 * ORDER permutation of the same instruction multiset, because mwcc pins an
 * extern global's load against the `sh 0xA8` alias hazard.  Written as
 * literals the schedule is retail's exactly.  Scored through the
 * scripts/t_lit4.py pool retarget (build/dv_oslit_na04.py).
 */

typedef struct Node { u8 pad000[0x1C6]; u8 f1C6; } Node;
typedef struct Sub  { u8 pad000[0x238]; Node *f238; } Sub;
typedef struct Ent  { u8 pad000[0x20];  Sub  *f20;  } Ent;

typedef struct Obj {
    u8  pad000[0x14];
    u8  f014[0xA8 - 0x14];
    s16 f0A8;
} Obj;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_MenuBattleEndExpBonusShowMaybe_4eb400(Obj *p)
{
    Node *n;

    n = ((Ent *)GetGameData_1fede0())->f20->f238;
    if (n != NULL) {
        if (n->f1C6 != 0) {
            p->f0A8 = 1;
            UiFadeWidgetAlpha_290690(p->f014, 0x11, 1.0f, 0.05f, -1.0f);
            UiSetWidgetColor_2905b0(p->f014, 0x11, 1.9f, 1.9f, 1.9f, -1.0f);
            UiFadeWidgetColor_2904e0(p->f014, 0x11, 1.0f, 1.0f, 1.0f, -1.0f, -0.1f);
        }
    }
}
