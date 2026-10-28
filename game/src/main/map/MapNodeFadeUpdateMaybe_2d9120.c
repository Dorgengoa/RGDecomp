/* rgp:protos */
#define RGP_SELF_MapNodeFadeUpdateMaybe_2d9120 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/* Fade driver.  The two `beql`s jump INTO their arms, so the step selection is
   a compiled switch (source case order is the reverse of the compare chain:
   0 then 1).  `v` is read ONCE before the switch - retail duplicates that load
   into all three delay slots and only re-reads f->val after a store.
   D_0047D1D0 is a %gp_rel pool slot, so a plain extern. */

typedef struct Fade {
    u8 f0;                  /* 0x0 */
    u8 pad1[3];
    s32 mode;               /* 0x4 */
    f32 val;                /* 0x8 */
} Fade;

typedef struct Owner {
    u8 pad0[0x34];
    s32 f34;                /* 0x34 */
    s32 f38;                /* 0x38 */
} Owner;

typedef struct Slot {
    u8 pad0[0x32];
    s16 h32;                /* 0x32 */
    u8 pad34[0x30];
    f32 f64;                /* 0x64 */
} Slot;

extern f32 D_0047D1D0;
/*rgp*/
/*rgp*/

void MapNodeFadeUpdateMaybe_2d9120(Fade *f, s32 unused, Owner *o, s32 id)
{
    Slot *sl;

    if (f->f0 == 0) {
        if (o == 0) {
            return;
        }
        sl = ((Slot *)NodeObjFindChildByName_195040(o, id));
        if (sl != 0) {
            sl->f64 = 0.0f;
            sl->h32 = 0;
        }
    } else {
        /* compound assignment: each arm's own read of f->val is what the
           scheduler lifts into the three branch delay slots */
        switch (f->mode) {
        case 0:
            f->val += D_0047D1D0;
            break;
        case 1:
            f->val -= D_0047D1D0;
            break;
        }
        if (f->val < 0.0f) {
            f->val = 0.0f;
        }
        if (f->val > 1.0f) {
            f->val = 1.0f;
        }
        if (o != 0) {
            o->f34 = 0;
            o->f38 = 0;
            NodeSetTranslation_1866b0(o, (void *)unused);
            sl = ((Slot *)NodeObjFindChildByName_195040(o, id));
            if (sl != 0) {
                sl->f64 = f->val;
                sl->h32 = 1;
            }
        }
    }
}
