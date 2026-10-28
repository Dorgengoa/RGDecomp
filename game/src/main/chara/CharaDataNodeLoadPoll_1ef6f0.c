/* rgp:protos */
#define RGP_SELF_CharaDataNodeLoadPoll_1ef6f0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_001ef6f0 {
    u8 pad0[8];
    s16 f8;
    s16 fA;
    s32 fC;
    u8 pad10[0x1E - 0x10];
    u8 f1E;
} S_001ef6f0;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void CharaDataNodeLoadPoll_1ef6f0(S_001ef6f0 *self)
{
    void *p;
    s32 r;
    if (self->f1E != 1) return;
    if (self->fC < 0) return;
    p = GetLoaderMgr_1f59d0();
    r = LoaderGetStatus_1cd4f0(p, self->fC);
    if (r == -1) {
        LoaderReleaseById_1cd340(p, self->fC);
        self->fC = -1;
        self->f1E = CharaDataNodeFailStatus_1ef9a0(self->f8);
        CharaDataNodeLoadFailStub_1ef7a0();
    } else if (r == 1) {
        self->f1E = 2;
    }
}
