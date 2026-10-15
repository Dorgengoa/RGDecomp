#include "types.h"
#pragma opt_common_subs off
#pragma opt_propagation off

typedef struct { f32 f; } FS;

class V7E40 {
public:
    u8 pad[0xDC];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual u8 v3();
};

extern "C" {
extern s32 EventPathRecFindPathByName_2e4040(s32, void *);
extern s32 EventPathGetTotalLength_2e4550(s32);
extern void TargetRefResolve_2e5ed0(void *, s32);
extern void EvObjResolveTarget_2f9a60(void *, s32);
extern char *strcpy(void *, const char *);
extern char D_00461DC0[];

s32 EvFollowObjResolveTarget_2f7e40(V7E40 *self)
{
    V7E40 *arg0;
    s32 hadFlag;
    s32 newFlags;
    s32 img;
    s32 v;

    arg0 = self;
    hadFlag = (*(s32 *)((u8 *)self + 0xD0) & 0x02000000) != 0;
    EvObjResolveTarget_2f9a60(self, 0);
    TargetRefResolve_2e5ed0((u8 *)arg0 + 0xE0, 0);
    if (!(arg0->v3() & 0xFF)) {
        newFlags = *(s32 *)((u8 *)arg0 + 0xD0) & 0xFDFFFFFF;
    } else {
        newFlags = *(s32 *)((u8 *)arg0 + 0xD0) | 0x02000000;
    }
    *(s32 *)((u8 *)arg0 + 0xD0) = newFlags;
    if (hadFlag == 0 && (*(s32 *)((u8 *)arg0 + 0xD0) & 0x02000000)) {
        *(s32 *)((u8 *)arg0 + 0x124) = 0;
        strcpy((u8 *)arg0 + 0x128, D_00461DC0);
        img = *(s32 *)((u8 *)arg0 + 0x110);
        if (img != 0) {
            v = EventPathRecFindPathByName_2e4040(img, (u8 *)arg0 + 0x128);
            if (v != 0) {
                *(s32 *)((u8 *)arg0 + 0x124) = (s32)(*(f32 *)((u8 *)arg0 + 0x138) * (f32)EventPathGetTotalLength_2e4550(v));
            }
        }
    }
    return 1;
}
}
