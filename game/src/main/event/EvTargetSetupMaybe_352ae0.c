/* rgp:protos */
#define RGP_SELF_EvTargetSetupMaybe_352ae0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { f32 x, y, z, w; } V4a;

typedef struct T352ae0 {
    u8  pad00[0x30];
    s32 f30;
    u8  pad34[0xD0 - 0x34];
    V4a v[6];
    s32 f130;
} T352ae0;

/*rgp*/
/*rgp*/

void EvTargetSetupMaybe_352ae0(T352ae0 *self, void *b, void *c, s32 d, V4a *arr, s32 n)
{
    EvTargetInit_352be0(self);
    TargetRefSetMapObj_2e6470(self, b, c, 0.0f);
    self->f30 = d;
    if (arr != 0) {
        if (n > 0) {
            self->f130 = 0;
            while (*(volatile s32 *)&self->f130 < n) {
                self->v[self->f130].x = arr[self->f130].x;
                self->v[self->f130].y = arr[self->f130].y;
                self->v[self->f130].z = arr[self->f130].z;
                self->v[self->f130].w = 1.0f;
                self->f130 = self->f130 + 1;
            }
        }
    }
}
