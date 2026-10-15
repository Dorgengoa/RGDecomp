#include "types.h"

extern void TaskEnableBaseSet_287870(void);
extern void TaskSetEnabled_27c2a0(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045FEB0[];
extern u8 D_0045FF98[];
extern u8 D_0045FFA8[];
extern u8 D_0045FFB8[];
extern u8 D_0045FFE0[];
extern u8 D_0045FFF0[];
extern u8 D_00460028[];
extern u8 D_00460038[];
extern u8 D_004600E8[];
extern u8 D_004600F8[];
extern u8 D_00460108[];
extern u8 D_00460148[];
extern u8 D_00460158[];
extern u8 D_00460168[];
extern u8 D_00460178[];
extern u8 D_00460188[];
extern u8 D_00460198[];
extern u8 D_004601B8[];
extern u8 D_00460210[];
extern u8 D_00460268[];
extern u8 D_00460280[];
extern u8 D_004602A0[];
extern u8 D_004602D8[];
extern u8 D_00460368[];
extern u8 D_00460568[];
extern u8 D_00460740[];
extern u8 D_00460850[];
extern u8 D_00460940[];

void TaskEnableCharaInteractSetMaybe_286d40(void)
{
    TaskEnableBaseSet_287870();
    TaskSetEnabled_27c2a0(1, D_00460568);
    TaskSetEnabled_27c2a0(1, D_0045FEB0);
    TaskSetEnabled_27c2a0(1, D_0045FFE0);
    TaskSetEnabled_27c2a0(1, D_0045FFF0);
    TaskSetEnabled_27c2a0(1, D_0045FF98);
    TaskSetEnabled_27c2a0(1, D_0045FFB8);
    TaskSetEnabled_27c2a0(1, D_00460268);
    TaskSetEnabled_27c2a0(1, D_00460280);
    TaskSetEnabled_27c2a0(1, D_004602A0);
    TaskSetEnabled_27c2a0(1, D_00460148);
    TaskSetEnabled_27c2a0(1, D_00460158);
    TaskSetEnabled_27c2a0(1, D_00460178);
    TaskSetEnabled_27c2a0(1, D_0045FFA8);
    TaskSetEnabled_27c2a0(1, D_00460568);
    TaskSetEnabled_27c2a0(1, D_00460940);
    TaskSetEnabled_27c2a0(1, D_00460028);
    TaskSetEnabled_27c2a0(1, D_00460038);
    TaskSetEnabled_27c2a0(1, D_00460210);
    TaskSetEnabled_27c2a0(1, D_00460108);
    TaskSetEnabled_27c2a0(1, D_004600F8);
    TaskSetEnabled_27c2a0(1, D_00460168);
    TaskSetEnabled_27c2a0(1, D_00460178);
    TaskSetEnabled_27c2a0(1, D_004601B8);
    TaskSetEnabled_27c2a0(0, D_00460368);
    TaskSetEnabled_27c2a0(0, D_004602D8);
    TaskSetEnabled_27c2a0(0, D_00460850);
    TaskSetEnabled_27c2a0(1, D_004600E8);
    TaskSetEnabled_27c2a0(1, D_00460188);
    TaskSetEnabled_27c2a0(1, D_00460198);
    TaskSetEnabled_27c2a0(1, D_00460740);
}
