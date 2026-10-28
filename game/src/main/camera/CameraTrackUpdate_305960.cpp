#include "camera_cpp.h"

/* The town's camera driver -- camera mode 5.

   Evaluate the track's keyframe events onto the camera, then place the whole
   rig in the world. The rig's frame comes either from a live object the track
   is following, or from the track's own stored position and euler when there
   is no object: with an object, the heading is the atan2 of the object's
   forward vector after its own transform, taken relative to its position.

   The eye and look-at come out of the camera in RIG-LOCAL space, get rotated
   by the frame's euler and translated by its position, and go back in. The
   angle handed to ViewSetFov_142f10 is converted the other way from
   CameraApplyAnimSample_154400's: the vtable getter returns DEGREES and this wants radians,
   so it is PI * angle / 180. */

typedef struct Track {
    u8 pad000[0x180];
    Vec4 pos;         /* +0x180 */
    Vec4 euler;       /* +0x190 */
    u8 pad1a0[0x50];
    u8 events[0x4];   /* +0x1F0 */
} Track;

typedef struct SceneMgr {
    u8 pad0000[0x4344];
    s32 cameraId;     /* +0x4344 */
} SceneMgr;

typedef struct Follow {
    u8 pad00[0x4];
    void *node;       /* +0x04 */
} Follow;

/* PI itself, as the gp-relative constant the reference names -- a literal
   would be mwcc's own @N label and could never take the same relocation. */
extern "C" f32 D_0047D1FC;

extern "C" Track *ObjRecGetLiveObject_1c4a90(SceneMgr *mgr, s32 index);
extern "C" void *GetDrawCtx_15de80(void);
extern "C" Camera *ObjRecGetLiveObject_1c3bc0(SceneMgr *mgr, s32 id);
extern "C" s32 ModelObjGetMotionName_1add90(Track *track);
extern "C" s32 CameraApplyMotionList_171c40(void *events, s32 id, Camera *camera);
extern "C" void ViewSetFov_142f10(void *thing, f32 radians);
extern "C" Follow *ModelGetRootFrame_1511a0(Track *track);
extern "C" void FrameGetWorldPos_148f30(void *node, Vec4 *pos);
extern "C" void FrameTransformPoint_148f60(void *node, Vec4 *out, const Vec4 *v);
extern "C" void VecSub_13be40(Vec4 *out, const Vec4 *a, const Vec4 *b);   /* a - b */
extern "C" void VecAdd_13be20(Vec4 *out, const Vec4 *a, const Vec4 *b);   /* a + b */
extern "C" f32 Atan2f_1291a8(f32 y, f32 x);
extern "C" void sceVu0UnitMatrix(Mtx4 *m);
extern "C" void sceVu0RotMatrix(Mtx4 *out, Mtx4 *m, const Vec4 *euler);
extern "C" void MtxMulVec4_10a8c0(Vec4 *out, const Mtx4 *m, const Vec4 *v);

extern "C" s32 CameraTrackUpdate_305960(SceneMgr *mgr, s32 index)
{
    Track *track;
    void *thing;
    Camera *camera;
    void *node;
    /* Declaration order sets the frame offsets -- mwcc allocates locals in
       REVERSE order, so pos lands highest at sp+0xC0 and frame lowest. */
    Vec4 pos __attribute__((aligned(16)));
    Vec4 euler __attribute__((aligned(16)));
    Vec4 forward __attribute__((aligned(16)));
    Vec4 eye __attribute__((aligned(16)));
    Vec4 at __attribute__((aligned(16)));
    Mtx4 frame __attribute__((aligned(16)));

    track = ObjRecGetLiveObject_1c4a90(mgr, index);
    thing = GetDrawCtx_15de80();
    camera = ObjRecGetLiveObject_1c3bc0(mgr, mgr->cameraId);

    if (track == NULL) {
        return 0;
    }
    if (ModelObjGetMotionName_1add90(track) == 0) {
        return 0;
    }

    CameraApplyMotionList_171c40(track->events, 0, camera);
    ViewSetFov_142f10(thing, D_0047D1FC * camera->getAngle() / 180.0f);

    {
        Follow *follow = ModelGetRootFrame_1511a0(track);

        node = NULL;
        if (follow != NULL) {
            node = follow->node;
        }
    }

    if (node != NULL) {
        FrameGetWorldPos_148f30(node, &pos);
        pos.w = 0.0f;
        forward.x = 0.0f;
        forward.y = 0.0f;
        forward.z = 1.0f;
        FrameTransformPoint_148f60(node, &forward, &forward);
        VecSub_13be40(&forward, &forward, &pos);
        euler.x = 0.0f;
        euler.y = Atan2f_1291a8(forward.x, forward.z);
        euler.z = 0.0f;
        euler.w = 0.0f;
    } else {
        pos = track->pos;
        euler = track->euler;
    }

    camera->getEyeLocal(&eye);
    camera->getAtLocal(&at);

    sceVu0UnitMatrix(&frame);
    sceVu0RotMatrix(&frame, &frame, &euler);
    MtxMulVec4_10a8c0(&eye, &frame, &eye);
    MtxMulVec4_10a8c0(&at, &frame, &at);
    VecAdd_13be20(&eye, &eye, &pos);
    VecAdd_13be20(&at, &at, &pos);

    camera->setEye(&eye);
    camera->setAt(&at);
    camera->apply();
    camera->commit();
    return 1;
}
