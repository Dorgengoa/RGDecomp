/* rgp:protos */
#define RGP_SELF_MesWinLayoutText_274e70 1
#include "port/game_protos.h"
#line 1
#include "types.h"
#pragma optimization_level 3

typedef struct {
    u8 pad0[0x193C];
    s32 x193C;                          /* 0x193C */
} Msg_00274e70;

extern s32 D_0045F200[];
extern s32 D_0045F208[];
extern char D_0045F6F8[];
extern char D_0045F700[];
extern char D_0045F710[];
extern char D_0045F718[];
extern char D_0045F730[];
extern char D_0045F738[];
extern char D_0045F740[];
extern char D_0045F750[];
extern char D_0045F758[];
extern char D_0045F760[];
extern char D_0045F768[];
extern char D_0045F770[];
extern char D_0045F778[];
extern char D_0045F780[];

extern s32 strlen(const char *);
extern s32 strncmp(const char *, const char *, s32);
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
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/

void MesWinLayoutText_274e70(Msg_00274e70 *p, const char *text)
{
    const char *s;
    s32 len;
    s32 pos;
    s16 lsp;
    s16 blank;
    char ch;
    s32 v;
    s32 k;
    s32 c;
    s32 r;
    u16 code;

    len = strlen(text);
    pos = 0;
    lsp = D_0045F208[0] + 4;
    blank = D_0045F200[0] - 1;
    while (pos < len) {
        if (strncmp(&text[pos], D_0045F710, 2) == 0) {
            pos += 2;
            while ((ch = text[pos]) != 0) {
                if (ch == '\n') {
                    break;
                }
                pos++;
            }
            pos++;
            continue;
        }
        s = &text[pos];
        if (*s == '[') {
            if (strncmp(s, D_0045F718, 5) == 0) {
                s32 n;
                pos += 5;
                n = 0;
                TextParseWideNumTag_2756a0(&text[pos], &n);
                if (n != 0) {
                    MesWinPushNumVar_275db0(p, n - 1, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                    MesWinSkipTagNum_275640(&pos, n, 2);
                    continue;
                }
            }
            if (strncmp(s, D_0045F730, 7) == 0) {
                s32 n;
                pos += 7;
                n = 0;
                TextParseNumTag_275970(&text[pos], &n);
                if (n != 0) {
                    MesWinPushNumVar_275db0(p, n - 1, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                    MesWinSkipTagNum_275640(&pos, n, 1);
                    continue;
                }
            }
            if (strncmp(s, D_0045F738, 4) == 0) {
                s32 n;
                pos += 4;
                n = 0;
                TextParseNumTag_275970(&text[pos], &n);
                if (n != 0) {
                    MesWinPushNumVar_275db0(p, n - 1, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                }
                pos += 3;
                continue;
            }
            if (strncmp(s, D_0045F740, 9) == 0) {
                s32 n;
                pos += 9;
                n = 0;
                TextParseWideNumTag_2756a0(&text[pos], &n);
                if (n != 0) {
                    MesWinLayoutItemName_2748f0(p, MesItemCodeFromIndex_2772b0(n));
                    MesWinSkipTagNum_275640(&pos, n, 2);
                    continue;
                }
            }
            if (strncmp(s, D_0045F750, 4) == 0) {
                s32 n;
                pos += 4;
                n = 0;
                TextParseNumTag_275970(&text[pos], &n);
                if (n != 0) {
                    MesWinLayoutItemName_2748f0(p, MesItemCodeFromIndex_2772b0(n));
                }
                pos += 3;
                continue;
            }
            if (strncmp(s, D_0045F758, 7) == 0) {
                s32 n;
                pos += 7;
                n = 0;
                TextParseWideNumTag_2756a0(&text[pos], &n);
                if (n != 0) {
                    MesWinLayoutStrVar_274e60(p, n - 1);
                    MesWinSkipTagNum_275640(&pos, n, 2);
                    continue;
                }
            }
            if (strncmp(s, D_0045F760, 4) == 0) {
                s32 n;
                pos += 4;
                n = 0;
                TextParseNumTag_275970(&text[pos], &n);
                if (n != 0) {
                    MesWinLayoutStrVar_274e60(p, n - 1);
                }
                pos += 3;
                continue;
            }
        }
        if (text[pos] == '<') {
            if (strncmp(&text[pos], D_0045F768, 7) == 0) {
                pos += 7;
                MesWinPushChar_2743c0(p, 0xFF07);
                continue;
            }
            if (strncmp(&text[pos], D_0045F778, 5) == 0) {
                pos += 5;
                v = (s32)(30.0f * (f32)Atof_12dee8(&text[pos]));
                if (MesWinGetCharCount_274c70(p) > 0) {
                    MesWinPushPause_275d60(p, MesWinGetCharCount_274c70(p), v);
                }
                while ((ch = text[pos]) != 0) {
                    if (ch == '>') {
                        break;
                    }
                    pos++;
                }
                pos++;
                continue;
            }
            if (strncmp(&text[pos], D_0045F6F8, 7) == 0) {
                pos += 7;
                MesWinClearName_2712c0(p);
                k = 0;
                for (;;) {
                    if (strncmp(&text[pos], D_0045F700, 8) == 0) {
                        pos += 8;
                        break;
                    }
                    MesWinSetNameShown_271390(p, 1);
                    MesWinSetNameChar_271370(p, k, text[pos]);
                    k++;
                    pos++;
                }
                continue;
            }
            if (strncmp(&text[pos], D_0045F770, 6) == 0) {
                pos += 6;
                MesWinPushChar_2743c0(p, 0xFF03);
                MesWinSetPenX_272af0(p, 0);
                MesWinSetPenY_272ac0(p, 0);
                p->x193C++;
                while ((ch = text[pos]) != 0) {
                    if (ch == '\n') {
                        break;
                    }
                    pos++;
                }
                pos++;
                continue;
            }
        }
        {
            s32 n;
            if (FontMatchSymbolTag_26ef40(&text[pos], &code, &n) != 0) {
                MesWinPushChar_2743c0(p, code);
                MesWinAddPenX_272ae0(p, FontGetCharWidth_26f4c0(p, code));
                pos += n;
                continue;
            }
        }
        {
            s32 n;
            if (FontMatchGaijiTag_26ef90(&text[pos], &code, &n) != 0) {
                MesWinPushChar_2743c0(p, code);
                MesWinAddPenX_272ae0(p, FontGetGaijiWidth_26f890(p, code));
                pos += n;
                continue;
            }
        }
        k = FontMapChar_26ed60(p, text[pos]);
        if (k == -2) {
            MesWinPushChar_2743c0(p, 0xFF00);
            MesWinSetPenX_272af0(p, 0);
            MesWinAddPenY_272ab0(p, lsp);
            MesWinAddPenY_272ab0(p, ((short)MesWinGetLineSpacing_2722e0(p, p->x193C)));
            p->x193C++;
            pos += 1;
            continue;
        }
        if (FontIsAsciiCode_26ed80(p, k) != 0) {
            MesWinPushChar_2743c0(p, k);
            MesWinAddPenX_272ae0(p, FontGetCharWidth_26f4c0(p, k));
            pos += 1;
            continue;
        }
        r = FontFindCode_26ee00(p, &text[pos]);
        if (r == -1) {
            r = FontFindCode_26ee00(p, D_0045F780);
        }
        MesWinPushChar_2743c0(p, r);
        MesWinAddPenX_272ae0(p, blank);
        pos += 2;
    }
}
