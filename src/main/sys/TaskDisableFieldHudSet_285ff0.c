#include "types.h"

extern void TaskSetEnabled_27c2a0(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045FED0[];
extern u8 D_004600B8[];
extern u8 D_004600C8[];
extern u8 D_00460230[];
extern u8 D_004602E8[];
extern u8 D_004602F8[];
extern u8 D_00460308[];
extern u8 D_00460320[];
extern u8 D_00460338[];
extern u8 D_00460390[];
extern u8 D_004603D0[];
extern u8 D_00460850[];
extern u8 D_00460870[];
extern u8 D_00460970[];
extern u8 D_00460988[];
extern u8 D_00460998[];
extern u8 D_004609A8[];
extern u8 D_00460A48[];
extern u8 D_00460A60[];
extern u8 D_00460AB0[];

void TaskDisableFieldHudSet_285ff0(void)
{
    TaskSetEnabled_27c2a0(0, D_004600B8);
    TaskSetEnabled_27c2a0(0, D_004600C8);
    TaskSetEnabled_27c2a0(0, D_00460850);
    TaskSetEnabled_27c2a0(0, D_00460320);
    TaskSetEnabled_27c2a0(0, D_00460970);
    TaskSetEnabled_27c2a0(0, D_00460338);
    TaskSetEnabled_27c2a0(0, D_00460988);
    TaskSetEnabled_27c2a0(0, D_004602E8);
    TaskSetEnabled_27c2a0(0, D_00460998);
    TaskSetEnabled_27c2a0(0, D_004602F8);
    TaskSetEnabled_27c2a0(0, D_00460A48);
    TaskSetEnabled_27c2a0(0, D_00460308);
    TaskSetEnabled_27c2a0(0, D_004609A8);
    TaskSetEnabled_27c2a0(0, D_00460870);
    TaskSetEnabled_27c2a0(0, D_004603D0);
    TaskSetEnabled_27c2a0(0, D_00460AB0);
    TaskSetEnabled_27c2a0(0, D_00460390);
    TaskSetEnabled_27c2a0(0, D_00460A60);
    TaskSetEnabled_27c2a0(0, D_0045FED0);
    TaskSetEnabled_27c2a0(0, D_00460230);
}
