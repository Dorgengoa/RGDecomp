#include "types.h"
/* the view has one parameter; the native provider takes (dst, src) through an
   array typedef: retail passes its own $a1 as the source */
extern void FixCopyVector_13c480(void *);

void FixCopyUser_13c4e0(void *dst, void *src)
{
    FixCopyVector_13c480(dst);
}
