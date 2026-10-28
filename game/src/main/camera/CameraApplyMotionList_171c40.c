/* rgp:protos */
#define RGP_SELF_CameraApplyMotionList_171c40 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* The scripted camera-keyframe evaluator: walk the track's list of camera
   events, evaluate each one, and hand the live ones to CameraApplyMotion_171540. This is
   what installs the cinematic pose -- the writer the camera investigation
   spent a session naming.

   The `event == NULL` test is not dead code by accident: `event` is the
   address of a sub-object at +0x10 of a list node that is already known
   non-NULL, so it can never be null. It looks like an inlined C++ accessor
   whose result the compiler could not prove non-null, and retail emits the
   check, so it stays. */

typedef struct TrackNode {
    struct TrackNode *next;   /* +0x00 */
    u8 pad04[0xC];
    u8 event[0x10];           /* +0x10 */
} TrackNode;

typedef struct TrackList {
    u8 pad00[0x4];
    TrackNode *head;          /* +0x04 */
} TrackList;

typedef struct EventResult {
    s32 skip;    /* +0x00, non-zero = this event contributes nothing */
    u8 pad04[0x4];
    s32 which;   /* +0x08 */
    f32 t;       /* +0x0C */
    u8 pad10[0x10];
} EventResult;

/*rgp*/
/*rgp*/

s32 CameraApplyMotionList_171c40(TrackList *list, void *arg, void *camera)
{
    TrackNode *node;
    EventResult result __attribute__((aligned(16)));

    for (node = list->head; node != NULL; node = node->next) {
        void *event = node->event;

        if (event == NULL) {
            continue;
        }
        MotionPlayerGetBlendMaybe_172ce0(event, &result);
        if (result.skip == 0) {
            CameraApplyMotion_171540(arg, camera, result.which, result.t);
        }
    }
    return 1;
}
