#include "types.h"

extern s32 sceMcOpen_12ca58(s16, s32, void *, s32);
extern s32 sceMcClose_12cbb8(s32, s32);
extern s32 sceMcWrite_12cf20(s32, u8 *, s32);
extern s32 sceMcSync_12d098(s32, s32 *, s32 *);
extern s32 sceMcFlush_12d8b8(s32);
extern u8 *GetGameData_1fede0(void);
extern void SaveProgressAdd_373650(u8 *, s32);
extern void McSetErrorResult_375890(u8 *, s32);
extern void SaveMgrClearResult_3759d0(u8 *);
extern s16 *SaveMgrGetResult_375a00(u8 *);
extern void SaveDataBuildWriteBuffer_375b80(u8 *);
extern void McSaveSerialize_375c60(u8 *);
extern void SaveSlotEntrySetBroken_376120(u8 *);
extern void McBuildIconPath_376400(void *, s16, s32);
extern void McBuildSaveDirPath_376460(void *, s16);
extern s32 sceMcMkdir(s16, s32, void *);
extern char *strcat(char *, const char *);
extern char D_004638C8[];

#define STATE (*(u32 *)(arg0 + 0x4E0))
#define X4E8 (*(s32 *)(arg0 + 0x4E8))
#define X4EC (*(s16 *)(arg0 + 0x4EC))
#define X4EE (*(s16 *)(arg0 + 0x4EE))
#define X514 (*(u8 **)(arg0 + 0x514))
#define X51C (*(s32 *)(arg0 + 0x51C))

