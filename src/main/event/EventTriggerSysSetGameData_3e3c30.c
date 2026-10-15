#include "types.h"

extern u8 *D_00483990;
extern s32 D_00483994;
extern u8 D_00483998;
extern s32 D_0048399C;
extern s32 D_004801F4;
extern u8 D_004839A0;
extern u8 D_004839A4;
extern u8 D_004839A8;
extern s16 D_004839AC;
extern s16 D_004839B0;
extern s32 D_004839B4;
extern u8 D_004E9740[];
extern u8 D_004E9770[];
extern u8 D_004E9800[];
extern void ActionPacketClear_3e3e90(void *);
extern void SkillActionReset_3e3dd0(void *);
extern void SkillTimerReset_3e3d20(void *);

/* Every gp_rel global is a plain scalar extern; the three %hi/%lo arrays are
   incomplete-array externs.  Strides 0x48 ((i*8+i)*8) and 0x18 ((i*2+i)*8). */

void EventTriggerSysSetGameData_3e3c30(u8 *p)
{
    s32 i;

    D_00483990 = p;
    D_00483994 = 0;
    if (p != 0) {
        D_00483994 = *(s32 *)(p + 0x8);
    }
    D_00483998 = 1;
    D_0048399C = 0;
    D_004801F4 = -1;
    ActionPacketClear_3e3e90(D_004E9740);
    D_004839A0 = 0;
    D_004839A4 = 0;
    D_004839A8 = 0;
    for (i = 0; i < 2; i++) {
        SkillActionReset_3e3dd0(D_004E9770 + i * 0x48);
    }
    for (i = 0; i < 0x40; i++) {
        SkillTimerReset_3e3d20(D_004E9800 + i * 0x18);
    }
    D_004839AC = 0;
    D_004839B0 = 0;
    D_004839B4 = 0;
}
