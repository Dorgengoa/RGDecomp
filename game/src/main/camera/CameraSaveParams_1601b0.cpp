#include "camera_cpp.h"

/* Save the live parameter block into the camera's copy at +0x130.
   Written against the C++ class so the vtable call goes through $t9 the way
   retail's does -- see include/camera_cpp.h. */

extern "C" void CameraSaveParams_1601b0(Camera *self)
{
    CamParams *p = self->getParams();

    self->saved.a = p->a;
    self->saved.b = p->b;
    self->saved.c = p->c;
    self->saved.d = p->d;
    self->saved.e = p->e;
    self->saved.f = p->f;
    self->saved.g = p->g;
    self->saved.h = p->h;
    self->saved.i = p->i;
    self->saved.j = p->j;
    self->saved.k = p->k;
}
