typedef char *va_list;
extern int D_0044A180[16], D_0044A1C0[16], D_0044A200[16], D_0044A240[16];
extern void *memset(void *, int, unsigned int);
extern void sceSdRemoteInit_122890(int);
extern int sceSdRemoteCallbackInit_122d70(int);
extern int sceSdRemote_1229e8(int, int, ...);
extern void sceSdRemoteCallbackQuit_122e70(void);
int SdRemoteInitMasterVolume_165608(int a0)
{
    int r;
    sceSdRemoteInit_122890(a0);
    r = sceSdRemoteCallbackInit_122d70(a0);
    sceSdRemote_1229e8(1, 0x8010, 0x980, 0x3FFF);
    sceSdRemote_1229e8(1, 0x8010, 0xA80, 0x3FFF);
    sceSdRemote_1229e8(1, 0x8010, 0x981, 0);
    sceSdRemote_1229e8(1, 0x8010, 0xA81, 0);
    return r;
}
#define VS(ap,l) (ap = (char *)__builtin_next_arg(l) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8))
int SdRemoteNopStubRelated_165690(void)
{
    return 0;
}
int SdRemoteQuit_165698(void)
{
    sceSdRemoteCallbackQuit_122e70();
    return 0;
}
int SoundIopSendCmdG0S2_1656b8(int a0, ...)
{
    va_list ap; int *p;
    VS(ap, a0);
    p = D_0044A180;
    memset(p, 0, 0x40);
    *p++ = 0;
    *p++ = 2;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, D_0044A180, 0x40);
}
#define VS(ap,l) (ap = (char *)__builtin_next_arg(l) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8))
int SoundIopSendCmdG0SA_165778(int a0, ...)
{
    va_list ap; int *p;
    VS(ap, a0);
    p = D_0044A180;
    memset(p, 0, 0x40);
    *p++ = 0;
    *p++ = 10;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, D_0044A180, 0x40);
}
int SoundIopSendCmdG1S0_165828(int a0, ...)
{
    va_list ap; int *p; int *buf;
    ap = (char *)__builtin_next_arg(a0) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    buf = p = D_0044A1C0;
    memset(p, 0, 0x40);
    *p++ = 0x1000000;
    *p++ = 0x0;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, buf, 0x40);
}
#define VS(ap,l) (ap = (char *)__builtin_next_arg(l) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8))
int SoundIopSendCmdG1S1_165900(int a0, ...)
{
    va_list ap; int *buf, *p;
    VS(ap, a0);
    buf = p = D_0044A1C0;
    memset(p, 0, 0x40);
    *p++ = 0x1000000;
    *p++ = 1;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, buf, 0x40);
}
int SoundIopSendCmdG1S2_1659a8(int a0, ...)
{
    va_list ap; int *p; int *buf;
    ap = (char *)__builtin_next_arg(a0) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    buf = p = D_0044A1C0;
    memset(p, 0, 0x40);
    *p++ = 0x1000000;
    *p++ = 0x2;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, buf, 0x40);
}
int SoundIopSendCmdG1S3_165a68(int a0, ...)
{
    va_list ap; int *p; int *buf;
    ap = (char *)__builtin_next_arg(a0) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    buf = p = D_0044A1C0;
    memset(p, 0, 0x40);
    *p++ = 0x1000000;
    *p++ = 0x3;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, buf, 0x40);
}
int SoundIopSendCmdG2S0_165b20(int a0, ...)
{
    va_list ap; int *p;
    ap = (char *)__builtin_next_arg(a0) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    p = D_0044A200;
    memset(p, 0, 0x40);
    *p++ = 0x2000000;
    *p++ = 0x0;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, D_0044A200, 0x40);
}
int SoundIopSendCmdG2S1_165bd0(int a0, ...)
{
    va_list ap; int *p;
    ap = (char *)__builtin_next_arg(a0) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    p = D_0044A200;
    memset(p, 0, 0x40);
    *p++ = 0x2000000;
    *p++ = 0x1;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, D_0044A200, 0x40);
}
int SoundIopSendCmdG2S2_165c70(int a0, ...)
{
    va_list ap; int *p;
    ap = (char *)__builtin_next_arg(a0) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    p = D_0044A200;
    memset(p, 0, 0x40);
    *p++ = 0x2000000;
    *p++ = 0x2;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, D_0044A200, 0x40);
}
int SoundIopSendCmdG2S3_165d28(int a0, ...)
{
    va_list ap; int *p;
    ap = (char *)__builtin_next_arg(a0) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    p = D_0044A200;
    memset(p, 0, 0x40);
    *p++ = 0x2000000;
    *p++ = 0x3;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, D_0044A200, 0x40);
}
int SoundIopSendCmdG3S0_165dc8(int a0, ...)
{
    va_list ap; int *p; int *buf;
    ap = (char *)__builtin_next_arg(a0) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    buf = p = D_0044A240;
    memset(p, 0, 0x40);
    *p++ = 0x3000000;
    *p++ = 0x0;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, buf, 0x40);
}
int SoundIopSendCmdG3S1_165e78(int a0, ...)
{
    va_list ap; int *p; int *buf;
    ap = (char *)__builtin_next_arg(a0) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    buf = p = D_0044A240;
    memset(p, 0, 0x40);
    *p++ = 0x3000000;
    *p++ = 0x1;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, buf, 0x40);
}
int SoundIopSendCmdG3S2_165f20(int a0, ...)
{
    va_list ap; int *p; int *buf;
    ap = (char *)__builtin_next_arg(a0) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    buf = p = D_0044A240;
    memset(p, 0, 0x40);
    *p++ = 0x3000000;
    *p++ = 0x2;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, buf, 0x40);
}
int SoundIopSendCmdG3S3_166020(int a0, ...)
{
    va_list ap; int *p; int *buf;
    ap = (char *)__builtin_next_arg(a0) - (__builtin_args_info(2) >= 8 ? 0 : (8 - __builtin_args_info(2)) * 8);
    buf = p = D_0044A240;
    memset(p, 0, 0x40);
    *p++ = 0x3000000;
    *p++ = 0x3;
    *p++ = a0;
    ap += 8; *p++ = ((int *)ap)[-2];
    ap += 8; *p++ = ((int *)ap)[-2];
    return sceSdRemote_1229e8(1, 0x90F0, buf, 0x40);
}
