#include "types.h"

/* insmenu 0x004EB120 (100 bytes, 25 instructions, 2 calls) -- the same row
 * push as insmenu_InsectVsSaveConfirmMoveCb_4f6ed0 with the widget taken as a parameter and a
 * different field id.  Same negated-inequality bool for the last argument.
 */

typedef struct Row Row;
struct Row {
    u8 pad00[0x10];
    s16 field010;
};

extern void func_28F930(const void *a, s32 b, s32 c, s32 d);

s32 insmenu_InsectVsYesNoCursorMoveCb_4eb120(Row *o, const void *w)
{
    u8 b;

    func_28F930(w, 8, 0x7A, o->field010);
    b = !(o->field010 != 0);
    func_28F930(w, 8, 0x46, b);
    return 1;
}
