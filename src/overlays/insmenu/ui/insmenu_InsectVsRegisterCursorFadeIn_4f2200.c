#include "types.h"
/* insmenu 0x004F2200 -- guarded five-argument call.
 * `bnel $2, $0, <epilogue>` carrying `ld $31` in its delay slot: the
 * guard exits to the shared epilogue, so the BODY is the == 0 arm.
 * $f12/$f13/$f14 are three separate float arguments; the literals are
 * inline (lui) while D_0047D34C is a gp float-pool global
 * (lwc1 off $28) and so is NOT const. */
extern s32 insmenu_InsectVsRegisterCursorIsOpaque_4f2150(void);
extern const u8 D_004FA180[];
extern f32 D_0047D34C;
extern void func_290690(const void *a, s32 b, f32 x, f32 y, f32 z);
void insmenu_InsectVsRegisterCursorFadeIn_4f2200(void)
{
    if (insmenu_InsectVsRegisterCursorIsOpaque_4f2150() == 0) {
        func_290690(D_004FA180, 0x18, 1.0f, D_0047D34C, -1.0f);
    }
}
