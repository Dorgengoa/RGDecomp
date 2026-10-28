#include "types.h"

struct Item {
    u8 pad0[0xc];
    s32 mC;
    char name[1];
};

struct Node {
    Node *next;
    u8 pad4[8];
    s32 key;
    Item data;
};

struct List {
    Node *head;
    Node *cur;
    s32 end;
    s32 Begin() {
        if (cur != 0) {
            return -1;
        }
        cur = head;
        end = 0;
        return 0;
    }
    Item *Next(s32 *key) {
        Item *p;
        if (cur == 0) {
            p = 0;
        } else {
            *key = cur->key;
            p = &cur->data;
            cur = cur->next;
            if (cur == 0) {
                end = 1;
            }
        }
        return p;
    }
    void Stop() {
        cur = 0;
        end = 0;
    }
};

struct Snd {
    List list;
    s32 mC;
    s32 m10;
    s32 m14;
    u8 pad18[4];
    s32 m1C;
    s32 m20;
};

extern "C" void MesWinOwnerCalcPageWait_24e860(Snd *);
extern "C" s32 EventVoiceStart_24ee40(Snd *, s32, s32, f32);
extern "C" void MesWinSetText_2727b0(s32, s32, s32, s32);
extern "C" s32 MesWinGetLabelText_274e10(s32);
extern "C" void MesWinSetLabelText_274e20(s32, s8 *);
extern "C" s32 MesWinGetTextFileSize_274e30(s32);
extern "C" s32 MesWinGetTextFile_274e40(s32);
extern "C" s8 *TextFindAtLabelLine_2772f0(s32, s32, s32);
extern "C" void MesWinClose_2774f0(s32);
extern "C" void strcpy(char *, const char *);

extern "C" s32 EventVoiceWithMessage_24ebf0(Snd *s, s32 arg1, s32 arg2, const char *arg3)
{
    s32 id;
    s32 t;
    s32 idx;
    s8 *str;
    Item *it;
    s32 key;

    if (s->mC == 0) {
        return -1;
    }
    id = EventVoiceStart_24ee40(s, arg1, 0, 1.0f);
    if (id >= 0) {
        t = MesWinGetTextFile_274e40(s->mC);
        idx = MesWinGetTextFileSize_274e30(s->mC);
        if (t != 0 && idx >= 0) {
            str = TextFindAtLabelLine_2772f0(t, idx, arg1);
            if (str != 0 && *str != 0x40) {
                MesWinClose_2774f0(s->mC);
                s->m10 = -1;
                MesWinSetLabelText_274e20(s->mC, str);
                MesWinSetText_2727b0(s->mC, MesWinGetLabelText_274e10(s->mC), 0, 0);
                s->m1C = 0;
                s->m20 = 1;
                s->m14 = 0;
                MesWinOwnerCalcPageWait_24e860(s);
            }
        }
        if (s->list.Begin() != 0) {
            it = 0;
        } else {
            while ((it = s->list.Next(&key)) != 0) {
                if (id == key) {
                    break;
                }
            }
            s->list.Stop();
        }
        if (it != 0) {
            it->mC = arg2;
            if (arg3 != 0) {
                strcpy(it->name, arg3);
            }
        }
    }
    return id;
}
