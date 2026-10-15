#include "types.h"

typedef struct E321d60 {
    u8  pad00[0xF0];
    f32 fF0;
    u8  padF4[0x1B0 - 0xF4];
} E321d60;

typedef struct T321d60 {
    u8  pad000[0x518];
    f32 f518;
    f32 f51C;
} T321d60;

extern s32 MinimapSlotIsActive_322510(E321d60 *);

void MinimapMgrFadeStep_321d60(T321d60 *self)
{
    E321d60 *e;
    s32 i;

    if (self->f51C) {
        self->f518 = self->f518 + self->f51C;
        if (self->f51C < 0.0f) {
            if (self->f518 <= 0.0f) {
                self->f518 = 0.0f;
                self->f51C = 0.0f;
            }
        }
        if (self->f51C > 0.0f) {
            if (self->f518 >= 1.0f) {
                self->f518 = 1.0f;
                self->f51C = 0.0f;
            }
        }
        for (i = 0; i < 3; i++) {
            e = (E321d60 *)((u8 *)self + i * 432);
            if (MinimapSlotIsActive_322510(e) != 0) {
                e->fF0 = self->f518;
            }
        }
    }
}
