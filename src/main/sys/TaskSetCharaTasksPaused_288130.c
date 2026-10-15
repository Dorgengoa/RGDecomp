#include "types.h"

/* The first callee of TaskSetUpdateTasksPaused_287dd0 and the same registration LIST shape:
   the u8 flag is rebuilt from the parameter with retail's
   `sltu $2,$0,$4 / xori $2,$2,1 / andi $16,$2,0xFF`, which is an inequality
   negated in one expression, then handed to 14 phase-name registrations. */

extern s32 TaskSetEnabled_27c2a0(s32, void *);

extern u8 D_00460080[];
extern u8 D_004600A0[];
extern u8 D_004600B8[];
extern u8 D_004600C8[];
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

void TaskSetCharaTasksPaused_288130(s32 mode)
{
    u8 f;

    f = !(mode != 0);
    TaskSetEnabled_27c2a0(f, D_00460080);
    TaskSetEnabled_27c2a0(f, D_004600A0);
    TaskSetEnabled_27c2a0(f, D_004600E8);
    TaskSetEnabled_27c2a0(f, D_00460188);
    TaskSetEnabled_27c2a0(f, D_00460198);
    TaskSetEnabled_27c2a0(f, D_004600B8);
    TaskSetEnabled_27c2a0(f, D_004600C8);
    TaskSetEnabled_27c2a0(f, D_004600F8);
    TaskSetEnabled_27c2a0(f, D_00460108);
    TaskSetEnabled_27c2a0(f, D_00460158);
    TaskSetEnabled_27c2a0(f, D_00460168);
    TaskSetEnabled_27c2a0(f, D_00460148);
    TaskSetEnabled_27c2a0(f, D_00460178);
    TaskSetEnabled_27c2a0(f, D_004601B8);
}
