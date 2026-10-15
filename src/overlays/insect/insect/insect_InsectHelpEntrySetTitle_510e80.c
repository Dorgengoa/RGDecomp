#include "types.h"
/* insect 0x00510E80 -- 72 B / 18 words.  Branch-free; a SUBSTITUTION off the
 * already-matching insect_InsectHelpEntrySetPageImage_510dc0.c with the leading func_134BB0 probe
 * dropped, the allocator key 3 instead of 1 and the slot at +0x00 instead of
 * +0x0C.  As there, the func_14D950 result is held in a LOCAL and handed
 * straight to func_134A98 (`daddu $4, $2, $0` off the return register, no
 * reload through the object). */
typedef struct WObj { s32 f00; } WObj;

extern s32 func_14D950(void *b, s32 k);
extern void func_134A98(s32 t, void *c);

void insect_InsectHelpEntrySetTitle_510e80(WObj *a, void *b, void *c)
{
    s32 t;

    t = func_14D950(b, 3);
    a->f00 = t;
    func_134A98(t, c);
}
