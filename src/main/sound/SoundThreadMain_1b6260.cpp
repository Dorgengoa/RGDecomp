#pragma opt_propagation off
#include "types.h"
extern "C" {

typedef struct {
    s32 b[10];
} Data001B6260;

typedef struct {
    s32 id;
    Data001B6260 data;
} Msg001B6260;

typedef struct {
    u8 empty;
    s32 rd;
    s32 wr;
    Msg001B6260 q[64];
} Queue001B6260;

void DeleteSema(s32);
void ExitDeleteThread(void);
s32 SignalSema(s32);
s32 WaitSema(s32);
void *memcpy(void *, const void *, u32);
extern s32 D_0048142C;
extern s32 D_00481430;
extern s32 D_00481434;
extern s32 D_00481440;
extern s32 D_0048144C;
extern s32 D_00481450;
extern u8 D_00481458;
extern u8 D_0049D510[0x28];
extern Queue001B6260 D_0049DD70;
}

extern "C" void SoundThreadMain_1b6260(void) {
    Msg001B6260 msg;
    u8 full;
    bool ok;
    s32 t;
    s32 id;
    Msg001B6260 *row;
    s32 n;
    Data001B6260 *src;

    while (D_00481458) {
        WaitSema(D_0048144C);
        t = D_0049DD70.empty != 0;
        if (t) {
            t = D_0049DD70.rd == D_0049DD70.wr;
        }
        full = t;
        SignalSema(D_0048144C);
        if (full) {
            WaitSema(D_00481450);
        }
        msg.id = 0;
        WaitSema(D_0048144C);
        if (D_0049DD70.empty != 0 && D_0049DD70.rd == D_0049DD70.wr) {
            ok = false;
        } else {
            row = &D_0049DD70.q[D_0049DD70.rd];
            msg.id = row->id;
            msg.data = row->data;
            n = (D_0049DD70.rd + 1) & 0x3F;
            D_0049DD70.rd = n;
            if (n == D_0049DD70.wr) {
                D_0049DD70.empty = 1;
            }
            ok = true;
        }
        SignalSema(D_0048144C);
        if ((ok & 0xFF) == 0) {
            continue;
        }
        id = msg.id;
        if (id == -1) {
            break;
        }
        if (WaitSema(D_00481430) < 0) {
            continue;
        }
        D_00481440 = id;
        src = &msg.data;
        if (src) {
            memcpy(D_0049D510, src, 0x28);
        }
        SignalSema(D_0048142C);
        WaitSema(D_00481434);
        SignalSema(D_00481430);
    }
    if (D_0048144C > 0) {
        DeleteSema(D_0048144C);
    }
    if (D_00481450 > 0) {
        DeleteSema(D_00481450);
    }
    D_0048144C = -1;
    D_00481450 = -1;
    ExitDeleteThread();
}
