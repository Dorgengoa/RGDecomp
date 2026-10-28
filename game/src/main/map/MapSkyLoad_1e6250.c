/* rgp:protos */
#define RGP_SELF_MapSkyLoad_1e6250 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct S_001e6250 {
    u8 pad0[0x17B0];
    u8 f17B0[0x10];
    s16 f17C0;
    s16 f17C2;
    s16 f17C4;
} S_001e6250;

extern u8 D_0045B4A0[];
/*rgp*/
/*rgp*/
/*rgp*/
extern void Sprintf_1343b8(void *, void *, void *);
/*rgp*/

s32 MapSkyLoad_1e6250(S_001e6250 *self, s32 k, void *p)
{
    u8 buf[0x80] __attribute__((aligned(16)));
    if (self->f17C0 == k) return 0;
    if (self->f17C2 == k) return 0;
    if (k < 0) goto zero;
    if (p != 0) goto ok;
zero:
    return 0;
ok:
    if (MapSkyGetHeap_1e6330((void *)self) == 0) return 0;
    MapSkyUnload_1e6190(self);
    LoadHandleReset_1ccc10(self->f17B0);
    Sprintf_1343b8(buf, D_0045B4A0, p);
    LoadHandleRequestFile_1ccbb0(self->f17B0, buf);
    self->f17C2 = k;
    self->f17C4 = 1;
    return 1;
}
