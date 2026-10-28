/* rg-missing: ModelObjExUpdate_1b02c0 (retail MAIN 0x001B02C0, size 0x470)
 * why: update slot (+0x44) of the Character2 vtable D_00470F50 (installed by 29
 * constructors) and of the ModelObjEx vtable D_00470FB0; the snapshot has no C and
 * its data names the entry func_001B02C0.  ModelObjUpdate_1adf90, then the
 * motion-synchronised SE notes (3D volume/pan, one-shot and sustained notes,
 * tex-anim start/reset by name), then the motion event lists.
 * Callers pass (this, f32 dt) (29 x VCM(void, (void *, f32), 0x44, ..)); dt is
 * forwarded to ModelObjUpdate_1adf90 in $f12, as retail does.
 * Checked: mwcc 3.0.1b210 -O4 compiles this file to retail's 283 instructions
 * (MATCH, out/missing-staged/README.md). */
#include "types.h"
#include "vec.h"

/* MotionPlayerGetState_1729d0's output record (0x30 bytes). */
typedef struct MotionState {
    s32 id;
    void *key;
    f32 frame;
    f32 frameEnd;
    f32 step;
    u8 pad14[0x30 - 0x14];
} MotionState;

/* One motion-synchronised sound/tex-anim note (0x14 bytes). */
typedef struct SeNote {
    f32 start;
    f32 end;
    s16 dur;
    s16 type;
    s16 param;
    s16 timer;
    void *name;
} SeNote;

typedef struct SeNoteSet {
    s32 key;
    s32 id;
    s32 count;
    SeNote *notes;
} SeNoteSet;

typedef struct SeNoteNode {
    struct SeNoteNode *next;
    u8 pad4[0xC];
    SeNoteSet set;
} SeNoteNode;

typedef struct MotionList {
    u8 pad0[4];
    s32 f4;
    s32 f8;
} MotionList;

typedef struct ModelObjEx {
    u8 pad0[0x1F0];
    MotionList motion;
    u8 pad1FC[0x4F0 - 0x1FC];
    s32 seBank0;
    s32 seBank0Ofs;
    s32 seBank0On;
    s32 seBank1;
    s32 seBank2;
    s32 se3d;
    f32 seVol;
    f32 sePan;
    s32 seTimer;
    s32 seLastType;
    void *seNoteList;
    SeNoteNode *seNotes;
    f32 seNear;
    f32 seFar;
    f32 seVolMin;
    f32 seVolMax;
    f32 seVolScale;
    s32 seOfs;
    u8 pad538[0x554 - 0x538];
    s32 f554;
    u8 pad558[0x568 - 0x558];
    u8 events[1];
} ModelObjEx;

#ifndef __MWERKS__
/* port: layout checks (i686 pointers are 4 bytes, so every offset is retail's) */
#define RG_OFS(T, f, o) typedef char rg_ofs_##T##_##f[(__builtin_offsetof(T, f) == (o)) ? 1 : -1]
RG_OFS(MotionState, step, 0x10);
typedef char rg_size_MotionState[(sizeof(MotionState) == 0x30) ? 1 : -1];
typedef char rg_size_SeNote[(sizeof(SeNote) == 0x14) ? 1 : -1];
RG_OFS(SeNoteNode, set, 0x10);
RG_OFS(ModelObjEx, motion, 0x1F0);
RG_OFS(ModelObjEx, seBank0, 0x4F0);
RG_OFS(ModelObjEx, seOfs, 0x534);
RG_OFS(ModelObjEx, f554, 0x554);
RG_OFS(ModelObjEx, events, 0x568);
#endif

extern f32 D_0047D26C;

extern void ModelObjUpdate_1adf90(ModelObjEx *self, f32 dt);
extern s32 ObjGetAttachNodePos_1adec0(ModelObjEx *self, s32 node, Vec4 *out);
extern void SoundCalcDistVolPan_1b7de0(f32 *vol, f32 *pan, Vec4 *pos, f32 near, f32 far);
extern s32 MotionListGetPlayerState_1723a0(MotionList *list, s32 key, MotionState *out);
extern s32 SoundNextPlayHandle_1b81c0(void);
extern void SoundPlayScaledVolPan_1b9680(s32 bank, s32 se, s32 handle, f32 vol, f32 pan);
extern s32 SoundNoteListPushDefault_1b4da0(void *list, s32 bank, s32 se, s32 dur, s32 id);
extern void ModelObjTexAnimStartByName_1ac590(ModelObjEx *self, void *name);
extern void ModelObjTexAnimResetByName_1ac510(ModelObjEx *self, void *name);
extern void *MotionListIterNext_172400(MotionList *list, s32 *key);
extern s32 MotionPlayerGetState_1729d0(void *player, MotionState *out);
extern s32 MotionEventListDispatch_1b4960(void *events, s32 key, s32 id, void *mkey, f32 frame, f32 frameEnd);

