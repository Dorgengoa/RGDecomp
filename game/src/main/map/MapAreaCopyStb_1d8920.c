/* rgp:protos */
#define RGP_SELF_MapAreaCopyStb_1d8920 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Rec {
    u8  pad00[0x2];
    s16 m02;
    s32 m04;
} Rec;

typedef struct Self {
    s32 m00;
    u8  pad04[0xA8 - 0x4];
    u8  mA8;
} Self;

/*rgp*/
/*rgp*/
/*rgp*/
extern void  Sprintf_1343b8(char *dst, const char *fmt, s32 v);
/*rgp*/
/*rgp*/
/*rgp*/
extern void *memcpy(void *d, const void *s, s32 n);
extern char D_0045B2D8[];

s32 MapAreaCopyStb_1d8920(Self *self)
{
    s32 len;
    char buf[0x4C] __attribute__((aligned(16)));
    Rec *p;
    void *q;
    void *dst;

    LoadHandlePollThunk_1ccb00(&self->mA8);
    p = ((Rec *)MapAreaLoadHandleAt_1dd120(&self->mA8, 0));
    if (p == NULL) {
        return -1;
    }
    if (p->m02 == 0) {
        return 0;
    }
    Sprintf_1343b8(buf, D_0045B2D8, MapAreaGetFileStem_1dce70(self));
    q = ArchiveGetFileByPath_1c2800(p->m04, buf, &len);
    if (q == NULL || len <= 0) {
        return 1;
    }
    dst = MemStackAllocQw_14d950(self->m00, AlignUp16_1cacd0(len) >> 4);
    *(void **)((u8 *)self + 0xE8) = dst;
    if (dst == NULL) {
        return -1;
    }
    memcpy(dst, q, len);
    *(s32 *)((u8 *)self + 0xEC) = len;
    return 2;
}
