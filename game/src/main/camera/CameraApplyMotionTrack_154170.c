/* rgp:protos */
#define RGP_SELF_CameraApplyMotionTrack_154170 1
#include "port/game_protos.h"
#line 1
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

/*rgp*/
/*rgp*/
/*rgp*/

s32 CameraApplyMotionTrack_154170(void *out, s32 id, void *owner, f32 t)
{
    Sample sample __attribute__((aligned(16)));
    Track *track;

    if (out == NULL) {
        return 0;
    }

    for (track = ((Track *)AnimResGetKeyListByType_14bf30(owner, 3)); track != NULL; track = track->next) {
        if (id == track->id) {
            AnimKeyEvalCamera_155830(&sample, track, t);
            CameraApplyAnimSample_154400(&sample, out);
            return 1;
        }
    }
    return 0;
}
