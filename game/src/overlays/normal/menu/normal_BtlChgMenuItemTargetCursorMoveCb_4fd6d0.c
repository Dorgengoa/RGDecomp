/* rgp:protos */
#define RGP_SELF_normal_BtlChgMenuItemTargetCursorMoveCb_4fd6d0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004FD6D0 -- normal_D_00525100 is OVERLAY data (0x00525100, far outside the
 * gp window at _gp 0x00485170), so it must be `const` to take %hi/%lo.  The
 * 8-byte element stride is what produces `sll $6, $4, 3`. */
typedef struct Ent { void *f0; s32 f4; } Ent;
typedef struct Obj { u8 pad00[0x10]; s16 f10; } Obj;

extern Ent normal_D_00525100[];
extern s32 normal_D_00525104;
extern void *D_0048449C;
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

s32 normal_BtlChgMenuItemTargetCursorMoveCb_4fd6d0(Obj *p)
{
    UiMoveWidgetUniform_290f50(D_0048449C, 0x2A, normal_D_00525100[p->f10].f0, normal_D_00525104 + 6, 0.5f, 0);
    GetCurrentScene_1f5be0();
    SoundPlayScaledVolume_1b9520(SceneSoundGetSlot0HandleCur_207df0(), 4, 0, 1.0f);
    return 1;
}
