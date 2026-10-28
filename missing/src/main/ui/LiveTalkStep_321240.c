/* rg-missing: LiveTalkStep_321240 (retail MAIN 0x00321240, size 0x380)
 * why: TaskStepLiveTalk_321210 (task table D_0044ECF0) calls it every field frame
 * with the two live-talk slots D_00482B60; the snapshot has no C.  Per slot (1, 0):
 * state 1 waits for a pending skill action and starts its timer, 2 streams
 * "wav/!/LiveTalk/%04d-%1d-%05d.mwv" on stream channel slot+1 and runs the
 * action's event script, 3 watches the stream, 4 ends the action.
 * Checked: mwcc 3.0.1b210 -O4 compiles this file to retail's 221 instructions
 * (MATCH, out/missing-staged/README.md). */
#include "types.h"
#pragma divbyzerocheck on

/* A pending skill action (array D_004E9770, stride 0x48; SkillActionFindPending_3e0e90). */
typedef struct LiveTalkAct {
    s16 id;
    u8 pad2[2];
    s32 voice;
    u8 pad8[6];
    u8 bE0 : 1;
    u8 hasVoice : 1;
    u8 bErest : 6;
    u8 padF[0x3E - 0xF];
    s16 streamStatus;
} LiveTalkAct;

/* D_00482B60: two live-talk slots (LiveTalkSlotsInit_3216c0). */
typedef struct LiveTalkSlot {
    s16 state;
    u8 pad2[2];
    LiveTalkAct *act;
} LiveTalkSlot;

#ifndef __MWERKS__
/* port: layout checks (i686 pointers are 4 bytes, so every offset is retail's) */
#define RG_OFS(T, f, o) typedef char rg_ofs_##T##_##f[(__builtin_offsetof(T, f) == (o)) ? 1 : -1]
RG_OFS(LiveTalkAct, voice, 0x4);
RG_OFS(LiveTalkAct, streamStatus, 0x3E);
RG_OFS(LiveTalkSlot, act, 0x4);
#endif

extern char D_004623F0[]; /* "wav/!/LiveTalk/%04d-%1d-%05d.mwv" */

extern void *GetStreamMgr_207ea0(void);
extern void *GetGameData_1fede0(void);
extern s32 GetGameMode_1f59c0(void);
extern s32 StreamMgrChanGetStatus_1d65f0(void *mgr, s32 ch);
extern LiveTalkAct *SkillActionFindPending_3e0e90(void);
extern s32 SkillTimerStartMaybe_3e0c70(s32 id);
extern s32 GetKeyCapModeMaybe_1c3540(void);
extern s32 Sprintf_1343b8(char *buf, const char *fmt, ...);
extern s32 PathLocalize_1c28c0(char *dst, char *src);
extern void StreamMgrStartChan_1d66f0(void *mgr, s32 ch, char *path, s32 a3);
extern void StreamMgrPlayChan_1d6670(void *mgr, s32 ch, f32 vol);
extern s32 EvScriptRunImmediateMaybe_3e1140(LiveTalkAct *act);
extern void StreamMgrStopChan_1d66b0(void *mgr, s32 ch);
extern s32 SkillActionEnd_3e0c20(s32 id);

void LiveTalkStep_321240(LiveTalkSlot *slots)
{
    char path[0x80];
    char name[0x80];
    void *mgr;
    s32 mode;
    s32 i;
    LiveTalkSlot *slot;
    LiveTalkAct *act;
    LiveTalkAct *cur;
    LiveTalkAct *next;
    s32 ch;
    s32 st;
    u8 ok;

    mgr = GetStreamMgr_207ea0();
    if (mgr == 0) {
        return;
    }
    if (GetGameData_1fede0() == 0) {
        return;
    }
    mode = GetGameMode_1f59c0();
    if (mode != 7 && mode != 0x12 && mode != 0x11 && mode != 0xD && mode != 6) {
        return;
    }
    for (i = 1; i >= 0; i--) {
        slot = &slots[i];
        act = slot->act;
        cur = 0;
        if (act != 0 && act->id >= 0) {
            cur = act;
        }
        ch = i + 1;
        st = StreamMgrChanGetStatus_1d65f0(mgr, ch);
        switch (slot->state) {
        case 0:
            break;
        case 1:
            if (st == -1 || st == 1 || st == 3) {
                break;
            }
            next = SkillActionFindPending_3e0e90();
            if (next != 0 && next->id >= 0) {
                cur = next;
            }
            if (cur != 0) {
                slot->state = 2;
                slot->act = next;
                SkillTimerStartMaybe_3e0c70(cur->id);
            }
            break;
        case 2:
            if (st == -1 || st == 1 || st == 3) {
                slot->state = 4;
                break;
            }
            if (cur != 0) {
                ok = 1;
                if (GetKeyCapModeMaybe_1c3540() != 0) {
                    ok = 0;
                }
                if (ok) {
                    if (cur->hasVoice) {
                        Sprintf_1343b8(name, D_004623F0, cur->voice / 10 / 100000 % 10000,
                                       cur->voice / 100000 % 10, cur->voice % 100000);
                        PathLocalize_1c28c0(path, name);
                        StreamMgrStartChan_1d66f0(mgr, ch, path, 0);
                        StreamMgrPlayChan_1d6670(mgr, ch, 1.0f);
                        if (act != 0) {
                            act->streamStatus = st;
                        }
                        slot->state = 3;
                    } else {
                        slot->state = 4;
                    }
                    EvScriptRunImmediateMaybe_3e1140(cur);
                } else {
                    slot->state = 4;
                }
            }
            if (slot->state != 3) {
                slot->state = 4;
            }
            break;
        case 3:
            if (act != 0) {
                act->streamStatus = st;
            }
            if (st == 2) {
                StreamMgrStopChan_1d66b0(mgr, ch);
                slot->state = 4;
            } else if (st == 0) {
                StreamMgrStopChan_1d66b0(mgr, ch);
                slot->state = 4;
            }
            break;
        case 4:
            if (cur != 0) {
                SkillActionEnd_3e0c20(cur->id);
            }
            slot->state = 1;
            slot->act = 0;
            break;
        }
    }
}
