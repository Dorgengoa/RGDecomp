#include "types.h"
typedef unsigned __int128 u128;

#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 0x10; if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }

typedef struct Rect { s32 x, y, w, h; } __attribute__((aligned(16))) Rect;

extern void GsPktPushQword_13f170(s32, Rect *);
extern void GsPktFinalizeTags_13f260(s32);
extern void GsPktOpenGifTag_13f3b0(s32, s32, s32, s32, s32);
extern s32 DrawEnvGetTop_1450c0(s32);
extern s32 DrawEnvGetLeft_1450f0(s32);
extern s32 DrawEnvGetHeight_1451d0(s32);
extern s32 DrawEnvGetWidth_1451e0(s32);
extern s32 GetDrawCtx_15de80(void);

void GsPktTileScreenSprites_177cf0(s32 o)
{
    Rect sz;
    Rect r;
    Rect p;
    s32 t;
    s32 i;
    s32 j;

    t = GetDrawCtx_15de80();
    GsPktOpenGifTag_13f3b0(o, 6, 0x43, 0, 2);
    ZERO16(&sz);
    sz.x = DrawEnvGetLeft_1450f0(t) * 16;
    sz.y = DrawEnvGetTop_1450c0(t) * 16;
    ZERO16(&r);
    ZERO16(&p);
    for (i = 0; i < DrawEnvGetWidth_1451e0(t); i += 0x40) {
        for (j = 0; j < DrawEnvGetHeight_1451d0(t); j += 0x20) {
            p.y = j * 16;
            p.x = i * 16;
            *(u128 *)&r = *(u128 *)&sz;
            GsPktPushQword_13f170(o, &p);
            r.x = p.x + sz.x;
            r.y = p.y + sz.y;
            GsPktPushQword_13f170(o, &r);
            p.y = (j + 0x20) * 16;
            p.x = (i + 0x40) * 16;
            GsPktPushQword_13f170(o, &p);
            r.x = p.x + sz.x;
            r.y = p.y + sz.y;
            GsPktPushQword_13f170(o, &r);
        }
    }
    GsPktFinalizeTags_13f260(o);
}
