#include "types.h"

/* Find the keyframe track whose id matches, sample it at t, and install the
   result. Returns 1 if a track was found and applied, 0 otherwise -- so a
   caller that gets 0 leaves whatever was in *out alone. */

typedef struct Track {
    struct Track *next;  /* +0x00 */
    u16 id;              /* +0x04 */
} Track;

typedef struct Sample {
    u8 bytes[0x50];
} Sample;

extern Track *AnimResGetKeyListByType_14bf30(void *owner, s32 kind);
extern void AnimKeyEvalCamera_155830(Sample *out, Track *track, f32 t);
extern void CameraApplyAnimSample_154400(Sample *sample, void *out);

s32 CameraApplyMotionTrack_154170(void *out, s32 id, void *owner, f32 t)
{
    Sample sample;
    Track *track;

    if (out == NULL) {
        return 0;
    }

    for (track = AnimResGetKeyListByType_14bf30(owner, 3); track != NULL; track = track->next) {
        if (id == track->id) {
            AnimKeyEvalCamera_155830(&sample, track, t);
            CameraApplyAnimSample_154400(&sample, out);
            return 1;
        }
    }
    return 0;
}
