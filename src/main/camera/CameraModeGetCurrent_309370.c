#include "types.h"

/* The active camera-MODE record, as a signed byte read out of it. +0x268 is a
   byte offset from the camera to the record, and zero means there is no mode
   at all -- hence the -1 rather than a load. */
typedef struct Camera {
    u8 pad000[0x268];
    s32 modeOffset;   /* +0x268, 0 = no mode */
} Camera;

s32 CameraModeGetCurrent_309370(Camera *this)
{
    s32 offset = this->modeOffset;

    if (offset == 0) {
        return -1;
    }
    /* Integer arithmetic, offset first: pointer arithmetic canonicalises to
       `addu v0, a0, v0` and retail has `addu v0, v0, a0`. */
    return *(s8 *)(offset + (s32)this + 0x25F);
}
