#include "types.h"

/* insmenu 0x004EE6B0 (84 bytes, 21 instructions, 4 calls) -- select the list
 * row and move the cursor widget onto it.  `func_28EC60` returns a record and
 * the two `lh`s off it are the row's x/y, read straight into the call's
 * argument registers.
 */

typedef struct Pos Pos;
struct Pos {
    s16 x;
    s16 y;
};

extern const u8 D_004FA180[];
extern const u8 D_004FA1A0[];

extern void func_28EA90(const void *a, s32 b, s32 c);
extern Pos *func_28EC60(const void *a);
extern void func_290F60(const void *a, s32 b, s32 c, s32 d);
extern void insmenu_InsectVsYesNoCursorFadeIn_4ee770(void);

void insmenu_InsectVsYesNoCursorPlace_4ee6b0(void)
{
    Pos *p;

    func_28EA90(D_004FA1A0, 0x7532, 1);
    p = func_28EC60(D_004FA1A0);
    func_290F60(D_004FA180, 9, p->x, p->y);
    insmenu_InsectVsYesNoCursorFadeIn_4ee770();
}
