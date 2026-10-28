/* rgp:protos */
#define RGP_SELF_EventCastObjLoadInfoCfg_24b510 1
#define RGP_SELF_ListBegin 1
#define RGP_SELF_ListEnd 1
#define RGP_SELF_ListFind 1
#define RGP_SELF_ListNext 1
#include "port/game_protos.h"
#line 1
#include "types.h"

typedef struct Node { struct Node *next; s32 w4; s32 w8; s32 key; } Node;
typedef struct List { Node *head; Node *cur; s32 end; } List;
typedef struct Desc {
    s32 w0;         /* 0x00 */
    char *name;     /* 0x04 */
    s32 w8;
    s32 wC;
    s32 w10;
    s32 w14;
    s32 w18;
    s32 w1C;
    s32 w20;
    s32 w24;
    s32 w28;
    char *p2C;      /* 0x2C */
    s32 n30;        /* 0x30 */
    s32 w34;
    char *p38;      /* 0x38 */
    s32 n3C;        /* 0x3C */
    char buf40[0x20];
    char buf60[0x28];
} Desc;
typedef struct Tbl { s32 v[0xFF]; s32 n; } Tbl;

void Sprintf_1343b8(char *, void *, ...);
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
void *memcpy(void *, const void *, u32);
void *memset(void *, s32, u32);
char *strcpy(char *, const char *);
extern u8 D_0045EB20[];
extern u8 D_0045EB70[];
extern u8 D_0045EB78[];
extern s32 D_0047E7E0;

static inline s32 ListBegin(List *l) {
    if (l->cur != NULL) return -1;
    l->cur = l->head;
    l->end = 0;
    return 0;
}

static inline u8 *ListNext(List *l, s32 *key) {
    Node *n = l->cur;
    u8 *d;
    if (n == NULL) return NULL;
    *key = n->key;
    d = (u8 *)(n + 1);
    if ((l->cur = n->next) == NULL) l->end = 1;
    return d;
}

static inline void ListEnd(List *l) {
    l->cur = NULL;
    l->end = 0;
}

static inline u8 *ListFind(List *l, s32 key) {
    u8 *d;
    s32 k;
    if (ListBegin(l) != 0) return NULL;
    while ((d = ListNext(l, &k)) != NULL) {
        if (key == k) break;
    }
    ListEnd(l);
    return d;
}

#define IS_EX(x) ((x) >= 0x40 && (x) < 0x80)

s32 EventCastObjLoadInfoCfg_24b510(List *list, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 res;
    char name2[0x2C] __attribute__((aligned(16)));
    char name[0x20] __attribute__((aligned(16)));
    __attribute__((aligned(16))) unsigned char rgp_blk1[sizeof(union { char m0[0x0 + sizeof(Desc)]; char m1[0x88]; char m2[0x90]; })];
    Tbl tbl __attribute__((aligned(16)));
    s32 id;
    u8 *ent;
    u8 *sys;
    u8 *chr;
    s32 *q;
    s32 tex;
    s32 v;
    s32 i;
    s32 n;
    void *p;
    s32 obj;


    id = EventCastGetObjId_24c160(list, arg3, (int)arg2);
    ent = ListFind(list, arg3);
    if (ent == NULL) return 0;
    sys = ((u8 *)GetDrawCtxNameTable_15de40());
    if ((chr = ((u8 *)ObjRecGetLiveObject_1c4a90(arg1, id))) == NULL) return 0;
    if ((obj = ((s32)RecStackGetSlot_1c4330(arg1, arg2))) == 0) return 0;
    MemStackAlign64_14d8e0(obj);
    tex = *(s32 *)(chr + 0x4DC);
    if (tex < 0 && IS_EX(id)) {
        tex = ((s32)ObjRecDefaultTexGroupMaybe_250440(id));
    }
    if (*(s32 *)(ent + 0x44) < 0) {
        Sprintf_1343b8(name2, D_0045EB70, id);
    } else {
        Sprintf_1343b8(name2, D_0045EB70, *(s32 *)(ent + 0x44));
    }
    if (IS_EX(id)) {
        strcpy((char *)(sys + 0x1E4), name2);
    }
    if (arg6 == 0) {
        Sprintf_1343b8(name, D_0045EB20);
    } else {
        Sprintf_1343b8(name, D_0045EB78, arg6);
    }
    memset(&(*(Desc *)(rgp_blk1 + 0x0)), 0, sizeof(Desc));
    (*(Desc *)(rgp_blk1 + 0x0)).w0 = arg5;
    (*(Desc *)(rgp_blk1 + 0x0)).w14 = tex;
    (*(Desc *)(rgp_blk1 + 0x0)).n30 = 8;
    (*(Desc *)(rgp_blk1 + 0x0)).p2C = (*(Desc *)(rgp_blk1 + 0x0)).buf40;
    (*(Desc *)(rgp_blk1 + 0x0)).n3C = 8;
    (*(Desc *)(rgp_blk1 + 0x0)).p38 = (*(Desc *)(rgp_blk1 + 0x0)).buf60;
    (*(Desc *)(rgp_blk1 + 0x0)).w8 = obj;
    (*(Desc *)(rgp_blk1 + 0x0)).wC = obj;
    (*(Desc *)(rgp_blk1 + 0x0)).w10 = obj;
    (*(Desc *)(rgp_blk1 + 0x0)).name = name;
    (*(Desc *)(rgp_blk1 + 0x0)).w18 = 0;
    if (IS_EX(id)) {
        (*(Desc *)(rgp_blk1 + 0x0)).w20 = 1;
    }
    InfoCfgParseAll_1afd00(chr, &(*(Desc *)(rgp_blk1 + 0x0)));
    if (IS_EX(id)) {
        *(sys + 0x1E4) = 0;
    }
    v = ((s32)ArchiveGetFileByPath_1c2800((*(Desc *)(rgp_blk1 + 0x0)).w0, name, &res));
    if (v != 0 && (ent = ListFind(list, arg4)) != NULL) {
        i = 0xFF;
        q = tbl.v;
        for (; i > 0; i--) {
            *q++ = D_0047E7E0;
        }
        tbl.n = 0;
        MotionMixerCfgParse_24e160(v, res, &tbl);
        n = tbl.n;
        p = MemStackNew_14e1b0(n * 4, obj);
        memcpy(p, tbl.v, n * 4);
        *(void **)(ent + 0x28) = p;
        *(s32 *)(ent + 0x2C) = n;
    }
    return 1;
}
