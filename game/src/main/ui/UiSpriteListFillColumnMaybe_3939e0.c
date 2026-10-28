/* rgp:protos */
#define RGP_SELF_UiSpriteListFillColumnMaybe_3939e0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
    s16 h8;
    s16 hA;
    s16 hC;
    s16 hE;
    s32 w10;
    s32 w14;
    s16 h18;
    s16 h1A;
    s32 w1C;
} Ent;

void UiSpriteListFillColumnMaybe_3939e0(s32 arg0, u8 *arg1, s32 n, s32 mode, f32 x, f32 y) {
    Ent *e;
    s32 i;
    f32 z;

    if (arg1 != NULL) {
        e = *(Ent **)(arg1 + 0x20);
        if (e != NULL) {
            z = 0.0f;
            for (i = 0; i < n; i++) {
                e->h0 = 0;
                e->h2 = (s32)(y * (f32)i);
                e->h4 = (s32)x;
                e->h6 = 6;
                switch (mode) {
                case 0:
                    e->h8 = 0x5F;
                    e->hA = 0x8B;
                    e->hC = 6;
                    e->hE = 6;
                    break;
                case 1:
                    e->h8 = 0x2C;
                    e->hA = 0xA6;
                    e->hC = 8;
                    e->hE = 6;
                    break;
                }
                e->w14 = 0;
                e->w10 = 0;
                e->h1A = (s16)z;
                e->h18 = (s16)z;
                e++;
            }
        }
    }
}
