/* rg-override: replaces game/src/main/event/EventCameraCmdShake_254f90.c sha256 4574fab3c630e2c7d6f9863489028e1a65466f37036aa8479228636ec52c9b9d
 * why: accessibility.camera_shake (docs/SETTINGS.md "Accessibility"): records the offset this
 * event-camera shake step added to the eye / look-at (a host-side note, no game state
 * changed); TaskUpdateDrawInfo_2f6ff0 scales it out of the draw camera copy */
/* rgp:protos */
#define RGP_SELF_EventCameraCmdShake_254f90 1
#include "port/game_protos.h"
#line 1
#include "types.h"
extern void rg_event_shake_note(const void *eye, const void *eye0, const void *at, const void *at0);   /* rg_aspect.c */
#include "vec.h"

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

typedef struct {
    u8 pad0[0x10];
    Vec4 v10;
    u8 pad20[0x10];
    s32 count;
} Src;

typedef struct {
    u8 pad0[0x44];
    s32 idx;
    u8 pad48[0x8];
    Vec4 v50;
    Vec4 v60;
    u8 pad70[0x180 - 0x70];
    s32 active;
    u8 pad184[0xC];
    Vec4 v190;
    Vec4 v1A0;
    Vec4 v1B0;
} Dst;

s32 EventCameraCmdShake_254f90(Src *arg0, Dst *arg1)
{
    Vec4 sp30 __attribute__((aligned(16)));

    if (arg0->count <= -1) {
        arg1->active = 1;
        sceVu0CopyVector(&arg1->v1A0, &arg1->v50);
        sceVu0CopyVector(&arg1->v1B0, &arg1->v60);
        if (arg1->idx % 4 == 0) {
            VecAdd_13be20(&arg1->v50, &arg1->v50, &arg0->v10);
            VecAdd_13be20(&arg1->v60, &arg1->v60, &arg0->v10);
        } else if (arg1->idx % 4 == 2) {
            VecSub_13be40(&arg1->v50, &arg1->v50, &arg0->v10);
            VecSub_13be40(&arg1->v60, &arg1->v60, &arg0->v10);
        }
        arg1->idx++;
        rg_event_shake_note(&arg1->v50, &arg1->v1A0, &arg1->v60, &arg1->v1B0);
    } else {
        if (arg1->idx >= arg0->count) {
            arg1->idx = 0;
            arg1->active = 0;
            return 0;
        }
        if (arg1->idx <= 0) {
            arg1->active = 1;
            sceVu0CopyVector(&arg1->v190, &arg0->v10);
        }
        sceVu0CopyVector(&arg1->v1A0, &arg1->v50);
        sceVu0CopyVector(&arg1->v1B0, &arg1->v60);
        if (arg1->idx % 4 == 0) {
            VecAdd_13be20(&arg1->v50, &arg1->v50, &arg1->v190);
            VecAdd_13be20(&arg1->v60, &arg1->v60, &arg1->v190);
        } else if (arg1->idx % 4 == 2) {
            VecSub_13be40(&arg1->v50, &arg1->v50, &arg1->v190);
            VecSub_13be40(&arg1->v60, &arg1->v60, &arg1->v190);
            sceVu0DivVector(&sp30, &arg0->v10, (f32)arg0->count);
            VecScale_13be00(&sp30, &sp30, (f32)arg1->idx);
            VecSub_13be40(&arg1->v190, &arg0->v10, &sp30);
        }
        arg1->idx++;
        rg_event_shake_note(&arg1->v50, &arg1->v1A0, &arg1->v60, &arg1->v1B0);
    }
    return 1;
}
