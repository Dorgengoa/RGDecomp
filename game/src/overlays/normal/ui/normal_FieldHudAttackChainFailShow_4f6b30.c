/* rgp:protos */
#define RGP_SELF_normal_FieldHudAttackChainFailShow_4f6b30 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F6B30 -- straight-line: two four-argument calls on the same
 * sub-object address, then two stores.  The FIRST unit compiled from C in the
 * NORMAL overlay.
 *
 * `&p->f14` is re-materialised at both call sites in the reference
 * (`addiu $4, $16, 0x14` twice) rather than cached, so it is written inline at
 * each call and the base stays in the callee-saved register. */
typedef struct Obj {
    u8  pad00[0x14];
    u8  f14;
    u8  pad15[0x3DC - 0x15];
    s16 f3DC;
    s32 f3E0;
} Obj;

/*rgp*/
/*rgp*/

void normal_FieldHudAttackChainFailShow_4f6b30(Obj *p)
{
    UiSetWidgetVisible_290010(&p->f14, 3, 1, -1);
    UiSetWidgetPos_290f60(&p->f14, 3, -0x23, -0x60);
    p->f3E0 = 0;
    p->f3DC = 0x16;
}
