#include "types.h"

extern s32 sceOpen_11b928(s8 *, s32);
extern void sceClose_11bbb8(s32);
extern void sceWrite_11c1e0(s32, s32, s32);
extern void FilePathApplyAlias_181590(s8 *, s8 *);
extern s32 FilePathGetDeviceIndex_181a80(s8 *);
extern s32 FileBuildDevicePath_1821f0(s32, s8 *);
extern void FileNetWriteStub_1850e0(s8 *, s32, s32);
extern s32 SignalSema(s32);
extern s32 WaitSema(s32);
extern s8 *strcpy(s8 *, s8 *);
extern u32 strlen(s8 *);
extern s32 D_0047E028;
extern s32 D_004811C4;
extern s32 D_00481214;

static inline void lock180060(void)
{
    if (D_0047E028 >= 0) {
        WaitSema(D_0047E028);
    }
    D_004811C4++;
}

static inline void unlock180060(void)
{
    if (D_0047E028 >= 0) {
        SignalSema(D_0047E028);
    }
    D_004811C4--;
}

s32 FileWriteAll_180060(s32 arg0, s32 arg1, s32 arg2)
{
    s8 buf[0x100];
    s8 tmp[0x100];
    u8 *q;
    u32 n;
    s32 r;
    s8 *p;
    s32 c;
    s32 f;

    q = (u8 *)buf;
    n = 0x100;
    if (q != 0) {
        do {
            *q = 0;
            n--;
            q++;
        } while (n != 0);
    }
    r = FileBuildDevicePath_1821f0(arg0, buf);
    if (D_00481214 > 0) {
        q = (u8 *)tmp;
        n = 0x100;
        if (q != 0) {
            do {
                *q = 0;
                n--;
                q++;
            } while (n != 0);
        }
        if (strlen(buf) + 0x40 < 0x100) {
            FilePathApplyAlias_181590(tmp, buf);
            strcpy(buf, tmp);
            r = FilePathGetDeviceIndex_181a80(buf);
            if (r < 0) {
                return 0;
            }
        }
    }
    if (r == 2) {
        p = buf;
        while ((c = *p) != 0) {
            p++;
            if ((s8)c == ':') {
                break;
            }
        }
        lock180060();
        FileNetWriteStub_1850e0(p, arg1, arg2);
        unlock180060();
        return 1;
    }
    p = buf;
    lock180060();
    f = sceOpen_11b928(p, 0x602);
    unlock180060();
    if (f < 0) {
        return 0;
    }
    lock180060();
    sceWrite_11c1e0(f, arg1, arg2);
    sceClose_11bbb8(f);
    unlock180060();
    return 1;
}
