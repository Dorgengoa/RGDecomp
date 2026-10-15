#include "types.h"

typedef struct {
    s8 v[128];
} Buf;

typedef struct {
    s16 h0;
    s16 h2;
    s16 h4;
    s16 h6;
} Rec;

typedef struct {
    u8 pad0[0x4dc];
    s32 unk4DC;
    s32 unk4E0;
    u8 pad4E4[8];
    s16 unk4EC;
    u8 pad4EE[0x10];
    s16 unk4FE;
    u8 *unk500;
} T3748c0_arg0;

extern s32 sceMcSync_12d098(s32, s32 *, s32 *);
extern s32 sceMcGetDir_12d3a8(s16, s32, void *, s32, s32, u8 *);
extern void SaveDirListClear_373330(void *);
extern u8 SaveSlotEntryIsEmptyAt_3734c0(void *, s32);
extern void SaveSlotEntriesClear_373590(void *);
extern s32 SaveCalcSizeKB_3735e0(void *);
extern s32 McSaveSlotScanStep_374b00(void *, s16, s32 *);
extern Rec *SaveMgrGetResult_375a00(void *);
extern void SaveSlotEntrySetNoSpace_376160(void *);
extern s32 strlen(const char *);

extern Buf D_00453F10;
extern s16 D_004831A8;

s32 McSaveDirScan_3748c0(T3748c0_arg0 *arg0)
{
    s32 spEC;
    s32 spE8;
    s32 spE4;
    Buf buf;
    Rec *r;
    s32 i;
    s32 ok;
    u8 *p;
    s32 rem;
    s32 flag;
    s32 cost;
    s8 *src;
    s8 *d;
    s32 n;

    spEC = 0;
    switch (arg0->unk4E0) {
    case 0:
        if (sceMcSync_12d098(1, NULL, NULL) == 0) {
            break;
        }
        SaveSlotEntriesClear_373590(arg0);
        SaveDirListClear_373330(arg0);
        d = buf.v;
        src = D_00453F10.v;
        n = 0x40;
        do {
            n--;
            d[0] = src[0];
            d[1] = src[1];
            src += 2;
            d += 2;
        } while (n > 0);
        if (sceMcGetDir_12d3a8(arg0->unk4EC, 1, &buf, 0, 0x32, arg0->unk500) == 0) {
            arg0->unk4E0++;
        }
        break;
    case 1:
        if (sceMcSync_12d098(1, &spE8, &spEC) == 0) {
            break;
        }
        arg0->unk4FE = 0;
        D_004831A8 = 0;
        if (spEC >= 0) {
            for (i = 0; i < 0x32; i++) {
                if (strlen((char *)(arg0->unk500 + (i << 6) + 0x20)) != 0) {
                    D_004831A8++;
                }
            }
            arg0->unk4E0++;
            break;
        }
        r = SaveMgrGetResult_375a00(arg0);
        r->h2 = arg0->unk4DC;
        r->h6 = arg0->unk4E0;
        return spEC;
    default:
        spE4 = arg0->unk4E0 - 2;
        ok = McSaveSlotScanStep_374b00(arg0, arg0->unk4FE, &spE4);
        arg0->unk4E0 = spE4 + 2;
        if (ok != 0) {
            arg0->unk4FE++;
        }
        if (arg0->unk4FE < 0x32) {
            break;
        }
        p = (u8 *)arg0 + arg0->unk4EC * 0x1C;
        rem = *(s32 *)(p + 0x4B4);
        flag = *(s32 *)(p + 0x4AC);
        cost = SaveCalcSizeKB_3735e0(arg0);
        for (i = 0; i < 0x32; i++) {
            if (SaveSlotEntryIsEmptyAt_3734c0(arg0, i) == 0) {
                continue;
            }
            if (flag == 0) {
                continue;
            }
            if (cost <= rem) {
                rem -= cost;
            } else {
                SaveSlotEntrySetNoSpace_376160((u8 *)arg0 + i * 2 + 0x78);
            }
        }
        return 1;
    }
    return 0;
}
