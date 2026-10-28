/* tests/protos fixture: an override (C port of an asm-bodied game file) is the
 * provider of its symbol; it returns $f0 (float). */
#include "types.h"

f32 VecLen_1cb3c0(void *v)
{
    return ((f32 *)v)[0] * 2.0f;
}
