#include "types.h"

typedef struct {
    char *name;
    void (*fn)();
} Tab;

typedef struct {
    s32 x0;
    s32 x4;
} Arg;

typedef struct {
    u8 *buf;
    s32 len;
    s32 pos;
    u8 pad0C[0x14 - 0xC];
    s32 ctx;
    u8 pad18[0x24 - 0x18];
    s32 bin;
    s32 count;
    Tab *tab;
    s32 extra;
} Lex;

extern s32 TextReaderReadCommandId_15e9a0(Lex *, s32 *);
extern s32 TextReaderGetChar_15eb90(Lex *, s32 *);
extern s32 TextReaderReadTextArgs_15ebc0(Lex *);
extern s32 TextReaderReadBinaryArgs_15ef70(Lex *);
extern Arg *TextReaderValueInit_15f600(Arg *);
extern void TextReaderArgsInit_15f610(Lex *, void *, s32);
extern void TextReaderStrPoolInit_15f620(Lex *, void *, s32);

s32 TextReaderParseStatement_15f430(Lex *lex, s32 call)
{
    s32 id;
    s32 tok;
    Arg arg;
    u8 big[0x4000];
    u8 small[0x300];
    s32 r;
    void (*f)();
    if (lex->tab == 0) {
        return -1;
    }
    TextReaderStrPoolInit_15f620(lex, big, 0x4000);
    for (;;) {
        TextReaderArgsInit_15f610(lex, small, 0x60);
        if (TextReaderReadCommandId_15e9a0(lex, &id) == 0) {
            return -1;
        }
        if (lex->bin != 0) goto binb;
        if (id < lex->count && id >= 0) break;
        do {
            if (TextReaderGetChar_15eb90(lex, &tok) == 0) goto next;
        } while (tok != 0x3B);
    next:;
    }
    r = TextReaderReadTextArgs_15ebc0(lex);
    if (call != 0) {
        if (lex->extra == 0) {
            { s32 k_ = id * 8; k_ = *(s32 *)((s32)&lex->tab->fn + k_); f = (void (*)())k_; }
            if (f != 0) {
                f(lex->ctx, r);
            }
        } else if (lex->tab[id].fn != 0) {
            TextReaderValueInit_15f600(&arg);
            arg.x0 = lex->extra;
            lex->tab[id].fn(lex->ctx, r, &arg);
        }
    }
    goto out;
binb:
    r = TextReaderReadBinaryArgs_15ef70(lex);
    if (id < lex->count && id >= 0 && call != 0) {
        { s32 k_ = id * 8; k_ = *(s32 *)((s32)&lex->tab->fn + k_); f = (void (*)())k_; }
        if (f != 0) f(lex->ctx, r);
    }
out:
    return id;
}
