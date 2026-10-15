#include "types.h"

extern void Sprintf_1343b8(void *, void *, s32, void *);
extern s32 CharaIsCurMotion_238540(void *, void *);
extern s8 *strcpy(s8 *, const s8 *);
extern s8 D_0045C840[0x400];
extern s8 D_0045C868[0x400];
extern s8 D_0045C870[0x400];
extern s8 D_0045C8F0[0x400];
extern s8 D_0045C910[0x400];
extern s8 D_0045CAF0[0x400];
extern s8 D_0045CB00[0x400];
extern s8 D_0045CB10[0x400];
extern s8 D_0045CB20[0x400];
extern s8 D_0045CB30[0x400];

s32 CharaIsInKnockbackMotionMaybe_214db0(u8 *arg0) {
    s8 buf[0x20];
    s16 val;
    s16 t;

    if (!(*(s32 *)(arg0 + 0x3D8) & 1)) {
        return 0;
    }
    t = *(s16 *)(arg0 + 0xA2E);
    if (t == 2) {
        val = *(s16 *)(arg0 + 0xA2C);
        if (val <= 0) {
            strcpy(buf, D_0045CAF0);
        } else {
            Sprintf_1343b8(buf, D_0045C840, val + 0x60, D_0045CB00);
        }
    } else if (t == 3) {
        val = *(s16 *)(arg0 + 0xA2C);
        if (val <= 0) {
            strcpy(buf, D_0045CB10);
        } else {
            Sprintf_1343b8(buf, D_0045C868, val + 0x60, D_0045CB00);
        }
    } else {
        val = *(s16 *)(arg0 + 0xA2C);
        if (val <= 0) {
            strcpy(buf, D_0045CB00);
        } else {
            Sprintf_1343b8(buf, D_0045C870, val + 0x60, D_0045CB00);
        }
        strcpy(buf, D_0045CB00);
    }
    if (CharaIsCurMotion_238540(arg0, buf) != 0) {
        return 1;
    }
    t = *(s16 *)(arg0 + 0xA2E);
    if (t == 2) {
        val = *(s16 *)(arg0 + 0xA2C);
        if (val <= 0) {
            strcpy(buf, D_0045CB20);
        } else {
            Sprintf_1343b8(buf, D_0045C840, val + 0x60, D_0045C8F0);
        }
    } else if (t == 3) {
        val = *(s16 *)(arg0 + 0xA2C);
        if (val <= 0) {
            strcpy(buf, D_0045CB30);
        } else {
            Sprintf_1343b8(buf, D_0045C868, val + 0x60, D_0045C8F0);
        }
    } else {
        val = *(s16 *)(arg0 + 0xA2C);
        if (val <= 0) {
            strcpy(buf, D_0045C8F0);
        } else {
            Sprintf_1343b8(buf, D_0045C870, val + 0x60, D_0045C8F0);
        }
        strcpy(buf, D_0045C8F0);
    }
    if (CharaIsCurMotion_238540(arg0, buf) != 0) {
        return 1;
    }
    return CharaIsCurMotion_238540(arg0, D_0045C910);
}
