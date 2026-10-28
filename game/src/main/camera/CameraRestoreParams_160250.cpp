#include "camera_cpp.h"

/* The restore twin of CameraSaveParams_1601b0: the same virtual call for the live
   parameter block, then the saved copy written back over it. */

extern "C" void CameraRestoreParams_160250(Camera *self)
{
    CamParams *p = self->getParams();

    p->a = self->saved.a;
    p->b = self->saved.b;
    p->c = self->saved.c;
    p->d = self->saved.d;
    p->e = self->saved.e;
    p->f = self->saved.f;
    p->g = self->saved.g;
    p->h = self->saved.h;
    p->i = self->saved.i;
    p->j = self->saved.j;
    p->k = self->saved.k;
}
