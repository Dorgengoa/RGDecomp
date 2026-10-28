/* rgp:protos */
#define RGP_SELF_normal_MenuBattleEndItemRowsCountUpdateMaybe_4eb150 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004EB150 -- the four normal_D_00527000 slots: when a slot is armed and its
 * 0xBA counter has run past 2, kick the 3*i+4 / 3*i+5 widgets and nudge the
 * func_290460 record's two s16s with clamps. */

typedef struct Eb1Slot {    /* 0x10 */
    f32 f00;
    f32 f04;
    f32 f08;
    s16 f0C;
    s16 f0E;
} Eb1Slot;

typedef struct Eb1Obj {
    u8      pad000[0x14];
    u8      f014[0xAC - 0x14];
    Eb1Slot f0AC[4];
} Eb1Obj;

typedef struct Eb1Rec {
    s16 f00;
    s16 f02;
    s16 f04;
} Eb1Rec;

typedef struct Eb1Box {
    u8      pad000[0x20];
    Eb1Rec *f20;
} Eb1Box;

extern s32 normal_D_00527000[];

/*rgp*/
/*rgp*/
/*rgp*/

void normal_MenuBattleEndItemRowsCountUpdateMaybe_4eb150(Eb1Obj *p)
{
    s32 i;
    s32 base;
    s32 id;
    Eb1Rec *r;

    for (i = 0; i < 4; i++) {
        if (normal_D_00527000[i] > 0 || normal_D_00527000[i] == -0xFF) {
            if (p->f0AC[i].f0C == 2 && p->f0AC[i].f0E > 2) {
                base = i * 3;
                UiFadeWidgetAlpha_290690(p->f014, base + 4, 1.0f, 0.06666667f, -1.0f);
                id = base + 5;
                UiSetWidgetsVisibleById_291110(p->f014, id, 1, 1);
                r = ((Eb1Box *)UiFindWidget_290460(p->f014, id))->f20;
                r->f00 = r->f00 - 15;
                if (r->f00 < -0xEF) {
                    r->f00 = -0xF0;
                }
                r->f04 = r->f04 + 30;
                if (r->f04 > 0xFC) {
                    r->f04 = 0xFC;
                }
            }
        }
    }
}
