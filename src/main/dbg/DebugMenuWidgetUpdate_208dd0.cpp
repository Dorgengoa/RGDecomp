#include "types.h"

struct Widget {
    u8 pad000[0x22];
    s16 x22;
    u8 pad024[6];
    u16 x2A;
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void cancel();
    virtual void decide();
    virtual void add(s32);
    virtual void v6();
    virtual void update();
};

extern "C" {
s32 PadIsTriggered_1839f0(u8 *, s32);
s32 PadIsHeld_183a20(u8 *, s32);
s32 PadIsRepeatTriggered_183dd0(u8 *, s32);
void DebugMenuWidgetClearJustOpenedMaybe_209b90(Widget *);
s32 DebugMenuWidgetCursorNext_209c40(Widget *, s32);
s32 DebugMenuWidgetCursorPrev_209ce0(Widget *, s32);
Widget *DebugMenuWidgetGetCurrentChild_209dd0(Widget *);
extern u8 D_004B2570[];
void DebugMenuWidgetUpdate_208dd0(Widget *self);
}

void DebugMenuWidgetUpdate_208dd0(Widget *self) {
    Widget *child;
    Widget *c2;
    s32 delta;
    s32 step;
    s32 i;
    s32 n;

    DebugMenuWidgetClearJustOpenedMaybe_209b90(self);
    if (!(self->x2A & 0x40)) {
        return;
    }
    child = DebugMenuWidgetGetCurrentChild_209dd0(self);
    if (child != 0) {
        DebugMenuWidgetClearJustOpenedMaybe_209b90(child);
        if (child->x2A & 0x40) {
            child->update();
            return;
        }
        if (PadIsTriggered_1839f0(D_004B2570, 0x40)) {
            child->decide();
            return;
        }
        delta = 0;
        if (PadIsTriggered_1839f0(D_004B2570, 0x8000)) {
            if (!PadIsHeld_183a20(D_004B2570, 0x80)) {
                delta -= 1;
            } else {
                delta -= 100;
            }
        }
        if (PadIsTriggered_1839f0(D_004B2570, 0x2000)) {
            if (!PadIsHeld_183a20(D_004B2570, 0x80)) {
                delta += 1;
            } else {
                delta += 100;
            }
        }
        if (PadIsTriggered_1839f0(D_004B2570, 4)) {
            if (!PadIsHeld_183a20(D_004B2570, 0x80)) {
                delta -= 10;
            } else {
                delta -= 1000;
            }
        }
        if (PadIsTriggered_1839f0(D_004B2570, 8)) {
            if (!PadIsHeld_183a20(D_004B2570, 0x80)) {
                delta += 10;
            } else {
                delta += 1000;
            }
        }
        if (PadIsTriggered_1839f0(D_004B2570, 1)) {
            if (!PadIsHeld_183a20(D_004B2570, 0x80)) {
                delta -= 100;
            } else {
                delta -= 10000;
            }
        }
        if (PadIsTriggered_1839f0(D_004B2570, 2)) {
            if (!PadIsHeld_183a20(D_004B2570, 0x80)) {
                delta += 100;
            } else {
                delta += 10000;
            }
        }
        if (delta != 0) {
            child->add(delta);
            return;
        }
        if (PadIsTriggered_1839f0(D_004B2570, 0x10)) {
            child->add(0);
        }
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x20)) {
        self->cancel();
        return;
    }
    step = 1;
    if (PadIsHeld_183a20(D_004B2570, 0x80)) {
        step = 10;
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x1000)) {
        for (i = 0; i < step; i++) {
            n = DebugMenuWidgetCursorPrev_209ce0(self, self->x22);
            if (n < 0) {
                continue;
            }
            if (!(n < self->x22) && PadIsRepeatTriggered_183dd0(D_004B2570, 0x1000)) {
                break;
            }
            self->x22 = n;
        }
    }
    if (PadIsTriggered_1839f0(D_004B2570, 0x4000)) {
        for (i = 0; i < step; i++) {
            n = DebugMenuWidgetCursorNext_209c40(self, self->x22);
            if (n < 0) {
                continue;
            }
            if (!(n > self->x22) && PadIsRepeatTriggered_183dd0(D_004B2570, 0x4000)) {
                break;
            }
            self->x22 = n;
        }
    }
    c2 = DebugMenuWidgetGetCurrentChild_209dd0(self);
    if (c2 != 0 && c2 != child) {
        DebugMenuWidgetClearJustOpenedMaybe_209b90(c2);
    }
}
