#include "types.h"

static u8 CharIsNotSpace_15e8e0(s8 c)
{
    s32 r;

    r = 0;
    if (c == 0x20) {
        r = 1;
    }
    if (c == 0x9) {
        r = 1;
    }
    if (c == 0xA) {
        r = 1;
    }
    if (c == 0xD) {
        r = 1;
    }
    return !(r != 0);
}

typedef struct Val {
    s32 type;
    s32 val;
} Val;

typedef struct Lex {
    u8 *buf;
    s32 len;
    s32 pos;
    u8 pad0C[0x18 - 0xC];
    u32 base;
    u32 cur;
    u32 size;
} Lex;

s32 TextReaderSkipSpace_15e940(Lex *s)
{
    u8 *p;
    s32 i;

    p = s->buf;
    for (i = s->pos; i < s->len; i++) {
        if (CharIsNotSpace_15e8e0(p[i])) {
            break;
        }
    }
    s->pos = i;
    if (i >= s->len) {
        return 0;
    }
    return 1;
}

extern s32 TextReaderGetChar_15eb90(Lex *, s32 *);
extern void TextReaderUngetChar_15eb70(Lex *);
extern void TextReaderPushValue_15f640(Lex *, Val);
extern s64 Atof_12dee8(char *);
extern f32 dptofp(s64);
extern s32 atoi(const char *);
extern s32 strlen(const char *);
extern char *strcpy(char *, const char *);

s32 TextReaderReadTextArgs_15ebc0(Lex *lex)
{
    s32 tok;
    u32 cur;
    s32 tok2;
    Val v;
    char buf[0x400];
    s32 n;
    s32 more;
    s32 i;
    s32 quote;
    s32 t;
    s32 q;
    s32 bad;
    s32 nd;
    s32 j;
    char *p;
    char *e;
    char *s;
    s8 c;

    if (TextReaderSkipSpace_15e940(lex) == 0) {
        return 0;
    }
    n = 0;
    more = 1;
    while (more) {
        if (TextReaderSkipSpace_15e940(lex) == 0) {
            return n;
        }
        i = 0;
        quote = 0;
        for (;;) {
            if (TextReaderGetChar_15eb90(lex, &tok) == 0) {
                return n;
            }
            if (tok == '"') {
                quote = (u8)((quote != 0) ^ 1);
            }
            if (quote) {
                if (tok & 0x80) {
                    if (tok < 0xA1 || tok > 0xDF) {
                        buf[i] = tok;
                        i++;
                        if (TextReaderGetChar_15eb90(lex, &tok) == 0) {
                            return n;
                        }
                    }
                } else if (tok == 0x5C) {
                    if (TextReaderGetChar_15eb90(lex, &tok2) == 0) {
                        TextReaderUngetChar_15eb70(lex);
                    } else if (tok2 != '"') {
                        TextReaderUngetChar_15eb70(lex);
                    } else {
                        tok = tok2;
                    }
                }
            }
            if (quote == 0) {
                if (tok == ',') break;
                if (tok == ';') {
                    more = 0;
                    break;
                }
            }
            buf[i] = tok;
            i++;
            if (i >= 0x3FC) {
                i = 0;
            }
        }
        if (i == 0 && tok == ';') {
            goto end;
        }
        n++;
        buf[i] = 0;
        j = 0;
        t = 1;
        q = 0;
        bad = 0;
        nd = 0;
        if (buf[0] == '"') {
            q = 1;
        }
        p = &buf[(u32)i];
        e = p - 1;
        if (p[-1] == '"') {
            *e = 0;
            q++;
        }
        for (; (c = *(p = &buf[j])) != 0; j++) {
            if (q != 0) continue;
            if (q == 0 && c == '.') {
                t = 2;
            }
            if (CharIsNotSpace_15e8e0(c)) {
                if (*p != '-' && *p != '.' && (*p < '0' || *p > '9')) {
                    nd = 1;
                }
            }
            if (!CharIsNotSpace_15e8e0(*p)) {
                *p = 0;
                break;
            }
        }
        if (q == 2) {
            t = 0;
        }
        if (nd != 0 && t != 0) {
            bad = 1;
        }
        if (j == 0) {
            bad = 1;
        }
        v.type = t;
        if (bad) {
            v.val = 0;
            v.type = 0xFF;
        }
        s = buf;
        if (t == 0) {
            s = buf + 1;
            cur = lex->cur;
            if (cur + strlen(s) + 1 > lex->size + lex->base) {
                v.val = 0;
            } else {
                v.val = lex->cur;
                strcpy((char *)lex->cur, s);
                lex->cur += strlen(s) + 1;
            }
        }
        if (v.type == 1) {
            v.val = atoi(s);
        }
        if (v.type == 2) {
            *(f32 *)&v.val = dptofp(Atof_12dee8(s));
        }
        TextReaderPushValue_15f640(lex, v);
    }
end:
    return n;
}
