#include "types.h"

extern void MotionEventWriteHeaderText_1b1850(void *p1, void *fmt, void *p2);
extern void *OstreamWriteCStr_1a1dd0(void *cursor, void *data);
extern void *OstreamWriteInt_1a1f60(void *cursor, s32 data);

extern u8 D_0045A9F8[];
extern u8 D_0045AA00[];
extern u8 D_0045A9C8[];
extern u8 D_0045A9D0[];
extern u8 D_0045A9D8[];
extern u8 D_0045A9E0[];
extern u8 D_0045A9E8[];

typedef struct S1b15d0 {
    u8 pad0[0x28];
    s32 f28;
    s32 f2C;
} S1b15d0;

void MotionEventTexAnimeWriteText_1b15d0(S1b15d0 *p1, u8 *p2)
{
    void *cur;

    MotionEventWriteHeaderText_1b1850(p1, D_0045A9F8, p2);
    OstreamWriteCStr_1a1dd0(p2 + 0x18, D_0045AA00);
    if (p1->f28 != 0) {
        cur = OstreamWriteCStr_1a1dd0(p2 + 0x18, D_0045A9D0);
        cur = OstreamWriteCStr_1a1dd0(cur, (void *)p1->f28);
        OstreamWriteCStr_1a1dd0(cur, D_0045A9D0);
    } else {
        OstreamWriteCStr_1a1dd0(p2 + 0x18, D_0045A9C8);
    }
    cur = OstreamWriteCStr_1a1dd0(p2 + 0x18, D_0045A9D8);
    cur = OstreamWriteInt_1a1f60(cur, p1->f2C);
    OstreamWriteCStr_1a1dd0(cur, D_0045A9E0);
    OstreamWriteCStr_1a1dd0(p2 + 0x18, D_0045A9E8);
}
