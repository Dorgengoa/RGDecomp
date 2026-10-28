#include "types.h"
/* NORMAL is resident here: the overlay import binds to normal's definition */
extern s32 func_4EC000(const u8 *, f32, f32);

void FieldHudFadeIn_203ee0(u8 *hud)
{
    func_4EC000(hud, 1.0f, 10.0f);
}
