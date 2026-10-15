#include "types.h"
#pragma opt_propagation off

typedef struct {
    void *buf;
    s32 m4;
    s32 m8;
    s32 mC;
    s32 m10;
} Res;

class Node {
public:
    Node *next;
    Node *prev;
    s32 m8;
    s32 mC;
    Res r;
    virtual void init();
};

extern "C" {
extern void *MemStackAllocAligned64_14da10(s32, s32);
extern Node *MemStackNew_14e230(s32, s32);
extern s32 TexAnimeTableLoadFromImg_159340(s32, void *, s32);
extern void NameTableRegisterImArchiveFwd_1594c0(s32, void *, s32, s32);
extern s32 GetDrawCtxNameTable_15de40(void);
extern s32 SlotGetInt_15f720(s32);
extern s32 VariantGetInt_15f780(void);
extern void *ArchiveGetFileData_181dd0(s32, s32, s32 *);
extern void ModelObjTexAnimBuildNameIndexMaybe_1abcd0(Res *, s32, s32);
extern void ModelObjTexAnimRemoveById_1ac610(u8 *, s32);
extern void *memcpy(void *, const void *, s32);
extern u8 D_00470F40[];
extern s32 D_0049D390[];
extern s32 D_0049D3A0[];
extern s32 D_0049D3A4[];
extern u8 *D_0049D418[];
}

extern "C" s32 InfoCfgImgCmd_1aa390(s32 arg0)
{
    u8 *ctx;
    s32 heap;
    s32 tag;
    Node *p;
    s32 h;
    s32 res;
    s32 size;
    void *data;
    Res *q;
    Node *n;

    ctx = D_0049D418[0];
    heap = D_0049D3A0[0];
    res = D_0049D390[0];
    if (heap == 0 || ctx == 0) {
        return 0;
    }
    arg0 += 8;
    tag = VariantGetInt_15f780();
    data = ArchiveGetFileData_181dd0(res, SlotGetInt_15f720(arg0), &size);
    if (data == 0) {
        return 0;
    }
    ModelObjTexAnimRemoveById_1ac610(ctx, tag);
    n = MemStackNew_14e230(0x28, heap);
    if (n != 0) {
        *(u8 **)((u8 *)n + 0x24) = D_00470F40;
        n->r.buf = 0;
        n->r.m4 = 0;
        n->r.mC = 0;
        n->r.m10 = 0;
        n->r.m8 = 1;
        n->init();
    }
    if (n == 0) {
        q = 0;
    } else {
        n->r.buf = 0;
        n->r.m4 = 0;
        n->r.mC = 0;
        n->r.m10 = 0;
        n->r.m8 = 1;
        n->mC = tag;
        q = &n->r;
        if (*(Node **)(ctx + 0x220) == 0) {
            *(Node **)(ctx + 0x220) = n;
        } else {
            p = *(Node **)(ctx + 0x220);
            while (p != 0) {
                if (p->next == 0) {
                    break;
                }
                p = p->next;
            }
            p->next = n;
            if (n != 0) {
                n->prev = p;
            }
        }
    }
    if (q == 0) {
        return 0;
    }
    {
        void *b = MemStackAllocAligned64_14da10(heap, size / 16 + 1);
        q->buf = b;
        if (b == 0) {
            return 0;
        }
        memcpy(b, data, size);
    }
    h = GetDrawCtxNameTable_15de40();
    NameTableRegisterImArchiveFwd_1594c0(h, q->buf, D_0049D3A4[0], 0);
    q->m4 = TexAnimeTableLoadFromImg_159340(h, q->buf, heap);
    *(s32 *)(ctx + 0x4DC) = D_0049D3A4[0];
    ModelObjTexAnimBuildNameIndexMaybe_1abcd0(q, *(volatile s32 *)&D_0049D3A4[0], heap);
    return 1;
}
