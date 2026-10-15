#include "types.h"

typedef struct Body {
    s32 w[11];
} Body;

typedef struct S30 {
    s16 a;
    s16 b;
    Body body;
} S30;

typedef struct V4 {
    f32 x;
    f32 y;
    f32 z;
    f32 w;
} V4;

extern s32 GetActionMgr_1fdb50(void);
extern s32 CharaCanPickFrontTargetMaybe_2107c0(s32);
extern f32 CharaGetCollRadius_2386a0(s32);
extern void CharaGetPos_2388a0(s32, V4 *);
extern void CharaGetRot_2388b0(s32, V4 *);
extern s32 ActionMgrFindById_233b50(s32, s32);
extern s32 TargetFindInFrontMaybe_2d0aa0(S30 *, V4 *, f32, f32);
extern S30 *CharaGetFrontTargetRefMaybe_214a20(s32);
extern void TargetRefCtor_2e71f0(S30 *);
extern s32 TargetRefGetKind_2e7130(S30 *);
extern s32 TargetRefGetId_2e7120(S30 *);
extern f32 D_0045B080[];

s32 CharaPickFrontTargetMaybe_2d0970(s32 arg0)
{
    V4 sp70;
    V4 sp60;
    S30 s30;
    s32 p;
    S30 *q;

    p = ActionMgrFindById_233b50(GetActionMgr_1fdb50(), arg0);
    if (p == 0) {
        return -1;
    }
    if (CharaCanPickFrontTargetMaybe_2107c0(p) == 0) {
        return -1;
    }
    CharaGetPos_2388a0(p, &sp70);
    CharaGetRot_2388b0(p, &sp60);
    TargetRefCtor_2e71f0(&s30);
    if (TargetFindInFrontMaybe_2d0aa0(&s30, &sp70, sp60.y, 0.0f + CharaGetCollRadius_2386a0(p) + 1.5f * D_0045B080[0]) == 0) {
        return -1;
    }
    q = CharaGetFrontTargetRefMaybe_214a20(p);
    q->a = s30.a;
    q->b = s30.b;
    q->body = s30.body;
    if (TargetRefGetKind_2e7130(&s30) == 8) {
        return -2;
    }
    return TargetRefGetId_2e7120(&s30);
}
