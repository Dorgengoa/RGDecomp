#include "types.h"

extern s16 HpGaugeGetBarWidth_31e2f0(void);
extern f32 HpGaugeGetSettledRatio_31e620(u8 *, s32);
extern f32 HpGaugeGetTargetRatio_31e640(u8 *, s32);

void HpGaugeAnimValues_31e3b0(u8 *self)
{
    s32 t;
    s32 i;
    f32 tgt;
    f32 cur;
    f32 v;
    f32 d;
    f32 st;
    f32 *pa;
    u8 *e;

    t = HpGaugeGetBarWidth_31e2f0();
    for (i = 0; i < 0x10; i++) {
        tgt = HpGaugeGetTargetRatio_31e640(self, i);
        cur = HpGaugeGetSettledRatio_31e620(self, i);
        if (tgt == cur) {
            *(f32 *)(self + i * 4 + 0x100) = tgt;
        } else if (!(cur <= tgt)) {
            d = (f32)t / 100.0f;
            e = self + i * 4;
            st = d / (f32)t;
            v = *(f32 *)(e + 0x100) - st;
            pa = (f32 *)(e + 0x100);
            if (!(v <= tgt)) {
                *pa = v;
            } else {
                *pa = tgt;
                *(f32 *)(e + 0x140) = tgt;
            }
            if (*pa <= 0.0f) {
                *pa = 0.0f;
                self[i + 0x1C0] = 2;
            }
        } else {
            d = (f32)t / 100.0f;
            e = self + i * 4;
            st = d / (f32)t;
            v = *(f32 *)(e + 0x100) + st;
            pa = (f32 *)(e + 0x100);
            if (v < tgt) {
                *pa = v;
            } else {
                *pa = tgt;
                *(f32 *)(e + 0x140) = tgt;
            }
            if (!(*pa < 1.0f)) {
                *pa = 1.0f;
            }
        }
    }
}
