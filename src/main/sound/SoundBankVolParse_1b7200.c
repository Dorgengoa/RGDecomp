#include "types.h"

#define ZERO16(d) { u8 *p_ = (u8 *)(d); u32 n_ = 0x10; if (p_ != 0) while (n_) { *p_ = 0; n_--; p_++; } }

typedef struct Item { u8 pad0[8]; u8 m8; u8 pad9[3]; } Item;
typedef struct Ent { u8 pad0[0x18]; s32 n; Item *items; u8 pad20[0x18]; } Ent;
typedef struct Self {
    u8 pad0[0xC];
    u8 mC;
    u8 mD;
    u8 padE[0xA];
    Ent ents[5];
    s32 m130;
    s32 m134;
} Self;

extern void SoundSendCmd_1b6cc0(s32, s32, s32, s32);
extern u32 TextSplitFields_1b78d0(char **, u32, u32);
extern s32 atoi(const char *);
extern s32 strcmp(const char *, const char *);
extern char D_0045AB80[];
extern char D_0045AB88[];
extern char D_0045AB90[];
extern char D_0045ABA0[];
extern s32 D_00481460;
extern s32 D_00481464;
extern s32 D_00481468;
extern s32 D_0048146C;

void SoundBankVolParse_1b7200(Self *self, s32 idx, u32 pos, s32 len)
{
    char b0[0x10];
    char b1[0x40];
    char b2[0x40];
    char *tok[4];
    Ent *e;
    u32 end;
    s32 a;
    s32 b;
    s32 n;
    Item *it;

    if (idx < 0 || idx >= 5) {
        e = 0;
    } else {
        e = &self->ents[idx];
    }
    if (e == 0) {
        return;
    }
    ZERO16(tok);
    end = pos + len;
    tok[0] = b0;
    tok[1] = b1;
    tok[2] = b2;
    while (pos < end) {
        pos = TextSplitFields_1b78d0(tok, pos, end);
        if (strcmp(tok[0], D_0045AB80) == 0) {
            break;
        }
        if (strcmp(tok[0], D_0045AB88) == 0) {
            self->m130 = atoi(tok[1]);
            self->m134 = atoi(tok[2]);
            if (self->mC != 0) {
                a = self->m130;
                b = self->m134;
                if (a != D_00481460) {
                    SoundSendCmd_1b6cc0(0x22, 2, 0, a);
                }
                SoundSendCmd_1b6cc0(0x23, 2, 0, b);
                D_00481460 = a;
                D_00481468 = b;
            }
            if (self->mD != 0) {
                a = self->m130;
                b = self->m134;
                if (a != D_00481464) {
                    SoundSendCmd_1b6cc0(0x22, 2, 1, a);
                }
                SoundSendCmd_1b6cc0(0x23, 2, 1, b);
                D_00481464 = a;
                D_0048146C = b;
            }
        } else if (strcmp(tok[0], D_0045AB90) == 0 || strcmp(tok[0], D_0045ABA0) == 0) {
            a = atoi(tok[1]);
            b = atoi(tok[2]);
            if (a != D_00481464) {
                SoundSendCmd_1b6cc0(0x22, 2, 1, a);
            }
            SoundSendCmd_1b6cc0(0x23, 2, 1, b);
            D_00481464 = a;
            D_0048146C = b;
        } else {
            n = atoi(b0);
            if (n < 0 || n >= e->n) {
                it = 0;
            } else {
                it = &e->items[n];
            }
            if (it != 0) {
                it->m8 = atoi(b1);
            }
        }
    }
}
