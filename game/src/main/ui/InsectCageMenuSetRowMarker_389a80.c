/* rgp:protos */
#define RGP_SELF_InsectCageMenuSetRowMarker_389a80 1
#include "port/game_protos.h"
#line 1
#include "types.h"

/*rgp*/                   /* extern */
/*rgp*/                   /* extern */
/*rgp*/                 /* extern */
/*rgp*/             /* extern */
extern s32 D_00483308;

void * InsectCageMenuSetRowMarker_389a80(s32 arg0, s32 arg1, s32 arg2, s32 arg3) { void * rgp_v0 = 0;
    s32 sp7C;
    s32 sp78;
    s32 temp_17;
    s32 temp_21;
    s32 temp_6;
    s32 var_16;
    s32 var_17;

    temp_17 = (arg0 + 0x7577) & 0xFFFF;
    var_16 = -1;
    temp_21 = (arg2 + 0x7580) & 0xFFFF;
    UiSetWidgetVisible_290010(D_00483308, temp_17, arg1, -1);
    if (arg1 != 0) {
        var_16 = arg3;
        InsectCageMenuGetMarkerPos_389b80(arg2, arg3, &sp7C, &sp78);
        temp_6 = sp7C + 0x1C;
        sp7C = temp_6;
        UiSetWidgetPos_290f60(D_00483308, temp_17, temp_6, sp78);
    }
    var_17 = 0;
    do {
        if (var_16 != var_17) {
            (rgp_v0 = UiSetSpriteW_28fbf0(D_00483308, temp_21, 0x94, var_17 + 4));
        } else {
            (rgp_v0 = UiSetSpriteW_28fbf0(D_00483308, temp_21, 1, var_17 + 4));
        }
        var_17 += 1;
    } while (var_17 < 5);
return rgp_v0; }
