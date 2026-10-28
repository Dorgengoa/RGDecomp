/* rgp:protos */
#define RGP_SELF_MenuCatalogListCursorCb_35c110 1
#define RGP_SELF_fmadd 1
#define RGP_SELF_fmul 1
#include "port/game_protos.h"
#line 1
/* PARK: adda.s/madd.s float accumulator resolved (29.0f + (f32)arg0->unk16 *
   D_00482388->unk1D0, re-reading arg0->unk16 instead of a cached local --
   fixed 21->7 bad words). Residual 7 bad words is pure register choice in
   the UiMoveWidgetUniform_290f50(6-arg) call tail: retail loads D_00482388 into $6 and
   schedules "addiu $6,0,0x173" last before the jal; ours uses $7 and
   schedules the "0" (5th arg) last instead -- an argument-evaluation-order
   artifact, not a value/shape bug. Not resolved in 3 round trips. */
#include "types.h"

typedef struct {
    u8 pad0[0x12];
    s16 unk12;
    u8 pad14[0x16 - 0x14];
    s16 unk16;
} Obj0035c110;

typedef struct {
    u8 pad0[0x1D0];
    f32 unk1D0;
    u8 pad1D4[0x274 - 0x1D4];
    s32 unk274;
    u8 pad278[0x288 - 0x278];
    s32 unk288;
    s32 unk28C;
} Obj00482388;

/*rgp*/
/*rgp*/
/*rgp*/
extern Obj00482388 *D_00482388;
extern s8 D_00482FEC;
extern s16 D_00482FF0;

static inline f32 fmul(f32 a, f32 b) { return a * b; }
static inline f32 fmadd(f32 c, f32 a, f32 b) { return c + a * b; }
s32 MenuCatalogListCursorCb_35c110(Obj0035c110 *arg0)
{
    s16 temp_3;
    s16 temp_3_2;

    temp_3 = arg0->unk12;
    if (temp_3 != D_00482388->unk288) {
        D_00482388->unk288 = temp_3;
        MenuCatalogPlaceRowCursor_360350(D_00482388);
        D_00482FEC = 0;
        D_00482FF0 = 0;
    }
    temp_3_2 = arg0->unk16;
    if (temp_3_2 != D_00482388->unk28C) {
        D_00482388->unk28C = temp_3_2;
        MenuCatalogListRefresh_3602e0(D_00482388);
        UiMoveWidgetUniform_290f50(D_00482388->unk274, 0x1F8, 0x173, (s32) (29.0f + fmul((f32) arg0->unk16, *(volatile f32 *)&D_00482388->unk1D0)), 0.25f, 0
);
        D_00482FEC = 0;
        D_00482FF0 = 0;
    }
    return 1;
}
