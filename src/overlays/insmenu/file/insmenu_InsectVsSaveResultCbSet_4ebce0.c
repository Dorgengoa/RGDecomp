#include "types.h"

/* insmenu 0x004EBCE0 (172 bytes) -- pick the frame handler for the scene the
 * lookup names and park it in the gp hook.
 *
 * ★ `lui $3, 0x37 / addiu $3, $3, 0x3C80` is a %hi/%lo pair on an unsymbolised
 * MAIN-image code address, i.e. `&function`.  A cast integer would compile to
 * lui + ORI instead.
 * ★ The compare chain is 3, 1, 2 and the blocks land 2, 1, 3, default -- the
 * chain order is the source order. */

typedef void (*Handler)(void);

extern Handler D_0047FAA4;      /* gp - 0x56CC */

extern void insmenu_InsectVsSaveKindLookup_4ebd90(s16 *a, s16 *b);
extern void insmenu_InsectVsGetSaveCtx_4f3850(void);
extern void func_373B40(void);
extern void func_373C60(void);
extern void func_373C80(void);
extern void func_373E10(void);

void insmenu_InsectVsSaveResultCbSet_4ebce0(void)
{
    s16 kind;
    s16 y;

    insmenu_InsectVsSaveKindLookup_4ebd90(&kind, &y);
    switch (kind) {
    case 2:
        insmenu_InsectVsGetSaveCtx_4f3850();
        D_0047FAA4 = func_373C80;
        break;
    case 1:
        insmenu_InsectVsGetSaveCtx_4f3850();
        D_0047FAA4 = func_373C60;
        break;
    case 3:
        insmenu_InsectVsGetSaveCtx_4f3850();
        D_0047FAA4 = func_373B40;
        break;
    default:
        insmenu_InsectVsGetSaveCtx_4f3850();
        D_0047FAA4 = func_373E10;
        break;
    }
}
