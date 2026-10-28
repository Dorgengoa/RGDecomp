#include "types.h"
/* the callee reads two arguments, the caller passes one: $a1 still holds q */
extern void MatFromQuat_13c440(void *);

void MatFromQuatFull_13c4c0(void *dst, void *q)
{
    MatFromQuat_13c440(dst);
}
