#pragma inline_depth(10)
#include "types.h"

typedef struct Node {
    struct Node *next;
} Node;

typedef struct List {
    Node *head;
    Node *cur;
    s32 end;
} List;

typedef struct Ctx {
    s32 p0;
    u8 *p4;
} Ctx;

extern void LoaderTick_1ccc30(void *);
extern s32 LoaderGetStatus_1cd4f0(void *, s32);
extern s32 LoaderIsIdle_1cd5b0(void *);
extern s32 LoaderCountQueued_1cd620(void *);
extern void *GetLoaderMgr_1f59d0(void);
extern void ScriptSetRefInt_249030(s32, s32);
extern Ctx *gEventContext;

static inline s32 List_Begin(List *l)
{
    if (l->cur != 0) {
        return -1;
    }
    l->cur = l->head;
    l->end = 0;
    return 0;
}

static inline u8 *List_Next(List *l)
{
    Node *n = l->cur;
    u8 *r;
    if (n == 0) {
        return 0;
    }
    r = (u8 *)n + 0x10;
    l->cur = n->next;
    if (l->cur == 0) {
        l->end = 1;
    }
    return r;
}

static inline void List_End(List *l)
{
    l->cur = 0;
    l->end = 0;
}

s32 EvCmdCastLoadStatus_248b50(s64 *out, s32 n)
{
    s32 cnt;
    s32 a;
    s32 b;
    s32 c;
    s32 res;
    void *g;
    s32 flag;
    s32 m;

    if (n <= 0) {
        return 0;
    }
    cnt = 0;
    a = 0;
    b = 0;
    c = 0;
    res = 0;
    g = GetLoaderMgr_1f59d0();
    LoaderTick_1ccc30(g);
    m = LoaderCountQueued_1cd620(g);
    flag = LoaderIsIdle_1cd5b0(g) & 0xFF;
    if (m > 0) {
        List *l;
        u8 *p;
        l = (List *)(gEventContext->p4 + 0x60);
        if (List_Begin(l) == 0) {
            while ((p = List_Next(l)) != 0) {
                s32 id = *(s32 *)(p + 0x24);
                if (id >= 0) {
                    s32 r = LoaderGetStatus_1cd4f0(g, id);
                    cnt++;
                    if (r == -1) {
                        c++;
                    } else if (r == 0) {
                        b++;
                    } else if (r == 1) {
                        a++;
                    }
                }
            }
            List_End(l);
        }
        if (cnt > 0) {
        if (cnt == a) {
            res = 1;
        } else if (cnt == c) {
            res = 9;
        } else if (cnt == a + c) {
            res = 2;
        } else if (flag) {
            if (a > 0) {
                if (c > 0) {
                    res = 4;
                } else {
                    res = 3;
                }
            } else if (c > 0) {
                res = 6;
            } else {
                res = 5;
            }
        } else if (c > 0) {
            res = 8;
        } else {
            res = 7;
        }
        }
    }
    ScriptSetRefInt_249030((s32)out++, res);
    if (n >= 2) {
        ScriptSetRefInt_249030((s32)out++, a);
    }
    if (n >= 3) {
        ScriptSetRefInt_249030((s32)out++, b);
    }
    if (n >= 4) {
        ScriptSetRefInt_249030((s32)out++, c);
    }
    if (n >= 5) {
        ScriptSetRefInt_249030((s32)out, flag & 0xFF);
    }
    return 1;
}
