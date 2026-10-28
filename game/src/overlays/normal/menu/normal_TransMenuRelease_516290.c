/* rgp:protos */
#define RGP_SELF_normal_TransMenuRelease_516290 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x00516290 -- the scene-enter REGISTRATION LIST: two overlay
 * bring-up calls, the 0x4B2570 text-device open/close pair, the block of
 * eight gp state stores, then a null-guarded chain that hands the current
 * selection to the camera.
 *
 * Every `beqz` in the chain jumps to the SHARED TAIL, and what retail falls
 * through into is the `if` body -- so the guards are NESTED ifs, not early
 * returns.  `sh $0, -0xA20($28)` and `sw $0, 0x518($16)` each sit in the
 * following call's delay slot, so both stores precede their call in source.
 * `lui $2,0x4170 / mtc1 $2,$f12` is the literal 15.0f. */

typedef struct Act { u8 pad00[0x30]; s16 f30; } Act;
typedef struct Ent { u8 pad00[0x18]; Act *f18; } Ent;
typedef struct Cam { u8 pad00[0x518]; s32 f518; } Cam;

extern u8 D_004B2570[];

extern s32   D_00484770;          /* gp - 0xA00  */
extern s16   D_004806C8;          /* gp - 0x4AA8 */
extern void *D_00484740;          /* gp - 0xA30  */
extern void *D_00484724;          /* gp - 0xA4C  */
extern void *D_0048475C;          /* gp - 0xA14  */
extern s16   D_0048474C;          /* gp - 0xA24  */
extern s8    D_00484748;          /* gp - 0xA28  */
extern s16   D_00484750;          /* gp - 0xA20  */

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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void normal_TransMenuRelease_516290(void)
{
    Ent *e;
    Cam *cam;
    s32  h;
    s32  sel;

    normal_TransMenuResFree_5181a0();
    normal_TransMenuSubResFree_517cf0();
    PadClearRepeatAll_183960(D_004B2570);
    PadClearStickDpadThreshold_183940(D_004B2570);
    D_00484770 = 0;
    D_004806C8 = 2;
    D_00484740 = 0;
    D_00484724 = 0;
    D_0048475C = 0;
    D_0048474C = 0;
    D_00484748 = 0;
    D_00484750 = 0;
    normal_TransWarpListFree_51a990();
    NameTableFreeGroup_158ac0(GetDrawCtxNameTable_15de40(), 0x32D);
    e = ((Ent *)GetGameData_1fede0());
    h = ((s32)GetMapMgr_201a90());
    if (h != 0) {
        sel = 0;
        MapSlotsFindBlockById_1e49b0(h, e->f18->f30, &sel);
        if (sel != 0) {
            if (MinimapFindForArea_1dcb50(sel) != 0) {
                cam = ((Cam *)GetMinimapMgr_201a70());
                if (cam != 0) {
                    cam->f518 = 0;
                    MinimapMgrFadeInStart_321e80(cam, 15.0f);
                    MinimapMgrResetView_321770(cam);
                }
            }
        }
    }
    ResGroupUnloadGroup_42b650(GetMenuResGroup_206a40(), 2);
}
