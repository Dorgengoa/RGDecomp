#include "types.h"

extern void InfoCfgParseThunk_1ac1e0(void);
extern void ParamScriptParse_1afb30(s32, s32);

/* Decoded by the pass-11 symbolic executor (build/w1_gen11.py):
   stores in listing order, return value read off $v0 at the jr,
   field types by ACCESS WIDTH.  The BUILD arbitrates -- this unit
   is here because its bytes are retail's bytes. */

void InfoCfgParseAll_1afd00(s32 p0, s32 p1)
{
    InfoCfgParseThunk_1ac1e0();
    ParamScriptParse_1afb30(p0, p1);
}
