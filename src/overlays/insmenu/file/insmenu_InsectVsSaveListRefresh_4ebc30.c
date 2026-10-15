#include "types.h"

/* insmenu 0x004EBC30 (172 bytes) -- dispatch on the second value the scene
 * lookup returns.
 *
 * ★ The compare chain runs 4, 3, 2, 1 while the blocks are laid out 1, 2, 3, 4:
 * the source is an if/else-if chain in the COMPARE order and mwcc lays the arms
 * out reversed.
 * ★ Each `beql` carries `daddu $4, $16, $0` in its delay slot -- one argument
 * setup duplicated into every likely slot, not four separate stores. */

extern void insmenu_InsectVsSaveKindLookup_4ebd90(s16 *a, s16 *b);
extern void func_3783C0(s32 a, s32 b);
extern void func_37A2B0(s32 a);
extern void func_37AB70(s32 a);
extern void func_377AE0(s32 a);

void insmenu_InsectVsSaveListRefresh_4ebc30(s32 a, s32 b)
{
    s16 kind;
    s16 x;

    insmenu_InsectVsSaveKindLookup_4ebd90(&x, &kind);
    switch (kind) {
    case 1:
        func_377AE0(a);
        break;
    case 2:
        func_37AB70(a);
        break;
    case 3:
        func_37A2B0(a);
        break;
    case 4:
        func_3783C0(a, b);
        break;
    }
}
