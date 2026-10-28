/* rgp:protos */
#define RGP_SELF_FileReqThread_182c30 1
#include "port/game_protos.h"
#line 1
#include "types.h"

s32 DisableIntr_120660(void);
void EnableIntr_1206b0(void);
/*rgp*/
void SignalSema(s32);
void WaitSema(s32);
/*rgp*/
extern s32 D_0047E020;
extern s32 D_0047E024;
extern s32 D_004811E8;
extern s32 D_004811F8;
extern s32 D_004811FC;
extern s32 D_00481204;
extern u8 D_00495FD0[];

void FileReqThread_182c30(void)
{
    s32 i;
    s32 t;
    s32 r;
    u8 *p;

    while (D_004811F8 != 0) {
        WaitSema(D_0047E020);
        while (!D_00481204) {
            t = DisableIntr_120660();
            p = D_00495FD0;
            for (i = 0; i < 0x20; i++) {
                p = D_00495FD0 + ((D_004811E8 + i) % 32) * 0x128;
                if (*(s32 *)(p + 0x120) == 0) {
                    continue;
                }
                if ((*(s32 *)(p + 4) != 0 && *(s32 *)(p + 8) == 0) ||
                    (*(s32 *)(p + 4) == 0 && *(s32 *)(p + 8) == 0)) {
                    break;
                }
            }
            if (t != 0) {
                EnableIntr_1206b0();
            }
            if (i == 0x20) {
                break;
            }
            if (*(s32 *)(p + 4) == 0) {
                r = FileReadChunked_180400(*(s32 *)(p + 0x124), *(s32 *)(p + 0x10C), *(s32 *)(p + 0x114));
                FileSlotCloseThunk_180540(*(s32 *)(p + 0x124));
                *(s32 *)(p + 0x124) = -1;
                if (r < *(s32 *)(p + 0x114)) {
                    *(s32 *)(p + 0x110) = r;
                }
                t = DisableIntr_120660();
                *(s32 *)(p + 4) = 1;
                *(s32 *)(p + 8) = 1;
                if (t != 0) {
                    EnableIntr_1206b0();
                }
            }
        }
        if (D_00481204 != 0) {
            D_00481204 = 0;
            SignalSema(D_0047E024);
        }
    }
    D_004811FC = 1;
}
