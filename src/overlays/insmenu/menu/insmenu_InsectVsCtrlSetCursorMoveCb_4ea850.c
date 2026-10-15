#include "types.h"

/* insmenu 0x004EA850 (132 bytes, 33 instructions, 5 calls) -- publish one
 * row's measured extent and its computed total.  `mult $7, $3, $2` is the
 * product written straight into the call's argument register.
 */

typedef struct Row Row;
struct Row {
    u8 pad00[0x6];
    s16 field006;
    u8 pad008[0xA];
    s16 field012;
};

typedef struct Handle Handle;
struct Handle {
    u8 pad00[0x24];
    void *field024;
};

extern const u8 D_004FA180[];

extern void func_28ED30(Row *o, s32 *a, s32 *b);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern Handle *func_1FEDE0(void);
extern void func_430BD0(void *a, s32 b);

s32 insmenu_InsectVsCtrlSetCursorMoveCb_4ea850(Row *o, const void *w)
{
    s32 sp3C;
    s32 sp38;

    func_28ED30(o, &sp3C, &sp38);
    func_290F60(w, 0xE, sp3C, sp38);
    func_290F60(D_004FA180, 0xB, 0, o->field012 * o->field006);
    func_430BD0(func_1FEDE0()->field024, o->field012);
    return 1;
}