void ModelObjExUpdate_1b02c0(ModelObjEx *self, f32 dt)
{
    s32 key;
    MotionState st;
    MotionState ps;
    Vec4 pos;
    MotionList *ml;
    SeNoteNode *node;
    SeNoteSet *set;
    SeNote *n;
    s32 i;
    s32 count;
    s32 h;
    f32 cur;
    f32 lo;
    f32 hi;
    f32 prev;
    f32 w;
    void *player;

    ModelObjUpdate_1adf90(self, dt);
    self->f554 = 0;
    if (self->seTimer > 0) {
        self->seTimer--;
    }
    self->seVol = self->seVolScale;
    self->sePan = 0.0f;
    ml = &self->motion;
    if (self->seVol < 0.0f) {
        self->seVol = 0.0f;
    }
    if (!(self->seVol <= 1.0f)) {
        self->seVol = 1.0f;
    }
    if (self->se3d != 0) {
        ObjGetAttachNodePos_1adec0(self, 0, &pos);
        SoundCalcDistVolPan_1b7de0(&self->seVol, &self->sePan, &pos, self->seNear, self->seFar);
        self->seVol = self->seVol * self->seVolScale;
        if (self->seVol < self->seVolMin) {
            self->seVol = self->seVolMin;
        }
        if (!(self->seVol <= self->seVolMax)) {
            self->seVol = self->seVolMax;
        }
    }
    for (node = self->seNotes; node != 0; node = node->next) {
        set = &node->set;
        MotionListGetPlayerState_1723a0(ml, set->key, &st);
        if (set->id != st.id) {
            continue;
        }
        count = set->count;
        i = 0;
        w = D_0047D26C * st.step;
        cur = st.frame;
        n = set->notes;
        prev = cur - st.step;
        lo = cur - w;
        hi = cur + w;
        for (; i < count; i++, n++) {
            if (n->dur > 0) {
                h = i % 31 + 1;
                if (!(cur < n->start) && cur <= n->end) {
                    if (n->type == 2 && self->seNoteList != 0) {
                        SoundNoteListPushDefault_1b4da0(self->seNoteList, self->seBank1, n->param + self->seOfs,
                                                        n->dur, h);
                    }
                    if (n->type == 3 && self->seNoteList != 0) {
                        SoundNoteListPushDefault_1b4da0(self->seNoteList, self->seBank2, n->param + self->seOfs,
                                                        n->dur, h);
                    }
                }
                n->timer = 0;
            } else {
                if (lo < n->start && !(hi <= n->start) && n->timer == 0) {
                    h = SoundNextPlayHandle_1b81c0();
                    if (n->type < 2 && self->seBank0On != 0 && !(self->seVol <= 0.0f)) {
                        if (self->seBank0Ofs >= 0) {
                            SoundPlayScaledVolPan_1b9680(self->seBank0, n->type + self->seBank0Ofs * 2, h,
                                                         self->seVol, self->sePan);
                        }
                        self->seTimer = 1;
                        self->seLastType = n->type;
                        n->timer = 6;
                    }
                    if (n->type == 2) {
                        SoundPlayScaledVolPan_1b9680(self->seBank1, n->param + self->seOfs, h, self->seVol,
                                                     self->sePan);
                        n->timer = 6;
                    }
                    if (n->type == 4) {
                        SoundPlayScaledVolPan_1b9680(self->seBank1, n->param, h, self->seVol, self->sePan);
                        n->timer = 6;
                        self->seTimer = 1;
                    }
                    if (n->type == 3) {
                        SoundPlayScaledVolPan_1b9680(self->seBank2, n->param + self->seOfs, h, self->seVol,
                                                     self->sePan);
                        n->timer = 6;
                    }
                }
                if (prev <= n->start && !(cur <= n->start) && n->type == 5 && n->name != 0) {
                    if (n->param != 0) {
                        ModelObjTexAnimStartByName_1ac590(self, n->name);
                    } else {
                        ModelObjTexAnimResetByName_1ac510(self, n->name);
                    }
                }
            }
            if (n->timer > 0) {
                n->timer--;
            }
        }
    }
    ml->f8 = ml->f4;
    for (;;) {
        player = MotionListIterNext_172400(ml, &key);
        if (player == 0) {
            break;
        }
        MotionPlayerGetState_1729d0(player, &ps);
        MotionEventListDispatch_1b4960(self->events, key, ps.id, ps.key, ps.frame, ps.frameEnd);
    }
    ml->f8 = 0;
}

#ifndef __MWERKS__
/* the snapshot's data (D_00470F50, D_00470FB0) and missing/UNBOUND.tsv spell this entry func_001B02C0 */
void func_001B02C0(ModelObjEx *self, f32 dt)
{
    ModelObjExUpdate_1b02c0(self, dt);
}
#endif
