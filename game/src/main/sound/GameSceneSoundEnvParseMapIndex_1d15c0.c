/* rgp:protos */
#define RGP_SELF_GameSceneSoundEnvParseMapIndex_1d15c0 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Ent {
    s16 id;
    s16 x2;
    s16 x4;
    s16 x6;
    s16 x8;
    s16 xA;
    s16 xC;
    s16 xE[8];
    s16 x1E;
    s16 x20;
    u8 x22;
    u8 x23;
} Ent;

typedef struct Map {
    s16 id;
    s16 a;
    s16 b;
    s16 pad;
} Map;

typedef struct Obj {
    u8 pad0[0x5E18];
    s32 count;
    Ent ent[(0xA61C - 0x5E1C) / 0x24];
    s32 nmap;
    Map map[1];
} Obj;

/*rgp*/
/*rgp*/
extern u32 strlen(const char *);
extern s32 strncmp(const char *, const char *, u32);
extern char *strncpy(char *, const char *, u32);
/*rgp*/
extern char D_0045B0F0[];

void GameSceneSoundEnvParseMapIndex_1d15c0(Obj *o, char *text, s32 len)
{
    char *cur;
    char buf[64][64] __attribute__((aligned(16)));
    char *tok[65];
    char sa[16] __attribute__((aligned(16)));
    char sb[16] __attribute__((aligned(16)));
    char *end;
    char *s;
    Ent *e;
    s32 i;
    s32 p;
    s32 k;
    char *pre;
    s32 n;
    s32 v;
    s32 a;
    s32 b;
    u32 plen;
    char *q;

    end = text + len;
    cur = text;
    for (i = 0; i < 64; i++) {
        tok[i] = buf[i];
    }
    tok[i] = 0;
    o->count = 0;
    while (cur < end) {
        cur = ((char *)TextSplitTabFields_1d2300(tok, cur, end));
        if (tok[0][0] < '0' || tok[0][0] > '9') {
            continue;
        }
        v = atoi(tok[0]);
        e = &o->ent[o->count++];
        if (v < 0) {
            return;
        }
        e->id = v;
        k = 4;
        if (tok[4][0] != 'B') {
            e->x2 = 0;
        } else {
            e->x2 = atoi(tok[4] + 3);
        }
        s = tok[5];
        if (s[0] != 'B') {
            e->x4 = 9999;
        } else {
            e->x4 = atoi(s + 3);
        }
        if (s[0] == '*') {
            e->x4 = -1;
        }
        s = tok[6];
        if (s[0] != 'F') {
            e->x6 = 9999;
        } else {
            e->x6 = atoi(s + 3);
        }
        if (s[0] == '*') {
            e->x6 = -1;
        }
        s = tok[7];
        if (s[0] != 'S') {
            e->x8 = 9999;
        } else {
            e->x8 = atoi(s + 3);
        }
        if (s[0] == '*') {
            e->x8 = -1;
        }
        pre = D_0045B0F0;
        plen = strlen(pre);
        k += 5;
        q = tok[8];
        e->xA = 0;
        if (q[0] == 'S') {
            e->xA = atoi(q + 7);
            e->xC = 0;
        } else if (strncmp(pre, q, plen) == 0) {
            e->xA = -1;
            v = 127.0f * (f32)Atof_12dee8(q + plen);
            if (v > 127) {
                v = 127;
            }
            e->xC = v;
        }
        for (i = 0; i < 8; i++) {
            e->xE[i] = -1;
        }
        for (i = 0; i < 6; i++) {
            s = tok[k++];
            if (s[0] != 'O') {
                e->xE[i] = -1;
            } else {
                e->xE[i] = atoi(s + 3);
            }
            if (s[0] == '*') {
                e->xE[0] = -1;
                break;
            }
        }
        s = tok[k];
        if (s[0] != 'E') {
            e->x1E = -1;
            e->x20 = -1;
        } else {
            strncpy(sa, s + 3, 3);
            sa[3] = 0;
            strncpy(sb, s + 7, 3);
            sb[3] = 0;
            e->x1E = atoi(sa);
            e->x20 = atoi(sb);
        }
        n = k + 6;
        s = tok[n];
        a = 0;
        b = 0;
        if (s[0] == 'R') {
            v = atoi(s + 3);
            for (n = 0; n < o->nmap; n++) {
                if (v == o->map[n].id) {
                    a = o->map[n].a;
                    b = o->map[n].b;
                    break;
                }
            }
        }
        e->x22 = a;
        e->x23 = b;
    }
}
