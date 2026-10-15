#include "types.h"

/* retail FALLS THROUGH into the body of both guards, so both are written
   as positive `if`s, not early returns.  retail HAS the madd.s
   contraction, so the products stay inline (no named product local). */

extern f32 D_0047DAF0;
extern void *GetEventObjMgr_2d1960(f32 *);
extern s32 EventObjMgrPosClearOfVolumesMaybe_2e8b60(void *, f32 *, f32);
extern s32 EventObjMgrFindNearestTargetPointMaybe_2e89e0(void *, f32 *, f32 *);
extern f32 RandRangeFloat_1ca5d0(f32);
extern f32 Sinf_128fd0(f32);
extern f32 Cosf_128d30(f32);

void EventObjMgrMovePosOutOfVolumesMaybe_2d0740(f32 *p, f32 ang)
{
    void *h;
    f32 t;
    f32 s;

    h = GetEventObjMgr_2d1960(p);
    if (EventObjMgrPosClearOfVolumesMaybe_2e8b60(h, p, ang) == 0) {
        if (EventObjMgrFindNearestTargetPointMaybe_2e89e0(h, p, p) != 0) {
            t = D_0047DAF0 * (RandRangeFloat_1ca5d0(1.0f) - 0.5f);
            s = 1.0f + RandRangeFloat_1ca5d0(1.0f);
            p[0] = p[0] + s * Sinf_128fd0(t);
            p[2] = p[2] + s * Cosf_128d30(t);
        }
    }
}
