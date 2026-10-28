/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuTacticsSelectState_4fd140 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FD140 -- the equip-compare panel's confirm handler.  The
 * func_28E170 menu call is issued twice (once inside the `b` arm, once
 * unconditionally) and its return is the three-way action code 1/2/other.
 *
 * The four `lwc1`/`swc1` at sp+0x30 are the {0,1,2,3} index table copied out
 * of small data one word at a time; sp+0x30 is then indexed by the record's
 * f12.  `lui $2,0xBF80 / mtc1 $2,$f15` is an inline -1.0f. */

typedef struct Rec { u8 pad00[0x12]; s16 f12; } Rec;
typedef struct Ent { u8 pad00[0xC]; s32 f0C; } Ent;

extern u8 D_004B2570[];

extern f32   D_0047D278;          /* gp - 0x7EF8 */
extern f32   D_0047D35C;          /* gp - 0x7E14 */
extern f32   D_0047D51C;          /* gp - 0x7C54 */
extern f32   D_00480580;          /* gp - 0x4BF0 */
extern f32   D_00480584;          /* gp - 0x4BEC */
extern f32   D_00480588;          /* gp - 0x4BE8 */
extern f32   D_0048058C;          /* gp - 0x4BE4 */
extern void *D_00484498;          /* gp - 0xCD8  */
extern void *D_0048449C;          /* gp - 0xCD4  */
extern void *D_004844A0;          /* gp - 0xCD0  */
extern s16   D_004844E4;          /* gp - 0xC8C  */

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuTacticsSelectState_4fd140(void *a, s32 b)
{
    s32  r;
    Rec *o;
    Ent *e;
    f32  v[4] __attribute__((aligned(16)));

    if (b != 0) {
        UiEntryListSelectByTag_28ea90(D_004844A0, 0x55F6, 1);
        MenuGridCursorInput_28e170(D_004844A0, D_004B2570, 5, 0);
        ((Rec *)UiEntryListGetCurrentData_28ec60(D_004844A0))->f12 = 0;
    }
    r = MenuGridCursorInput_28e170(D_004844A0, D_004B2570, 5, 0);
    o = ((Rec *)UiEntryListGetCurrentData_28ec60(D_004844A0));
    if (r == 2) {
        PlayMenuSe_289ef0(6);
        StateMachineSetState_28ede0(D_00484498, 0x560A, 0);
    } else if (r == 1) {
        v[0] = D_00480580;
        v[1] = D_00480584;
        v[2] = D_00480588;
        v[3] = D_0048058C;
        e = ((Ent *)GetGameData_1fede0());
        if (e == 0) {
            return 0;
        }
        OptionsSetTacticsMode_3d5f50(e->f0C, *(s32 *)&v[o->f12]);
        UiSetWidgetColor_2905b0(D_0048449C, 0x38, D_0047D35C, D_0047D35C, D_0047D35C, -1.0f);
        UiFadeWidgetColor_2904e0(D_0048449C, 0x38, D_0047D278, D_0047D278, D_0047D278, -1.0f,
                    D_0047D51C);
        PlayMenuSe_289ef0(3);
        if (o->f12 == 2) {
            D_004844E4 = 2;
            StateMachineSetState_28ede0(D_00484498, 0x560B, 0);
        } else {
            StateMachineSetState_28ede0(D_00484498, 0x560A, 0);
        }
    }
    return 1;
}
