#include "types.h"

typedef struct {
    s32 id;
    u8 pad4[0xC];
    f32 size;
} Part;

s32 ObjRecGetLiveObject_1c4a90(s32, s32);
Part *ObjFindNthAttachPoint_1addc0(s32, s32, s32);
s32 ModelGetFrame_1511f0(s32, s32);
void FrameTransformPoint_148f60(s32, f32 *, f32 *);
void FrameGetWorldPos_148f30(s32, f32 *);
f32 VecDistSq_13d360(f32 *, f32 *);
extern f32 D_0047D240;

s32 ObjFindAttachPointsInRangeMaybe_2cd960(s32 scene, s32 selfId, s32 *ids, s32 n, f32 *pos, s32 kind, s32 mode, s32 *out) {
    s32 self;
    s32 obj;
    s32 found = 0;
    s32 i;
    f32 radius = pos[3];
    s32 *idp;
    s32 j;
    Part *e;
    s32 q;
    f32 d;
    f32 dist;
    f32 v[4];
    f32 buf[4];

    self = ObjRecGetLiveObject_1c4a90(scene, selfId);
    if (self == 0) {
        return 0;
    }
    switch (mode) {
    case 0:
        e = ObjFindNthAttachPoint_1addc0(self, 1, 0);
        if (e == 0) {
            return 0;
        }
        q = ModelGetFrame_1511f0(self, e->id);
        if (q == 0) {
            return 0;
        }
        v[0] = pos[0];
        v[1] = pos[1];
        v[2] = pos[2];
        v[3] = 0.0f;
        FrameTransformPoint_148f60(q, v, v);
        break;
    case 2:
        v[0] = pos[0];
        v[1] = pos[1];
        v[2] = pos[2];
        v[3] = 0.0f;
        break;
    }
    for (i = 0; i < n; i++) {
        idp = &ids[i];
        if (selfId == *idp) {
            continue;
        }
        obj = ObjRecGetLiveObject_1c4a90(scene, *idp);
        if (obj == 0) {
            continue;
        }
        if (mode == 1) {
            e = ObjFindNthAttachPoint_1addc0(obj, 1, 0);
            if (e == 0) {
                continue;
            }
            q = ModelGetFrame_1511f0(self, e->id);
            if (q == 0) {
                continue;
            }
            v[0] = pos[0];
            v[1] = pos[1];
            v[2] = pos[2];
            v[3] = 0.0f;
            FrameTransformPoint_148f60(q, v, v);
        }
        j = 0;
        while ((e = ObjFindNthAttachPoint_1addc0(obj, kind, j++)) != 0) {
            q = ModelGetFrame_1511f0(obj, e->id);
            if (q == 0) {
                continue;
            }
            FrameGetWorldPos_148f30(q, buf);
            d = D_0047D240 * e->size;
            dist = VecDistSq_13d360(v, buf);
            if (dist < (radius + d) * (radius + d)) {
                out[found] = *idp;
                found++;
                break;
            }
        }
    }
    return found;
}
