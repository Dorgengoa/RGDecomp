/* rgp:protos */
#define RGP_SELF_MesWinMeasureText_272b80 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct {
    u8 pad0[0x56];
    s16 width;                          /* 0x56 */
    u8 pad58[0x195D - 0x58];
    char names[1][0x20];                /* 0x195D */
} Msg_00272b80;

#define MSG_VAL(p, n) (*(s32 *)((u8 *)(p) + 0x1B9C + (n) * 4))
#define MSG_1C1C(p) (*(s8 *)((u8 *)(p) + 0x1C1C))
#define MSG_1C1D(p) (*(s8 *)((u8 *)(p) + 0x1C1D))

extern s32 D_0045F200[];
extern s32 D_0045F208[];
extern char D_0045F6F8[];
extern char D_0045F700[];
extern char D_0045F710[];
extern char D_0045F718[];
extern char D_0045F720[];
extern char D_0045F728[];
extern char D_0045F730[];
extern char D_0045F738[];
extern char D_0045F740[];
extern char D_0045F750[];
extern char D_0045F758[];
extern char D_0045F760[];
extern char D_0045F768[];
extern char D_0045F770[];

extern char *strcpy(char *, const char *);
extern s32 strlen(const char *);
extern s32 strncmp(const char *, const char *, s32);
extern s32 Sprintf_1343b8(char *, const char *, ...);
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesWinMeasureText_272b80(Msg_00272b80 *p, const char *text)
{
    char buf[0x324] __attribute__((aligned(16)));
    s32 x;
    s32 line;
    s32 col;
    s32 len;
    s32 pos;
    s32 lh;
    s16 lsp;
    s16 blank;
    s32 w;
    s32 v;
    s32 c;
    char ch;
    u16 code;

    strcpy(buf, text);
    p->width = 0;
    x = 0;
    line = 0;
    col = 0;
    len = strlen(buf);
    pos = 0;
    lh = D_0045F208[0] + 4;
    lsp = lh;
    blank = D_0045F200[0] - 1;
    while (pos < len) {
        if (strncmp(&buf[pos], D_0045F6F8, 7) == 0) {
            pos += 7;
            while (pos < len) {
                if (strncmp(&buf[pos], D_0045F700, 8) == 0) {
                    break;
                }
                pos++;
            }
            continue;
        }
        if (strncmp(&buf[pos], D_0045F710, 2) == 0) {
            pos += 2;
            while ((ch = *(char *)((u32)&buf[pos])) != 0) {
                if (ch == '\n') {
                    break;
                }
                pos++;
            }
            pos++;
            continue;
        }
        if (buf[pos] == '[') {
            if (strncmp(&buf[pos], D_0045F718, 5) == 0) {
                s32 n;
                pos += 5;
                n = 0;
                TextParseWideNumTag_2756a0(&buf[pos], &n);
                if (n != 0) {
                    v = MSG_VAL(p, n);
                    if (MSG_1C1D(p) != 0 || v != 0) {
                        char tmp[0x80] __attribute__((aligned(16)));
                        if (MSG_1C1C(p) != 0 && v > 0) {
                            Sprintf_1343b8(tmp, D_0045F720, v);
                        } else {
                            Sprintf_1343b8(tmp, D_0045F728, v);
                        }
                        w = strlen(tmp) - 1;
                        MesWinAddLineWidth_273c20(p, line, (long long)(w * FontGetDigitWidth_26f5a0()));
                    }
                    MesWinSkipTagNum_275640(&pos, n, 2);
                    continue;
                }
            }
            if (strncmp(&buf[pos], D_0045F730, 7) == 0) {
                s32 n;
                pos += 7;
                n = 0;
                TextParseNumTag_275970(&buf[pos], &n);
                if (n != 0) {
                    v = MSG_VAL(p, n);
                    if (MSG_1C1D(p) != 0 || v != 0) {
                        char tmp[0x80] __attribute__((aligned(16)));
                        if (MSG_1C1C(p) != 0 && v > 0) {
                            Sprintf_1343b8(tmp, D_0045F720, v);
                        } else {
                            Sprintf_1343b8(tmp, D_0045F728, v);
                        }
                        w = strlen(tmp) - 1;
                        MesWinAddLineWidth_273c20(p, line, (long long)(w * FontGetDigitWidth_26f5a0()));
                    }
                    MesWinSkipTagNum_275640(&pos, n, 1);
                    continue;
                }
            }
            if (strncmp(&buf[pos], D_0045F738, 4) == 0) {
                s32 n;
                pos += 4;
                n = 0;
                TextParseNumTag_275970(&buf[pos], &n);
                if (n != 0) {
                    v = MSG_VAL(p, n);
                    if (MSG_1C1D(p) != 0 || v != 0) {
                        char tmp[0x80] __attribute__((aligned(16)));
                        if (MSG_1C1C(p) != 0 && v > 0) {
                            Sprintf_1343b8(tmp, D_0045F720, v);
                        } else {
                            Sprintf_1343b8(tmp, D_0045F728, v);
                        }
                        w = strlen(tmp) - 1;
                        MesWinAddLineWidth_273c20(p, line, (long long)(w * FontGetDigitWidth_26f5a0()));
                    }
                }
                pos += 3;
                continue;
            }
            if (strncmp(&buf[pos], D_0045F740, 9) == 0) {
                s32 n;
                pos += 9;
                n = 0;
                TextParseWideNumTag_2756a0(&buf[pos], &n);
                if (n != 0) {
                    s32 r = MesWinMeasureItemSlot_2746b0(p, n);
                    if (r != 0) {
                        MesWinAddLineWidth_273c20(p, line, (long long)(r));
                    }
                    MesWinSkipTagNum_275640(&pos, n, 2);
                    continue;
                }
            }
            if (strncmp(&buf[pos], D_0045F750, 4) == 0) {
                s32 n;
                pos += 4;
                n = 0;
                TextParseNumTag_275970(&buf[pos], &n);
                if (n != 0) {
                    s32 r = MesWinMeasureItemSlot_2746b0(p, n);
                    if (r != 0) {
                        MesWinAddLineWidth_273c20(p, line, (long long)(r));
                    }
                }
                pos += 3;
                continue;
            }
            if (strncmp(&buf[pos], D_0045F758, 7) == 0) {
                s32 n;
                pos += 7;
                n = 0;
                TextParseWideNumTag_2756a0(&buf[pos], &n);
                if (n != 0) {
                    MesWinAddLineWidth_273c20(p, line, (long long)(FontMeasureStringWidth_2773d0(p, p->names[n - 1])));
                    MesWinSkipTagNum_275640(&pos, n, 2);
                    continue;
                }
            }
            if (strncmp(&buf[pos], D_0045F760, 4) == 0) {
                s32 n;
                pos += 4;
                n = 0;
                TextParseNumTag_275970(&buf[pos], &n);
                if (n != 0) {
                    MesWinAddLineWidth_273c20(p, line, (long long)(FontMeasureStringWidth_2773d0(p, p->names[n - 1])));
                }
                pos += 3;
                continue;
            }
        }
        if (strncmp(&buf[pos], D_0045F768, 7) == 0) {
            pos += 7;
            continue;
        }
        {
            s32 n;
            if (FontMatchSymbolTag_26ef40(&buf[pos], &code, &n) != 0) {
                MesWinAddLineWidth_273c20(p, line, (long long)(FontGetCharWidth_26f4c0(p, code)));
                pos += n;
                continue;
            }
        }
        {
            s32 n;
            if (FontMatchGaijiTag_26ef90(&buf[pos], &code, &n) != 0) {
                MesWinAddLineWidth_273c20(p, line, (long long)(FontGetGaijiWidth_26f890(p, code)));
                pos += n;
                continue;
            }
        }
        if (buf[pos] == '\n') {
            pos++;
            x += lsp;
            x += ((short)MesWinGetLineSpacing_2722e0(p, line));
            if (p->width < x) {
                p->width = x;
            }
            line++;
            MesWinSetLineWidth_273be0(p, line, 0);
            continue;
        }
        if (strncmp(&buf[pos], D_0045F770, 6) == 0) {
            pos += 6;
            MesWinSetPageLineCount_273b90(p, line, col);
            line++;
            col++;
            MesWinSetLineWidth_273be0(p, line, 0);
            x = 0;
            while ((ch = *(char *)((u32)&buf[pos])) != 0) {
                if (ch == '\n') {
                    break;
                }
                pos++;
            }
            pos++;
            continue;
        }
        c = FontMapChar_26ed60(p, buf[pos]);
        if (FontIsAsciiCode_26ed80(p, c) != 0) {
            MesWinAddLineWidth_273c20(p, line, (long long)(FontGetCharWidth_26f4c0(p, c)));
            pos += 1;
        } else {
            MesWinAddLineWidth_273c20(p, line, (long long)(blank));
            pos += 2;
        }
    }
    MesWinSetPageLineCount_273b90(p, line - 1, col);
    p->width += (s16)lh;
    MesWinCalcMaxLineWidth_273b00(p);
    MesWinCalcLineCentering_273a10(p);
}
