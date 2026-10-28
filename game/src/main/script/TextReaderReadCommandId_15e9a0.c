/* rgp:protos */
#define RGP_SELF_TextReaderReadCommandId_15e9a0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node {
    struct Node *next;
    char *name;
    s32 val;
} Node;

typedef struct {
    char *name;
    s32 pad;
} Tab;

typedef struct {
    u8 *buf;
    s32 len;
    s32 pos;
    u8 pad0C[0x24 - 0xC];
    s32 bin;
    s32 count;
    Tab *tab;
    s32 pad30;
    Node **hash;
} Lex;

/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
/*rgp*/
extern s32 strcmp(const char *, const char *);

s32 TextReaderReadCommandId_15e9a0(Lex *lex, s32 *out)
{
    char buf[0x20C] __attribute__((aligned(16)));
    s32 c;
    s32 i;
    s16 v;
    Node *n;

    if (lex->bin != 0) {
        if (lex->pos >= lex->len) {
            return 0;
        }
        v = *(s16 *)(lex->buf + lex->pos);
        lex->pos += 2;
        *out = v;
        return v >= 0;
    }
    if (TextReaderSkipSpace_15e940(lex) == 0) {
        return 0;
    }
    i = 0;
    for (;;) {
        if (((unsigned char)TextReaderGetChar_15eb90(lex, &c)) == 0) {
            return 0;
        }
        if (((unsigned char)CharIsNotSpace_15e8e0((s8)c)) == 0 || c == ';') {
            if (c == ';') {
                TextReaderUngetChar_15eb70(lex);
            }
            break;
        }
        buf[i++] = c;
    }
    buf[i] = 0;
    if (buf[0] < 'A' || buf[0] > 'Z') {
        *out = -1;
        return 1;
    }
    if (lex->hash != 0) {
        for (n = lex->hash[StrHash101_15f3b0(lex, buf)]; n != 0; n = n->next) {
            if (strcmp(buf, n->name) == 0) {
                *out = n->val;
                return 1;
            }
        }
    } else {
        for (i = 0; i < lex->count; i++) {
            if (strcmp(lex->tab[i].name, buf) == 0) {
                *out = i;
                return 1;
            }
        }
    }
    *out = -1;
    return 1;
}
