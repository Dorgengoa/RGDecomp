#include "types.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 w;
} V177a70;

void GsPktPushQword_13f170(s32, V177a70 *);
void GsPktFinalizeTags_13f260(s32);
void GsPktOpenGifTag_13f3b0(s32, s32, s32, s32, s32);
s32 DrawEnvGetCenterY_145120(s32);
s32 DrawEnvGetCenterX_145130(s32);
s32 DrawEnvGetHeight_1451d0(s32);
s32 GetDrawCtx_15de80(void);
extern f32 D_0047DF90;
extern f32 D_0047DF94;

static inline void Clr(u8 *p, u32 n)
{
    if (p != NULL) {
        while (n != 0) {
            *p = 0;
            n--;
            p++;
        }
    }
}

void ScreenFadeBlockDrawWipeStrips_177a70(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 off[2];
    V177a70 size;
    V177a70 b;
    V177a70 a;
    s32 obj;
    s32 step;
    s32 i;
    s32 y;

    obj = GetDrawCtx_15de80();
    GsPktOpenGifTag_13f3b0(arg0, 4, 0x43, 0, 2);
    Clr((u8 *)&size, 16);
    size.x = DrawEnvGetCenterX_145130(obj) * 16;
    size.y = DrawEnvGetCenterY_145120(obj) * 16;
    step = DrawEnvGetHeight_1451d0(obj) / 16;
    Clr((u8 *)&b, 16);
    Clr((u8 *)&a, 16);
    ((f32 *)off)[0] = D_0047DF90;
    ((f32 *)off)[1] = D_0047DF94;
    for (i = 0; i < 17; i++) {
        if (arg3 == 0) {
            a.x = arg1 * 16;
        } else {
            a.x = (arg1 + off[i % 2]) * 16;
        }
        if (a.x < 0) {
            a.x = 0;
        }
        y = i * step * 16;
        a.y = y;
        GsPktPushQword_13f170(arg0, &a);
        b.x = a.x + size.x;
        b.y = a.y + size.y;
        GsPktPushQword_13f170(arg0, &b);
        if (arg3 == 0) {
            a.x = (arg2 + off[i % 2]) * 16;
        } else {
            a.x = arg2 * 16;
        }
        if (a.x < 0) {
            a.x = 0;
        }
        a.y = y;
        GsPktPushQword_13f170(arg0, &a);
        b.x = a.x + size.x;
        b.y = a.y + size.y;
        GsPktPushQword_13f170(arg0, &b);
    }
    GsPktFinalizeTags_13f260(arg0);
}
