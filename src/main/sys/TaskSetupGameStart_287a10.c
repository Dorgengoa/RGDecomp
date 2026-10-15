#include "types.h"

extern void TaskSetAllEnabled_27c290(s32);
extern void TaskSetEnabled_27c2a0(s32, void *);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

extern u8 D_0045FEC0[];
extern u8 D_0045FEE0[];
extern u8 D_0045FEF0[];
extern u8 D_0045FF00[];
extern u8 D_0045FF10[];
extern u8 D_0045FF20[];
extern u8 D_0045FF30[];
extern u8 D_0045FF50[];
extern u8 D_004600E8[];
extern u8 D_004600F8[];
extern u8 D_00460108[];
extern u8 D_00460168[];
extern u8 D_00460188[];
extern u8 D_00460198[];
extern u8 D_004601B8[];
extern u8 D_004602D8[];
extern u8 D_00460578[];
extern u8 D_00460588[];
extern u8 D_004605E8[];
extern u8 D_004605F8[];
extern u8 D_00460608[];
extern u8 D_00460C48[];

void TaskSetupGameStart_287a10(void)
{
    TaskSetAllEnabled_27c290(0);
    TaskSetEnabled_27c2a0(1, D_00460588);
    TaskSetEnabled_27c2a0(1, D_0045FEC0);
    TaskSetEnabled_27c2a0(1, D_004605E8);
    TaskSetEnabled_27c2a0(1, D_004605F8);
    TaskSetEnabled_27c2a0(1, D_00460578);
    TaskSetEnabled_27c2a0(1, D_0045FF20);
    TaskSetEnabled_27c2a0(1, D_0045FEF0);
    TaskSetEnabled_27c2a0(1, D_0045FF00);
    TaskSetEnabled_27c2a0(1, D_0045FF30);
    TaskSetEnabled_27c2a0(1, D_0045FF50);
    TaskSetEnabled_27c2a0(1, D_0045FF10);
    TaskSetEnabled_27c2a0(1, D_0045FEE0);
    TaskSetEnabled_27c2a0(1, D_00460608);
    TaskSetEnabled_27c2a0(1, D_004600E8);
    TaskSetEnabled_27c2a0(1, D_004600F8);
    TaskSetEnabled_27c2a0(1, D_00460108);
    TaskSetEnabled_27c2a0(1, D_00460168);
    TaskSetEnabled_27c2a0(1, D_00460188);
    TaskSetEnabled_27c2a0(1, D_00460198);
    TaskSetEnabled_27c2a0(1, D_004601B8);
    TaskSetEnabled_27c2a0(1, D_004602D8);
    TaskSetEnabled_27c2a0(1, D_00460C48);
}
