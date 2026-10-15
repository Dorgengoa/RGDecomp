#include "types.h"

/* Hub function: called from many already-merged src/ files (src/p19d/*,
   src/bodies2/*) as a "find value by u16 key" helper -- their extern
   declarations pin the signature as (s32, s32) returning a pointer. */

struct N290460 {
    void *f0;
    u8 pad4[4];
    struct N290460 *f8;
};

struct Head290460 {
    struct N290460 *f0;
};

void *UiFindWidget_290460(struct Head290460 *head, s32 arg1)
{
    struct N290460 *cur;
    u16 key;
    void *val;

    cur = head->f0;
    if (cur == 0) {
        return 0;
    }
    key = (u16)arg1;
    while (cur != 0) {
        val = cur->f0;
        if (val != 0) {
            if (*(u16 *)val == key) {
                return val;
            }
        } else {
            return 0;
        }
        cur = cur->f8;
    }
    return 0;
}
