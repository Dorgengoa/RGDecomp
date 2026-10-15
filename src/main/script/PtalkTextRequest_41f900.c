#include "types.h"

void LoaderQueueAppendSeparator_1cd670(s32);
s32 LoaderRequestFile_1cd870(s32, void *, s32);
s32 GetLoaderMgr_1f59d0(void);
s32 StrCacheFind_3f01a0(s32, s32, s32, s32);
u8 PtalkTextPacPath_41fac0(void *, void *, s16 *);
u8 *GroupFindByKey_41fbf0(void *, s32);

s32 PtalkTextRequest_41f900(u8 *arg0, s32 arg1, s32 arg2) {
    u8 buf[0x80];
    s32 h;
    u8 *e;
    s16 **pp;
    s16 *p;
    s32 r;

    if (*(s32 *)(arg0 + 4) == 0) {
        return 0;
    }
    if (*(s32 *)(arg0 + 0x10) == 2) {
        return 0;
    }
    h = GetLoaderMgr_1f59d0();
    if (h == 0) {
        return 0;
    }
    e = GroupFindByKey_41fbf0(arg0, arg1);
    if (e == NULL) {
        return 0;
    }
    pp = *(s16 ***)(e + 0x94);
    if (pp == NULL) {
        return 0;
    }
    p = *pp;
    if (p == NULL) {
        return 0;
    }
    r = StrCacheFind_3f01a0(*(s32 *)(arg0 + 4), 1, *p, arg2);
    if (r != 0) {
        *(s16 **)(arg0 + 0x18) = p;
        *(s16 *)(arg0 + 0x1C) = arg2;
        *(s32 *)(arg0 + 0x20) = r;
        *(s32 *)(arg0 + 0x10) = 3;
        return 1;
    }
    if ((PtalkTextPacPath_41fac0(arg0, buf, p) & 0xFF) == 0) {
        return 0;
    }
    *(s32 *)(arg0 + 0x14) = LoaderRequestFile_1cd870(h, buf, 0);
    if (*(s32 *)(arg0 + 0x14) < 0) {
        return 0;
    }
    LoaderQueueAppendSeparator_1cd670(h);
    *(s32 *)(arg0 + 0x10) = 2;
    *(s16 **)(arg0 + 0x18) = p;
    *(s16 *)(arg0 + 0x1C) = arg2;
    *(s32 *)(arg0 + 0x20) = 0;
    return 1;
}
