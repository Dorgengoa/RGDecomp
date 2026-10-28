// SPDX-License-Identifier: CC0-1.0
// ddcap: grab a screen rectangle through DXGI Desktop Duplication (the composed image the
// monitor shows, flip-model / Vulkan swapchains included, which GDI screen grabs and
// PrintWindow return black for; docs/NATIVE-VULKAN.md "FPS counter capture").
//
//   ddcap X0 Y0 X1 Y1 OUT.bmp [TIMEOUT_MS]
//
// Coordinates are physical desktop pixels (a per-monitor DPI-aware caller: wincap.py --dd).
// Waits up to TIMEOUT_MS (default 3000) for a frame in which the desktop image was updated,
// writes a 24-bit BMP.  Exit 0, 1 on failure (message on stderr).
// Build: tools/native/ddcap_build.cmd [OUT.exe] (clang-cl, x64: Desktop Duplication is not
// reliably available to WOW64 processes; default out/tools/ddcap.exe).
#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <d3d11.h>
#include <dxgi1_2.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define FAIL(...) do { fprintf(stderr, "ddcap: " __VA_ARGS__); fputc('\n', stderr); return 1; } while (0)

static int write_bmp(const char *path, const std::vector<unsigned char> &bgr, int w, int h)
{
    int stride = (w * 3 + 3) & ~3;
    BITMAPFILEHEADER fh = {};
    BITMAPINFOHEADER ih = {};
    fh.bfType = 0x4D42;
    fh.bfOffBits = sizeof fh + sizeof ih;
    fh.bfSize = fh.bfOffBits + stride * h;
    ih.biSize = sizeof ih;
    ih.biWidth = w;
    ih.biHeight = h;   // bottom-up
    ih.biPlanes = 1;
    ih.biBitCount = 24;
    FILE *f = fopen(path, "wb");
    if (!f) return -1;
    fwrite(&fh, sizeof fh, 1, f);
    fwrite(&ih, sizeof ih, 1, f);
    std::vector<unsigned char> row(stride, 0);
    for (int y = h - 1; y >= 0; y--) {
        memcpy(row.data(), &bgr[(size_t)y * w * 3], (size_t)w * 3);
        fwrite(row.data(), 1, stride, f);
    }
    fclose(f);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 6) FAIL("usage: ddcap X0 Y0 X1 Y1 OUT.bmp [TIMEOUT_MS]");
    SetProcessDPIAware();
    LONG x0 = atol(argv[1]), y0 = atol(argv[2]), x1 = atol(argv[3]), y1 = atol(argv[4]);
    DWORD timeout = argc > 6 ? (DWORD)atol(argv[6]) : 3000;
    if (x1 <= x0 || y1 <= y0) FAIL("empty rectangle");
    IDXGIFactory1 *fac = nullptr;
    if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void **)&fac))) FAIL("CreateDXGIFactory1");
    IDXGIAdapter1 *ad = nullptr;
    IDXGIOutput *out = nullptr;
    DXGI_OUTPUT_DESC od = {};
    for (UINT a = 0; !out && fac->EnumAdapters1(a, &ad) != DXGI_ERROR_NOT_FOUND; a++) {
        IDXGIOutput *o = nullptr;
        for (UINT i = 0; ad->EnumOutputs(i, &o) != DXGI_ERROR_NOT_FOUND; i++) {
            o->GetDesc(&od);
            RECT r = od.DesktopCoordinates;
            if (x0 >= r.left && y0 >= r.top && x0 < r.right && y0 < r.bottom) { out = o; break; }
            o->Release();
        }
        if (!out) { ad->Release(); ad = nullptr; }
    }
    if (!out) FAIL("no output contains (%ld, %ld)", x0, y0);
    RECT dr = od.DesktopCoordinates;
    if (x1 > dr.right) x1 = dr.right;
    if (y1 > dr.bottom) y1 = dr.bottom;
    ID3D11Device *dev = nullptr;
    ID3D11DeviceContext *ctx = nullptr;
    if (FAILED(D3D11CreateDevice(ad, D3D_DRIVER_TYPE_UNKNOWN, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &dev, nullptr, &ctx)))
        FAIL("D3D11CreateDevice");
    IDXGIOutput1 *o1 = nullptr;
    if (FAILED(out->QueryInterface(__uuidof(IDXGIOutput1), (void **)&o1))) FAIL("IDXGIOutput1");
    IDXGIOutputDuplication *dup = nullptr;
    HRESULT hr = o1->DuplicateOutput(dev, &dup);
    if (FAILED(hr)) FAIL("DuplicateOutput 0x%08lx (locked desktop / secure desktop / another duplication?)", (unsigned long)hr);
    ID3D11Texture2D *frame = nullptr;
    DWORD t0 = GetTickCount();
    for (;;) {
        DXGI_OUTDUPL_FRAME_INFO fi = {};
        IDXGIResource *res = nullptr;
        hr = dup->AcquireNextFrame(250, &fi, &res);
        if (hr == DXGI_ERROR_WAIT_TIMEOUT) {
            if (GetTickCount() - t0 > timeout) FAIL("no desktop update within %lu ms", (unsigned long)timeout);
            continue;
        }
        if (FAILED(hr)) FAIL("AcquireNextFrame 0x%08lx", (unsigned long)hr);
        if (fi.LastPresentTime.QuadPart != 0) {
            res->QueryInterface(__uuidof(ID3D11Texture2D), (void **)&frame);
            res->Release();
            break;   // released after the copy
        }
        res->Release();
        dup->ReleaseFrame();
        if (GetTickCount() - t0 > timeout) FAIL("no presented frame within %lu ms", (unsigned long)timeout);
    }
    D3D11_TEXTURE2D_DESC td;
    frame->GetDesc(&td);
    td.Usage = D3D11_USAGE_STAGING;
    td.BindFlags = 0;
    td.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    td.MiscFlags = 0;
    ID3D11Texture2D *stg = nullptr;
    if (FAILED(dev->CreateTexture2D(&td, nullptr, &stg))) FAIL("staging texture");
    ctx->CopyResource(stg, frame);
    frame->Release();
    dup->ReleaseFrame();
    D3D11_MAPPED_SUBRESOURCE m;
    if (FAILED(ctx->Map(stg, 0, D3D11_MAP_READ, 0, &m))) FAIL("Map");
    // the duplicated image is in the output's (unrotated) space: offsets from its desktop origin
    int w = (int)(x1 - x0), h = (int)(y1 - y0);
    std::vector<unsigned char> bgr((size_t)w * h * 3);
    for (int y = 0; y < h; y++) {
        const unsigned char *s = (const unsigned char *)m.pData + (size_t)(y0 - dr.top + y) * m.RowPitch + (size_t)(x0 - dr.left) * 4;
        for (int x = 0; x < w; x++) {
            bgr[((size_t)y * w + x) * 3 + 0] = s[x * 4 + 0];
            bgr[((size_t)y * w + x) * 3 + 1] = s[x * 4 + 1];
            bgr[((size_t)y * w + x) * 3 + 2] = s[x * 4 + 2];
        }
    }
    ctx->Unmap(stg, 0);
    if (write_bmp(argv[5], bgr, w, h)) FAIL("cannot write %s", argv[5]);
    printf("ddcap: %s %dx%d (output %ls, desktop format %u)\n", argv[5], w, h, od.DeviceName, (unsigned)td.Format);
    return 0;
}
