#include "types.h"
#include "vec.h"
#include "camera.h"

/* Advance a fade clock by dt/30 and stop the fade once it reaches its limit.
   Both guards compare against a float zero built with `mtc1 $0` rather than
   loaded, and 30.0f is materialised with `lui 0x41F0; mtc1` -- neither
   constant costs a .rodata word, which is what keeps this unit admissible to
   the link.

   The 30 is the game's design frame rate: `dt` here is the fixed 1/30 the
   animation timestep note records, so `dt / 30.0f` is a per-frame fraction of
   a second's worth of fade. */

void CameraShakeTimerStep_305860(Camera *self, f32 dt)
{
    f32 zero;

    zero = 0.0f;
    if (self->fadeRate == zero) {
        return;
    }
    self->fadeClock = self->fadeClock + dt / 30.0f;
    if (self->fadeLimit == zero) {
        return;
    }
    if (self->fadeLimit <= self->fadeClock) {
        self->fadeRate = 0.0f;
    }
}
