/* rgp:protos */
#define RGP_SELF_FarClipRecParseArgs_18c850 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Cur8 { s32 a, b; } Cur8;

typedef struct T18c850 {
    s32 f00;
    s32 f04;
    s32 f08;
    f32 f0C;
    f32 f10;
    s32 f14;
} T18c850;

extern char D_00459CF8[];

/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(const char *, const char *);
/*rgp*/

void FarClipRecParseArgs_18c850(T18c850 *self, Cur8 *q, s32 mode)
{
    char *s;

    self->f0C = VariantGetFloat_15f740(q++);
    self->f14 = VariantGetInt_15f780(q++);
    if (mode >= 3) {
        self->f10 = VariantGetFloat_15f740(q++);
    }
    if (self->f0C > 0.0f || self->f10 > 0.0f) {
        self->f04 = 1;
    }
    if (mode >= 4) {
        s = ((char *)SlotGetInt_15f720(q++));
        if (s != 0) {
            if (strcmp(s, D_00459CF8) == 0) {
                self->f08 = 1;
            }
        }
    }
    if (mode >= 5) {
        FarClipRecApplyPreset_18c950(self, VariantGetInt_15f780(q));
    }
}
