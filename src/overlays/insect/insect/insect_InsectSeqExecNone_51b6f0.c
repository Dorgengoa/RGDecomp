#include "types.h"
/* insect 0x0051B6F0 -- 32 bytes.  `sltu $2, $0, $2` on the callee's result is
 * the `!= 0` normalisation, i.e. the return is a boolean. */
extern s32 func_31A8D0(void);

s32 insect_InsectSeqExecNone_51b6f0(void)
{
    return func_31A8D0() != 0;
}
