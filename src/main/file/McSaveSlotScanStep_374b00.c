#include "types.h"

typedef struct {
    u8 pad0[0x10];
    s32 f10;
} Sub;

typedef struct {
    u8 pad0[0x78];
    s16 tbl[(0x4E8 - 0x78) / 2];
    s32 h;          /* 0x4E8 */
    s16 id;         /* 0x4EC */
    u8 pad4EE[0x504 - 0x4EE];
    Sub *p504;      /* 0x504 */
    Sub *p508;      /* 0x508 */
    s32 buf;        /* 0x50C */
    u8 pad510[0x51C - 0x510];
    s32 n;          /* 0x51C */
} Obj;

typedef struct {
    s16 s0;
    u8 pad2[6];
    s32 f8;
} Ctl;

typedef struct {
    u8 pad0[0x5C];
    s32 f5C;
} Sys;

extern s32 sceMcOpen_12ca58(s16, s32, char *, s32);
extern s32 sceMcClose_12cbb8(s32);
extern s32 sceMcRead_12ce08(s32, s32, s32);
extern s32 sceMcSync_12d098(s32, s32 *, s32 *);
extern s32 sceMcGetDir_12d3a8(s16, s32, char *, s32, s32, Sub *);
extern void Sprintf_1343b8(char *, void *, s32);
extern Sys *GetGameData_1fede0(void);
extern void McSaveHeaderCheckClearedMaybe_372fd0(s32, s16);
extern void McSaveHeaderMergeFlagsMaybe_373060(s32);
extern s32 McSaveFlagMergeEnabledMaybe_373150(void);
extern s32 SaveDirListContains_3732b0(Obj *, char *);
extern void SaveProgressAdd_373650(Obj *, s32);
extern void McSetErrorResult_375890(Obj *, s32);
extern Ctl *SaveMgrGetResult_375a00(Obj *);
extern void SaveDirEntriesClear_376020(Sub *, s32);
extern void SaveSlotEntrySetValid_376080(s16 *);
extern void SaveSlotEntrySetBadData_3760d0(s16 *);
extern void SaveSlotEntrySetBroken_376120(s16 *);
extern void SaveSlotEntryClear_3761a0(s16 *);
extern void MemcardBuildSavePath_376380(s32, char *);
extern void McBuildIconPath_376400(char *, s32, s32);
extern s32 SlotRecordStore_3e52f0(Sys *, s32, s32, s32);
extern void memset(s32, s32, s32);
extern char D_00463900[];
extern char D_00463920[];
extern s32 D_004658F0[4];
extern s32 D_004831A4;

s32 McSaveSlotScanStep_374b00(Obj *o, s32 idx, s32 *st) {
    s32 a;
    s32 b;
    s32 c;
    char b110[0x84];
    char bF0[0x20];
    char b70[0x80];
    Sys *sys;
    Ctl *ctl;
    s16 *ent;
    s32 r;

    sys = GetGameData_1fede0();
    ctl = SaveMgrGetResult_375a00(o);
    ent = &o->tbl[idx];
    switch (*st % 8) {
    case 0:
        if (sceMcSync_12d098(1, 0, 0) == 0) {
            break;
        }
        o->h = -1;
        Sprintf_1343b8(bF0, D_00463900, idx);
        if (SaveDirListContains_3732b0(o, bF0) == 0) {
            *st += 8;
            SaveSlotEntryClear_3761a0(ent);
            return -1;
        }
        Sprintf_1343b8(b70, D_00463920, idx);
        SaveDirEntriesClear_376020(o->p504, 6);
        if (sceMcGetDir_12d3a8(o->id, 1, b70, 0, 6, o->p504) == 0) {
            *st += 1;
            break;
        }
        sceMcSync_12d098(1, 0, 0);
        break;
    case 1:
        if (sceMcSync_12d098(1, &a, &b) == 0) {
            break;
        }
        if (a != 0xD) {
            break;
        }
        if (b < 0) {
            McSetErrorResult_375890(o, b);
            *st += 7;
            return 1;
        }
        *st += 1;
        break;
    case 2:
        McBuildIconPath_376400(b110, idx, 0);
        SaveDirEntriesClear_376020(o->p508, 9);
        if (sceMcGetDir_12d3a8(o->id, 1, b110, 0, 1, o->p508) == 0) {
            *st += 1;
            break;
        }
        *st += 6;
        return 1;
    case 3:
        if (sceMcSync_12d098(1, &a, &b) == 0) {
            break;
        }
        if (b <= 0) {
            McSetErrorResult_375890(o, b);
            *st += 5;
            SaveSlotEntrySetBroken_376120(ent);
            return 1;
        }
        if (o->p508->f10 != 0x3C4) {
            McSetErrorResult_375890(o, b);
            *st += 5;
            SaveSlotEntrySetBroken_376120(ent);
            return 1;
        }
        b110[0] = 0;
        MemcardBuildSavePath_376380(idx, b110);
        if (sceMcOpen_12ca58(o->id, 1, b110, 1) == 0) {
            *st += 2;
            break;
        }
        *st += 5;
        return 1;
    case 5:
        if (sceMcSync_12d098(1, &a, &b) == 0) {
            break;
        }
        if (b < 0) {
            McSetErrorResult_375890(o, b);
            *st += 3;
            SaveSlotEntrySetBroken_376120(ent);
            return 1;
        }
        o->h = b;
        o->n = 0;
        {
            s32 sz = D_004658F0[0];
            s32 buf;
            ctl->f8 = 0;
            buf = o->buf;
            memset(buf, 0, D_004831A4 = sz);
        }
        if (sceMcRead_12ce08(o->h, o->buf, D_004831A4) == 0) {
            *st += 1;
            break;
        }
        McSetErrorResult_375890(o, b);
        *st += 3;
        SaveSlotEntrySetBroken_376120(ent);
        return 1;
    case 6:
        if (sceMcSync_12d098(1, &a, &c) == 0) {
            break;
        }
        if (c < 0) {
            McSetErrorResult_375890(o, c);
            *st += 2;
            sceMcClose_12cbb8(o->h);
            sceMcSync_12d098(0, 0, 0);
            ctl->s0 = 0;
            return 1;
        }
        o->n += c;
        SaveProgressAdd_373650(o, c);
        if (o->n >= D_004831A4) {
            if (sceMcClose_12cbb8(o->h) == 0) {
                *st += 1;
                break;
            }
            *st += 2;
            return -1;
        } else {
            if (sceMcClose_12cbb8(o->h) == 0) {
                *st += 1;
                break;
            }
            *st += 2;
            return -1;
        }
    case 7:
        if (sceMcSync_12d098(1, &a, &b) == 0) {
            break;
        }
        if (b < 0) {
            McSetErrorResult_375890(o, b);
            *st += 1;
            SaveSlotEntrySetBroken_376120(ent);
            return -1;
        }
        r = SlotRecordStore_3e52f0(sys, idx, o->buf, D_004658F0[0]);
        switch (sys->f5C) {
        case 0:
        case 10:
            SaveSlotEntrySetValid_376080(ent);
            if (McSaveFlagMergeEnabledMaybe_373150() != 0) {
                McSaveHeaderMergeFlagsMaybe_373060(r);
                McSaveHeaderCheckClearedMaybe_372fd0(r, o->id);
            }
            break;
        case 9:
            SaveSlotEntrySetBadData_3760d0(ent);
            break;
        default:
            SaveSlotEntrySetBadData_3760d0(ent);
            break;
        }
        *st += 1;
        return 1;
    }
    return 0;
}