s32 McSaveCreateStep_375090(u8 *arg0) {
    s32 sp16C;
    static s8 D_0047FAA8 = -1;
    static s32 D_0048319C;
    static s32 D_004831A0;
    s32 sp168;
    s32 sp164;
    char bufE0[0x84];
    char buf60[0x80];
    u8 *g;
    u8 *e;
    s16 *res;
    u8 *h;
    s32 n;
    s32 t;
    s32 d;
    u8 *h2;
    s32 k;
    s32 r;
    u8 *q;

    sp16C = 0;
    sp168 = 0;
    g = GetGameData_1fede0();
    e = arg0 + X4EC * 0x1C + 0x4A4;
    res = SaveMgrGetResult_375a00(arg0);
    h = arg0 + X4EE * 2 + 0x78;
    switch (STATE) {
    case 0:
        if (sceMcSync_12d098(1, 0, 0) != 0) {
            SaveMgrClearResult_3759d0(arg0);
            k = X4EE;
            D_004831A0 = 0xA00;
            McBuildSaveDirPath_376460(bufE0, k);
            if (sceMcMkdir(X4EC, 1, bufE0) == 0) {
                STATE++;
            } else {
                *res = 0xC;
                return 1;
            }
        }
        break;
    case 1:
        if (sceMcSync_12d098(1, &sp168, &sp16C) != 0) {
            if (sp16C < 0 && sp16C != -4) {
                McSetErrorResult_375890(arg0, sp16C);
                return 1;
            }
            McBuildIconPath_376400(buf60, X4EE, 0);
            if (sceMcOpen_12ca58(X4EC, 1, buf60, 0x202) == 0) {
                D_0047FAA8 = -1;
                STATE++;
            } else {
                return -1;
            }
        }
        break;
    case 2:
        if (sceMcSync_12d098(1, &sp168, &sp16C) != 0) {
            if (sp16C < 0) {
                if (sp16C == -2) {
                    *(s32 *)(e + 8) = 0;
                }
                if (sp16C < -10) {
                    *(s32 *)e = 0;
                }
                McSetErrorResult_375890(arg0, sp16C);
                SaveSlotEntrySetBroken_376120(h);
                return 1;
            }
            X4E8 = sp16C;
            X51C = 0;
            if (**(s32 **)(*(u8 **)(g + 0x24) + 0x1188) == 0) {
                McSaveSerialize_375c60(arg0);
            } else {
                SaveDataBuildWriteBuffer_375b80(arg0);
            }
            X514 = arg0 + 0xE0;
            k = X4E8;
            D_0048319C = 0x3C4;
            if (sceMcWrite_12cf20(k, arg0 + 0xE0, 0x3C4) == 0) {
                STATE++;
            } else {
                return -1;
            }
        }
        break;
    case 3:
    case 7:
    case 11:
    case 15:
        if (sceMcSync_12d098(1, &sp168, &sp164) != 0) {
            if (sp164 < 0) {
                if (sp164 < -10) {
                    *(s32 *)e = 0;
                }
                McSetErrorResult_375890(arg0, sp164);
                SaveSlotEntrySetBroken_376120(h);
                return 1;
            }
            X51C = X51C + sp164;
            SaveProgressAdd_373650(arg0, sp164);
            n = 0x500;
            if (D_004831A0 < 0x500) {
                n = D_004831A0;
            }
            D_004831A0 -= n;
            SaveProgressAdd_373650(arg0, n);
            d = D_0048319C;
            t = X51C;
            if (t >= d) {
                X51C = 0;
                if (sceMcFlush_12d8b8(X4E8) == 0) {
                    STATE++;
                } else {
                    return -1;
                }
            } else {
                r = d - t;
                n = 0x200;
                if (r < 0x200) {
                    n = r;
                }
                sceMcWrite_12cf20(X4E8, X514 + t, n);
            }
        }
        break;
    case 4:
    case 8:
    case 12:
    case 16:
        if (sceMcSync_12d098(1, &sp168, &sp16C) != 0) {
            if (sp168 != 10) {
                *res = 0xC;
                return 1;
            }
            if (sp16C < 0) {
                McSetErrorResult_375890(arg0, sp16C);
                SaveSlotEntrySetBroken_376120(h);
                return 1;
            }
            if ((sp168 = sceMcClose_12cbb8(X4E8, sp16C)) == 0) {
                STATE++;
            } else {
                *res = 0xC;
                return 1;
            }
        }
        break;
    case 5:
    case 9:
    case 13:
    case 17:
        if (sceMcSync_12d098(1, &sp168, &sp16C) != 0) {
            if (sp168 != 3) {
                *res = 0xC;
                return 1;
            }
            if (sp16C < 0) {
                McSetErrorResult_375890(arg0, sp16C);
                SaveSlotEntrySetBroken_376120(h);
                return 1;
            }
            if (++D_0047FAA8 <= 0) {
                McBuildSaveDirPath_376460(bufE0, X4EE);
                strcat(bufE0, D_004638C8);
                strcat(bufE0, (char *)(arg0 + D_0047FAA8 * 32));
                if ((sp168 = sceMcOpen_12ca58(X4EC, 1, bufE0, 0x203)) == 0) {
                    STATE++;
                } else {
                    return -1;
                }
            } else {
                SaveProgressAdd_373650(arg0, 0x800);
                SaveProgressAdd_373650(arg0, D_004831A0);
                return 1;
            }
        }
        break;
    case 6:
    case 10:
    case 14:
        if (sceMcSync_12d098(1, &sp168, &sp16C) != 0) {
            if (sp16C < 0) {
                if (sp16C < -10) {
                    *(s32 *)e = 0;
                }
                McSetErrorResult_375890(arg0, sp16C);
                SaveSlotEntrySetBroken_376120(h);
                return 1;
            }
            X4E8 = sp16C;
            X51C = 0;
            k = D_0047FAA8 * 4; q = (u8 *)(k + (s32)arg0);
            n = *(s32 *)(q + 0x6C);
            h2 = *(u8 **)(q + 0x60);
            X514 = h2;
            k = X4E8;
            D_0048319C = n;
            if ((sp168 = sceMcWrite_12cf20(k, h2, 0x200)) == 0) {
                STATE++;
            } else {
                return -1;
            }
        }
        break;
    }
    return 0;
}
