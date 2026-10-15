#include "types.h"

extern void FieldHudWidget86Close_203fc0(void);
extern void FieldHudWidget81Close_204040(void);
extern void FieldHudWidget82Close_204020(void);
extern void FieldHudWidget7FClose_203f80(void);
extern void FieldHudWidget83Close_203ff0(void);
extern void FieldHudLogClose_203fa0(void);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void FieldHudCloseWidgets_288240(s32 p0)
{
    FieldHudWidget86Close_203fc0();
    FieldHudWidget81Close_204040();
    FieldHudWidget82Close_204020();
    FieldHudWidget7FClose_203f80();
    FieldHudWidget83Close_203ff0();
    if (p0 != 0) {
        FieldHudLogClose_203fa0();
    }
}
