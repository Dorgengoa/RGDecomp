#include "types.h"
/* insmenu 0x004F3330 -- `j insmenu_InsectVsMenuResPoll_4f3370` with a `nop` slot: an
 * argument-free tail call. */
extern s32 insmenu_InsectVsMenuResPoll_4f3370(void);
s32 insmenu_InsectVsMenuResReady_4f3330(void) { return insmenu_InsectVsMenuResPoll_4f3370(); }
