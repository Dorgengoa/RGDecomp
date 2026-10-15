#include "types.h"
/* normal 0x00524220 -- clamp the index to [0,6] and hand index+10 to the
 * lookup; the duplicated `addiu $5,$4,0xA` is the branch-likely delay-slot
 * copy of the shared tail, not a second statement. */

extern void *D_004849B4;          /* gp - 0x7BC */

extern void *func_28AA30(void *w, s32 id);
extern void  func_12DF00(void *p);

void normal_InsectEntryGetFee_524220(s32 n)
{
    if (n < 0) {
        n = 0;
    } else if (n >= 6) {
        n = 6;
    }
    func_12DF00(func_28AA30(D_004849B4, n + 10));
}
