/* rgp:protos */
#define RGP_SELF_MotionEventCfgParse_1b45c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct { u8 b[0xED0]; } Reader;
typedef struct { s32 w[12]; } Arg;
typedef struct {
    Arg a;
    s32 k8;
    s32 arg0;
    s32 r;
    u8 pad[0x24];
} Buf;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern void memset(void *, s32, s32);
extern u8 D_0044ADC0[];

s32 MotionEventCfgParse_1b45c0(s32 arg0, Arg *arg1)
{
    Reader rd __attribute__((aligned(16)));
    Buf buf __attribute__((aligned(16)));

    if (arg1->w[2] == 0 || arg1->w[5] == 0 || arg1->w[6] == 0) {
        return -1;
    }
    if (arg1->w[3] == 0) {
        return -1;
    }
    TextReaderCtor_15f140(&rd);
    memset(&buf, 0, 0x30);
    memset(&buf, 0, 0x54);
    buf.a.w[0] = arg1->w[0];
    buf.a.w[1] = arg1->w[1];
    buf.a.w[2] = arg1->w[2];
    buf.a.w[3] = arg1->w[3];
    buf.a.w[4] = arg1->w[4];
    buf.a.w[5] = arg1->w[5];
    buf.a.w[6] = arg1->w[6];
    buf.a.w[7] = arg1->w[7];
    buf.a.w[8] = arg1->w[8];
    buf.a.w[9] = arg1->w[9];
    buf.a.w[10] = arg1->w[10];
    buf.a.w[11] = arg1->w[11];
    buf.k8 = buf.a.w[2];
    buf.arg0 = arg0;
    buf.r = ((s32)MotionListFindSubEntry_172430(buf.a.w[3], buf.a.w[0], buf.a.w[1]));
    if (buf.r == 0) {
        return -1;
    }
    TextReaderSetKeywords_15f230(&rd, D_0044ADC0, &buf);
    TextReaderOpen_15f1b0(&rd, arg1->w[5], arg1->w[6]);
    TextReaderParseAll_15f3f0(&rd);
    return 0;
}
