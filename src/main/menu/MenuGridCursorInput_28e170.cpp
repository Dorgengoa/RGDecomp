#include "types.h"

typedef struct Desc {
    u8 pad0[0x12];
    s16 x12;
    s16 x14;
    u8 pad16[0x1C - 0x16];
    s32 x1C;
    void (*fn[8])(void *, s32);
} Desc;

typedef struct Cur {
    Desc *desc;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE;
    s16 x10;
    s16 x12;
    s16 x14;
    s16 x16;
    s16 x18;
    s16 x1A;
    s16 x1C;
    s16 x1E;
} Cur;

typedef struct Menu {
    u8 pad0[0xC];
    Cur *cur;
    s32 x10;
    s32 x14;
    s32 x18;
    s32 x1C;
    u8 b0 : 1;
    u8 lock : 1;
    u8 pad21;
    s8 wait;
} Menu;

extern "C" {
extern s32 PadIsTriggered_1839f0(s32, s32);
extern s32 PadIsRepeatTriggered_183dd0(s32, s32);
extern void SoundPlayScaledVolume_1b9520(s32, s32, s32, f32);
extern void PadRestartRepeat_28e900(Menu *, s32, s32);
extern void MenuGridCursorSeUpdate_28e960(Menu *);
extern void MenuGridCursorRequestSe_28e9e0(Menu *, s32);
extern s32 GetPauseStep_2f6660(void);
s32 MenuGridCursorInput_28e170(Menu *m, s32 a1, s32 a2, s32 a3);
}

