/* rgp:protos */
#define RGP_SELF_normal_ThinkMenuConfirmState_5201a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x005201A0 -- the shop caption page tick.  `daddu $16,$2,$0` sits in
 * func_28EC60's DELAY SLOT, so `m` is func_28E170's result and the pointer the
 * f10 test reads is func_28EC60's -- the classic wrong-call misread.
 * `addiu $4,$28,-0x848` is the ADDRESS of D_00484928, so that global has to be
 * declared at or under the 8-byte small-data threshold or the addiu becomes a
 * lui/%lo pair. */

typedef struct Box  { u8 pad00[8]; s16 f08; u8 pad0A[0x28 - 0x0A]; s16 f28; } Box;
typedef struct Hdl  { u8 pad00[0x14]; s16 f14; s16 f16; } Hdl;
typedef struct Vw   { u8 pad00[0x10]; s16 f10; } Vw;
typedef struct Sess { u8 pad00[0x11]; s8 f11; } Sess;
typedef struct Sub  { s16 f00; } Sub;
typedef struct Rec  { u8 pad00[4]; s16 f04; u8 pad06[0x10 - 0x06]; Sub *f10; } Rec;
typedef struct Root { u8 pad00[0x18]; void *f18; } Root;

extern u8 D_004B2570;
extern u8 normal_D_00528030[];

extern s32   D_00484948;          /* gp - 0x828 */
extern s32   D_0048494C;          /* gp - 0x824 */
extern s32   D_00484950;          /* gp - 0x820 */
extern void *D_00484920;          /* gp - 0x850 */
extern void *D_00484928;          /* gp - 0x848 */
extern Sess *D_00484934;          /* gp - 0x83C */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_ThinkMenuConfirmState_5201a0(void *a, s32 b)
{
    Root *h;
    Hdl  *w;
    Box  *q;
    Rec  *e;
    Vw   *r;
    s32   m;

    if (b != 0) {
        UiEntryListSelectByTag_28ea90(normal_D_00528030, 0x7532, 0);
        ((Hdl *)UiEntryListFindByTag_28ea40(normal_D_00528030, 0x7532))->f14 = 0;
        q = ((Box *)UiGetWidgetSprite_28fe10(D_00484920, 0x753E, 0));
        if (q == 0) {
            return 0;
        }
        q->f08 = 0x4C;
        q->f28 = 0x18;
    }
    normal_ThinkMenuPromptScrollStep_521660(GameSceneGetTimeStep_1ceba0(GetCurrentScene_1f5be0()));
    m = MenuGridCursorInput_28e170(normal_D_00528030, &D_004B2570, 0, 0);
    r = ((Vw *)UiEntryListGetCurrentData_28ec60(normal_D_00528030));
    if (m == 1) {
        if (r->f10 == 0) {
            h = ((Root *)GetGameData_1fede0());
            w = ((Hdl *)UiEntryListFindByTag_28ea40(normal_D_00528030, 0x7531));
            e = ((Rec *)InvFindByCategoryIndex_3c86e0(h->f18, 0, D_00484934->f11, w->f14, w->f16, 0));
            if (e != 0) {
                D_0048494C = e->f10->f00;
                D_00484950 = e->f04;
                D_00484948 = 0;
            }
        } else if (r->f10 == 1) {
            D_00484948 = 1;
        }
        StateMachineSetState_28ede0(&D_00484928, 0x7536, 0);
    } else if (m == 2) {
        D_00484948 = 1;
        StateMachineSetState_28ede0(&D_00484928, 0x7536, 0);
    }
    return 1;
}
