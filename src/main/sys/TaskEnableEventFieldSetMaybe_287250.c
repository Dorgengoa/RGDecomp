#include "types.h"

extern void TaskEnableFieldSet_2874a0(void);
extern void TaskSetEnabled_27c2a0(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045FED0[];
extern u8 D_0045FF78[];
extern u8 D_004600B8[];
extern u8 D_004600C8[];
extern u8 D_004600D8[];
extern u8 D_00460200[];
extern u8 D_00460210[];
extern u8 D_004602E8[];
extern u8 D_00460308[];
extern u8 D_00460320[];
extern u8 D_00460338[];
extern u8 D_004605C0[];
extern u8 D_004605D8[];
extern u8 D_00460760[];
extern u8 D_00460780[];
extern u8 D_00460850[];
extern u8 D_00460870[];
extern u8 D_00460970[];
extern u8 D_00460988[];
extern u8 D_00460998[];
extern u8 D_004609A8[];
extern u8 D_004609E8[];
extern u8 D_00460A38[];

void TaskEnableEventFieldSetMaybe_287250(void)
{
    TaskEnableFieldSet_2874a0();
    TaskSetEnabled_27c2a0(1, D_004600D8);
    TaskSetEnabled_27c2a0(1, D_004609E8);
    TaskSetEnabled_27c2a0(1, D_00460A38);
    TaskSetEnabled_27c2a0(1, D_00460308);
    TaskSetEnabled_27c2a0(1, D_004609A8);
    TaskSetEnabled_27c2a0(1, D_00460780);
    TaskSetEnabled_27c2a0(0, D_004605C0);
    TaskSetEnabled_27c2a0(0, D_004605D8);
    TaskSetEnabled_27c2a0(0, D_0045FED0);
    TaskSetEnabled_27c2a0(0, D_004600B8);
    TaskSetEnabled_27c2a0(0, D_004600C8);
    TaskSetEnabled_27c2a0(0, D_00460200);
    TaskSetEnabled_27c2a0(0, D_00460850);
    TaskSetEnabled_27c2a0(0, D_00460320);
    TaskSetEnabled_27c2a0(0, D_00460970);
    TaskSetEnabled_27c2a0(0, D_00460338);
    TaskSetEnabled_27c2a0(0, D_00460988);
    TaskSetEnabled_27c2a0(0, D_004602E8);
    TaskSetEnabled_27c2a0(0, D_00460998);
    TaskSetEnabled_27c2a0(0, D_00460210);
    TaskSetEnabled_27c2a0(0, D_00460760);
    TaskSetEnabled_27c2a0(0, D_004609A8);
    TaskSetEnabled_27c2a0(0, D_00460870);
    TaskSetEnabled_27c2a0(0, D_0045FF78);
}
