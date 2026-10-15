/* PARKED s17b: win/lose/draw stat classifier. 1 round trip: 131 words,
   length 0x20C vs retail 0x220 (5 words short). */
#include "types.h"

extern void LoaderTick_1ccc30(s32);
extern s32 LoaderGetStatus_1cd4f0(s32, s32);
extern s32 LoaderIsIdle_1cd5b0(s32);
extern s32 LoaderCountQueued_1cd620(s32);
extern s32 GetLoaderMgr_1f59d0(void);
extern void ScriptSetRefInt_26a1e0(s32, s32);
extern s32 D_00482074;
extern u8 D_004BE170[0x400];

s32 EvCmdResLoadStatus_268780(s64 *arg0, s32 arg1)
{
    s32 total;
    s32 nWin;
    s32 nDraw;
    s32 nLose;
    s32 result;
    u32 handle;
    s32 count;
    s32 flag;
    u8 *p;
    s32 i;
    s32 v;
    s32 slot;

    if (arg1 <= 0) {
        return 0;
    }
    total = 0;
    nWin = 0;
    nDraw = 0;
    nLose = 0;
    result = 0;

    handle = GetLoaderMgr_1f59d0();
    LoaderTick_1ccc30(handle);
    count = LoaderCountQueued_1cd620(handle);
    flag = LoaderIsIdle_1cd5b0(handle) & 0xFF;

    if (count > 0) {
        i = 0;
        p = D_004BE170;
        while (i < D_00482074) {
            v = *(s32 *)p;
            if (v >= 0) {
                slot = LoaderGetStatus_1cd4f0(handle, v);
                total += 1;
                if (slot == -1) {
                    nLose += 1;
                } else if (slot == 0) {
                    nDraw += 1;
                } else if (slot == 1) {
                    nWin += 1;
                }
            }
            p += 0x84;
            i += 1;
        }
        if (total > 0) {
            if (total == nWin) {
                result = 1;
            } else if (total == nLose) {
                result = 9;
            } else {
                if (total == (nWin + nLose)) {
                    result = 2;
                } else {
                    if (flag != 0) {
                        if (nWin > 0) {
                            if (nLose > 0) {
                                result = 4;
                            } else {
                                result = 3;
                            }
                        } else if (nLose > 0) {
                            result = 6;
                        } else {
                            result = 5;
                        }
                    } else if (nLose > 0) {
                        result = 8;
                    } else {
                        result = 7;
                    }
                }
            }
        }
    }

    ScriptSetRefInt_26a1e0((s32)arg0++, result);
    if (arg1 >= 2) {
        ScriptSetRefInt_26a1e0((s32)arg0++, nWin);
    }
    if (arg1 >= 3) {
        ScriptSetRefInt_26a1e0((s32)arg0++, nDraw);
    }
    if (arg1 >= 4) {
        ScriptSetRefInt_26a1e0((s32)arg0++, nLose);
    }
    if (arg1 >= 5) {
        ScriptSetRefInt_26a1e0((s32)arg0, flag & 0xFF);
    }
    return 1;
}
