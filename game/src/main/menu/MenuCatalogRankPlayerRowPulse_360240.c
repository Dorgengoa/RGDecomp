/* rgp:protos */
#define RGP_SELF_MenuCatalogRankPlayerRowPulse_360240 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    u8 pad274[0x274];
    s32 unk274;
    u8 pad284[0x284 - 0x278];
    s32 unk284;
} S00360240;

/*rgp*/
extern f32 D_0047D35C;
extern f32 D_0047F830;
extern f32 D_0047F834;
extern s16 D_0047F838;

void MenuCatalogRankPlayerRowPulse_360240(S00360240 *arg0) {
    f32 temp_f1;

    if (arg0->unk284 == 2 && D_0047F838 >= 0) {
        temp_f1 = D_0047F834 + D_0047F830;
        D_0047F834 = temp_f1;
        if (!(temp_f1 <= D_0047D35C)) {
            D_0047F834 = D_0047D35C;
            D_0047F830 = -D_0047F830;
        }
        if (D_0047F834 < 1.0f) {
            D_0047F834 = 1.0f;
            D_0047F830 = -D_0047F830;
        }
        UiSetTextColorScaled_290850(arg0->unk274, 0x1F3, 0xFF303030, D_0047F838, D_0047F834);
    }
}
