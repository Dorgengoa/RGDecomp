/* rgp:protos */
#define RGP_SELF_insect_InsectBattleFlowStageCaption_508670 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* insect 0x00508670 -- 592 bytes, 148 instructions.  State dispatch on
 * insect_InsectBattleGetStep_50d6a0(o, 0); five arms plus a default. */

typedef struct Obj {
    u8  pad0000[0x4F90];
    u8  f4F90[0x2C];                /* +0x4F90 */
    u8  f4FBC;                      /* +0x4FBC */
    u8  pad4FBD[0x5000 - 0x4FBD];
    u8  f5000[4];                   /* +0x5000 */
    u8  pad5004[0x5DB0 - 0x5004];
    s32 f5DB0;                      /* +0x5DB0 */
    u8  pad5DB4[0x5EFE - 0x5DB4];
    s16 f5EFE;                      /* +0x5EFE */
    u8  pad5F00[0x5FC8 - 0x5F00];
    f32 f5FC8;                      /* +0x5FC8 */
} Obj;

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

void insect_InsectBattleFlowStageCaption_508670(Obj *o)
{
    s32 h;
    s32 id;
    s32 p;

    h = ((s32)GetMapMgr_201a90());
    id = o->f5EFE + 0xBEA;
    switch (insect_InsectBattleGetStep_50d6a0(o, 0)) {
    case 1:
        MapMgrCaptionLoad_1e2f10(h, id, 0);
        insect_InsectBattleSetStep_50d7a0(o, 6, 0, -1);
        o->f5DB0 = 0x1E;
        break;
    case 6:
        if (((unsigned char)insect_InsectLoaderIsIdle_512030()) != 0) {
            if (o->f5DB0 <= 0) {
                MapMgrCaptionNop_1e2670(h);
                MapMgrCaptionNop_1e2660(h, (s32)(15.0f / o->f5FC8));
                MapMgrCaptionShow_1e2650(h);
                p = ((s32)GetCaptionPanel_340420());
                MapCaptionSetWaitFrames_33f180(((s32)MapMgrGetCaption_1e56c0(h)), (s32)(10.0f / o->f5FC8));
                UiPanelSetTimers_33e8f0(p, (s32)(10.0f / o->f5FC8));
                insect_InsectBattleSetStep_50d7a0(o, 9, 0, -1);
            }
        }
        break;
    case 9:
        if (UiPanelIsOpen_33dd30(((s32)GetCaptionPanel_340420())) == 0) {
            o->f5DB0 = (s32)(10.0f / o->f5FC8);
            insect_InsectBattleSetStep_50d7a0(o, 10, 0, -1);
            o->f4FBC &= 0xFD;
        }
        break;
    case 10:
        if (insect_InsectCursorSetGetEvents_5119f0(o->f4F90, -1) != 0) {
            o->f5DB0 = 0;
        }
        if (o->f5DB0 <= 0) {
            insect_InsectBattleSetStep_50d7a0(o, 11, 0, -1);
            insect_InsectBattleSetState_50d8c0(o, 6, 2, -1);
        }
        break;
    case 11:
        insect_InsectBattleSetState_50d8c0(o, 6, 0, -1);
        break;
    }
}
