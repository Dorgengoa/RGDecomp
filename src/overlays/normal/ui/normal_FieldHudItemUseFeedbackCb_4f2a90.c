#include "types.h"
/* normal 0x004F2A90 -- `j normal_FieldHudItemUseFeedback_4f2ab0 / daddu $5, $0, $0`, and its twin
 * normal_FieldHudItemUseFeedbackSeCb_4f2aa0 passes 1.  `$4` is never touched, so it is this function's own
 * parameter passed straight through; normal_FieldHudItemUseFeedback_4f2ab0 stores `$5` with `sb`, so
 * the flag is a byte.  One of the 55 unnamed functions. */
extern void normal_FieldHudItemUseFeedback_4f2ab0(void *p, u8 flag);

void normal_FieldHudItemUseFeedbackCb_4f2a90(void *p)
{
    normal_FieldHudItemUseFeedback_4f2ab0(p, 0);
}
