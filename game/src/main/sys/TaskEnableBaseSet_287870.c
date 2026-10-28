/* rgp:protos */
#define RGP_SELF_TaskEnableBaseSet_287870 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/
/*rgp*/
/*rgp*/

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
extern u8 D_0045FF40[];
extern u8 D_0045FF50[];
extern u8 D_0045FFC8[];
extern u8 D_00460118[];
extern u8 D_00460578[];
extern u8 D_00460588[];
extern u8 D_00460598[];
extern u8 D_004605E8[];
extern u8 D_004605F8[];
extern u8 D_00460608[];
extern u8 D_00460620[];
extern u8 D_004609D8[];
extern u8 D_00460A20[];
extern u8 D_00460C58[];
extern u8 D_00460C88[];
extern u8 D_00460CE8[];

void TaskEnableBaseSet_287870(void)
{
    TaskSetAllEnabled_27c290(0);
    TaskSetRenderTasksEnabled_287b90(1);
    TaskSetEnabled_27c2a0(1, D_00460588);
    TaskSetEnabled_27c2a0(1, D_0045FEC0);
    TaskSetEnabled_27c2a0(1, D_004605E8);
    TaskSetEnabled_27c2a0(1, D_004605F8);
    TaskSetEnabled_27c2a0(1, D_00460578);
    TaskSetEnabled_27c2a0(1, D_0045FF20);
    TaskSetEnabled_27c2a0(1, D_0045FF00);
    TaskSetEnabled_27c2a0(1, D_0045FEF0);
    TaskSetEnabled_27c2a0(1, D_0045FF30);
    TaskSetEnabled_27c2a0(1, D_0045FF40);
    TaskSetEnabled_27c2a0(1, D_0045FF50);
    TaskSetEnabled_27c2a0(1, D_0045FF10);
    TaskSetEnabled_27c2a0(1, D_0045FEE0);
    TaskSetEnabled_27c2a0(1, D_0045FFC8);
    TaskSetEnabled_27c2a0(1, D_00460620);
    TaskSetEnabled_27c2a0(1, D_00460608);
    TaskSetEnabled_27c2a0(1, D_004609D8);
    TaskSetEnabled_27c2a0(1, D_00460CE8);
    TaskSetEnabled_27c2a0(1, D_00460A20);
    TaskSetEnabled_27c2a0(1, D_00460118);
    TaskSetEnabled_27c2a0(1, D_00460C88);
    TaskSetEnabled_27c2a0(1, D_00460598);
    TaskSetEnabled_27c2a0(1, D_00460C58);
}
