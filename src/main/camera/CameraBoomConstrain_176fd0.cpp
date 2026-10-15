#include "camera_cpp.h"

/* vmC0: the boom constraint. This is the branch the town never takes -- the
   camera investigation spent a while on why -- and it is worth knowing what
   it would have done.

   It takes the horizontal vector between the camera's two boom points,
   flattens it to the XZ plane, and measures it. That distance is clamped into
   [a, b] by pushing an offset along the boom direction, and the height is
   lerped between c and d by where the distance sits in that range. A
   degenerate (zero-length) boom is forced to point along +Z at unit length
   rather than dividing by zero.

   The height parameter e is itself clamped into [g, f] -- the same clamp
   CameraLatchGoals_177310 applies, which is a useful cross-check that the parameter
   block is being read the same way in both places. */

extern "C" void VecAdd_13be20(Vec4 *out, const Vec4 *a, const Vec4 *b);  /* a + b */
extern "C" void VecSub_13be40(Vec4 *out, const Vec4 *a, const Vec4 *b);  /* a - b */
extern "C" void VecScale_13be00(Vec4 *out, const Vec4 *v, f32 scale);
extern "C" void VecNormalize_13bd90(Vec4 *out, const Vec4 *v);                 /* normalise */
extern "C" f32 VecLength_13d4a0(const Vec4 *v);                             /* length */
extern "C" void VecAddInPlace_13e070(Vec4 *acc, const Vec4 *v);                 /* acc += v */

extern "C" void CameraBoomConstrain_176fd0(Camera *self)
{
    CamParams *p;
    Vec4 boomA;
    Vec4 boomB;
    Vec4 span;
    Vec4 dir;
    Vec4 push;
    f32 dist;
    f32 t;

    if (self->latch == 0) {
        return;
    }

    p = self->getParams();
    VecAdd_13be20(&self->eye, &self->base, &self->offset);

    self->getBoomA(&boomA);
    self->getBoomB(&boomB);

    VecSub_13be40(&span, &boomA, &boomB);
    span.y = 0.0f;
    VecNormalize_13bd90(&dir, &span);

    VEC4_ZERO(push);

    dist = VecLength_13d4a0(&span);
    if (dist <= 0.0f) {
        span.z = 1.0f;
        dist = 1.0f;
        dir.z = 1.0f;
    }

    if (dist < p->a) {
        VecScale_13be00(&push, &dir, dist - p->a);
    }
    if (dist > p->b) {
        VecScale_13be00(&push, &dir, dist - p->b);
    }

    if (p->e < p->g) {
        p->e = p->g;
    }
    if (p->e > p->f) {
        p->e = p->f;
    }

    t = (dist - p->a) / (p->b - p->a);
    push.y = p->c + t * (p->d - p->c);

    boomB.y = boomA.y + p->e;
    VecAddInPlace_13e070(&boomB, &push);
    self->at = boomB;
}
