#include "types.h"

extern void EventScratchRewind_301db0(void);
extern void EventScriptRecReset_2e3a90(void *);
extern void EventVolumeRecReset_2e4f20(void *);
extern void EventPathRecReset_2e43b0(void *);
extern void EvSwitchObjReset_2f8670(void *);
extern void EvFollowObjReset_2f8170(void *);
extern void EvDoorObjReset_304440(void *);
extern void EvMapObjResetMaybe_366f20(void *);
extern void ObjTypeVehicleReset_3383c0(void *);
extern void EvM05ChangeReset_3522b0(void *);
extern void EvObjLiftReset_336500(void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern s32 D_00482820;
extern s32 D_00482824;
extern s32 D_00482828;
extern s32 D_0048282C;
extern s32 D_00482830;
extern s32 D_00482834;
extern s32 D_00482838;
extern s32 D_0048283C;
extern s32 D_00482840;
extern s32 D_00482844;
extern s32 D_00482848;
extern s32 D_0048284C;
extern s32 D_00482850;
extern s32 D_00482854;
extern s32 D_00482858;
extern s32 D_0048285C;
extern s32 D_00482860;
extern s32 D_00482864;
extern s32 D_00482868;
extern s32 D_0048286C;
extern s32 D_00482870;
extern s32 D_00482874;
extern s32 D_00482878;
extern s32 D_0048287C;
extern s32 D_00482880;
extern s32 D_00482884;
extern s32 D_00482888;
extern s32 D_0048288C;
extern s32 D_00482890;
extern s32 D_00482894;
extern u8 D_004E66B0[];
extern u8 D_004E66D0[];
extern u8 D_004E6700[];
extern u8 D_004E6720[];
extern u8 D_004E6880[];
extern u8 D_004E69D0[];
extern u8 D_004E6B80[];
extern u8 D_004E6EC0[];
extern u8 D_004E7000[];
extern u8 D_004E7110[];

void EvScriptTemplatesReset_301c20(void)
{
    EventScratchRewind_301db0();
    D_00482820 = 0;
    D_00482824 = 0;
    D_00482828 = 0;
    D_0048282C = 0;
    EventScriptRecReset_2e3a90(D_004E66B0);
    D_00482830 = 0;
    D_00482834 = 0;
    EventVolumeRecReset_2e4f20(D_004E66D0);
    D_00482838 = 0;
    D_0048283C = 0;
    D_00482840 = 0;
    D_00482844 = 0;
    D_00482848 = 0;
    D_0048284C = 0;
    EventPathRecReset_2e43b0(D_004E6700);
    EvSwitchObjReset_2f8670(D_004E6720);
    EvFollowObjReset_2f8170(D_004E6880);
    D_00482860 = 0;
    D_00482864 = 0;
    D_00482850 = 0;
    D_00482854 = 0;
    D_00482858 = 0;
    D_0048285C = 0;
    EvDoorObjReset_304440(D_004E69D0);
    D_00482868 = 0;
    D_0048286C = 0;
    D_00482870 = 0;
    D_00482874 = 0;
    EvMapObjResetMaybe_366f20(D_004E6B80);
    D_00482878 = 0;
    D_0048287C = 0;
    ObjTypeVehicleReset_3383c0(D_004E6EC0);
    D_00482890 = 0;
    D_00482894 = 0;
    EvM05ChangeReset_3522b0(D_004E7110);
    D_00482880 = 0;
    D_00482884 = 0;
    D_00482888 = 0;
    D_0048288C = 0;
    EvObjLiftReset_336500(D_004E7000);
}
