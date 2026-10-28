/* rgp:protos */
#define RGP_SELF_normal_FieldHudAttackChainHide_4f6ab0 1
#include "port/game_protos.h"
#line 1
#include "types.h"
/* normal 0x004F6AB0 -- the store is through the PARAMETER, before it is copied
 * to the callee-saved register, so it is the first statement. */
typedef struct Obj {
    u8  pad000[0x14];
    u8  f014;
    u8  pad015[0x28 - 0x15];
    u8  f028;
    u8  pad029[0x3DC - 0x29];
    s16 f3DC;
} Obj;

/*rgp*/
/*rgp*/

void normal_FieldHudAttackChainHide_4f6ab0(Obj *p)
{
    p->f3DC = 0;
    BattleSparkBurstReset_382fc0(&p->f028);
    UiSetWidgetVisible_290010(&p->f014, 1, 0, -1);
    UiSetWidgetVisible_290010(&p->f014, 2, 0, -1);
    UiSetWidgetVisible_290010(&p->f014, 3, 0, -1);
    UiSetWidgetVisible_290010(&p->f014, 4, 0, -1);
}