s32 MenuGridCursorInput_28e170(Menu *m, s32 a1, s32 a2, s32 a3) {
    s32 st;
    s32 ret;
    s32 flags;
    bool moved;
    u8 lock;
    Cur *c;
    s16 *p;
    s16 *q;
    s32 f9;
    s32 n;
    s32 i;
    void (*f)(void *, s32);

    if (a1 == 0 && a3 == 0) {
        return -1;
    }
    if (a1 == 0) {
        a1 = a3;
    }
    if (a3 == 0) {
        a3 = a1;
    }
    st = GetPauseStep_2f6660();
    m->x14 = 0;
    m->x1C = 0;
    ret = -1;
    flags = 0x20;
    moved = false;
    lock = m->lock;
    if (m->wait > 0) {
        m->wait--;
        lock = true;
        if (m->wait < 0) {
            m->wait = 0;
        }
    }
    if (!lock && (st == 0 || st == 3)) {
        if (PadIsTriggered_1839f0(a1, 0x4000) || PadIsTriggered_1839f0(a3, 0x4000)) {
            c = m->cur;
            p = &c->x16;
            if (*p < c->xE) {
                *p = *p + 1;
                flags |= 1;
                moved = true;
            } else if (q = &c->x1A, *p + *q < c->x12) {
                *q = *q + 1;
                flags |= 1;
                moved = true;
            } else if ((a2 & 4) && c->xE > 0 && (PadIsRepeatTriggered_183dd0(a1, 0x4000) == 0 || PadIsRepeatTriggered_183dd0(a3, 0x4000) == 0)) {
                flags |= 1;
                moved = true;
                m->cur->x16 = 0;
                PadRestartRepeat_28e900(m, a1, 0x4000);
                PadRestartRepeat_28e900(m, a3, 0x4000);
            } else {
                m->x14 |= 2;
            }
        } else if (PadIsTriggered_1839f0(a1, 0x1000) || PadIsTriggered_1839f0(a3, 0x1000)) {
            c = m->cur;
            p = &c->x16;
            if (*p > 0) {
                *p = *p - 1;
                flags |= 1;
                moved = true;
            } else if (q = &c->x1A, *p + *q > 0) {
                *q = *q - 1;
                flags |= 1;
                moved = true;
            } else if ((a2 & 4) && c->xE > 0 && (PadIsRepeatTriggered_183dd0(a1, 0x1000) == 0 || PadIsRepeatTriggered_183dd0(a3, 0x1000) == 0)) {
                flags |= 1;
                moved = true;
                c = m->cur;
                c->x16 = c->xE;
                PadRestartRepeat_28e900(m, a1, 0x1000);
                PadRestartRepeat_28e900(m, a3, 0x1000);
            } else {
                m->x14 |= 1;
            }
        }
        if (PadIsTriggered_1839f0(a1, 0x2000) || PadIsTriggered_1839f0(a3, 0x2000)) {
            c = m->cur;
            p = &c->x14;
            if (*p < c->xC) {
                *p = *p + 1;
                flags |= 1;
                moved = true;
            } else if (q = &c->x18, *p + *q < c->x10) {
                *q = *q + 1;
                moved = true;
                flags |= 1;
            } else if ((a2 & 2) && c->xC > 0 && (PadIsRepeatTriggered_183dd0(a1, 0x2000) == 0 || PadIsRepeatTriggered_183dd0(a3, 0x2000) == 0)) {
                flags |= 1;
                moved = true;
                m->cur->x14 = 0;
                PadRestartRepeat_28e900(m, a1, 0x2000);
                PadRestartRepeat_28e900(m, a3, 0x2000);
            } else {
                m->x14 |= 8;
            }
        } else if (PadIsTriggered_1839f0(a1, 0x8000) || PadIsTriggered_1839f0(a3, 0x8000)) {
            c = m->cur;
            p = &c->x14;
            if (*p > 0) {
                *p = *p - 1;
                flags |= 1;
                moved = true;
            } else if (q = &c->x18, *p + *q > 0) {
                *q = *q - 1;
                flags |= 1;
                moved = true;
            } else if ((a2 & 2) && c->xC > 0 && (PadIsRepeatTriggered_183dd0(a1, 0x8000) == 0 || PadIsRepeatTriggered_183dd0(a3, 0x8000) == 0)) {
                flags |= 1;
                moved = true;
                c = m->cur;
                c->x14 = c->xC;
                PadRestartRepeat_28e900(m, a1, 0x8000);
                PadRestartRepeat_28e900(m, a3, 0x8000);
            } else {
                m->x14 |= 4;
            }
        }
    }
    c = m->cur;
    c->x1C = c->x8 * (c->x14 + c->x18);
    m->cur->x1C = m->cur->x4;
    c = m->cur;
    c->x1E = c->xA * (c->x16 + c->x1A);
    m->cur->x1E = m->cur->x6;
    if (moved) {
        MenuGridCursorRequestSe_28e9e0(m, a2);
    }
    MenuGridCursorSeUpdate_28e960(m);
    if (!lock && (st == 0 || st == 3)) {
        if (m->cur->desc->x1C & 4) {
            if (PadIsTriggered_1839f0(a1, 0x20) || PadIsTriggered_1839f0(a3, 0x20)) {
                ret = 2;
                flags |= 4;
                n = m->cur->desc->x14;
                if (n > 0) {
                    if (!(a2 & 0x11)) {
                        SoundPlayScaledVolume_1b9520(m->x18, n, 0, 1.0f);
                    }
                } else if (n == 0) {
                    if (!(a2 & 0x11)) {
                        SoundPlayScaledVolume_1b9520(m->x18, 6, 0, 1.0f);
                    }
                }
            }
        }
        if (ret == -1 && (m->cur->desc->x1C & 2)) {
            if (PadIsTriggered_1839f0(a1, 0x40) || PadIsTriggered_1839f0(a3, 0x40)) {
                ret = 1;
                flags |= 2;
                n = m->cur->desc->x12;
                if (n > 0) {
                    if (!(a2 & 0x11)) {
                        SoundPlayScaledVolume_1b9520(m->x18, n, 0, 1.0f);
                    }
                } else if (n == 0) {
                    if (!(a2 & 0x11)) {
                        SoundPlayScaledVolume_1b9520(m->x18, 5, 0, 1.0f);
                    }
                }
            }
        }
        if (m->cur->desc->x1C & 0x40) {
            f9 = 0;
            if (PadIsTriggered_1839f0(a1, 0x9F) || PadIsTriggered_1839f0(a3, 0x9F)) {
                f9 = 1;
            }
            if (f9) {
                ret = 6;
                flags |= 0x40;
            }
        }
    }
    m->x1C = flags;
    for (i = 0; i < 8; i++) {
        if (flags & (1 << i)) {
            f = *(void (**)(void *, s32))((u32)m->cur->desc + (u32)i * 4 + 0x20);
            if (f != 0) {
                f(&m->cur->x4, m->x10);
            }
        }
    }
    return ret;
}
