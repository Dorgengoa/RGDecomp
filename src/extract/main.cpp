// SPDX-License-Identifier: CC0-1.0
// rg-extract command line. See docs/EXTRACT.md.
#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "extract.h"
#include "mvi.h"

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#elif defined(__APPLE__)
#include <mach-o/dyld.h>
#endif

namespace fs = std::filesystem;

namespace {

fs::path exe_dir(const fs::path& argv0) {
#ifdef _WIN32
    std::wstring buf(32768, L'\0');
    DWORD n = GetModuleFileNameW(nullptr, &buf[0], DWORD(buf.size()));
    if (n > 0 && n < buf.size()) {
        buf.resize(n);
        return fs::path(buf).parent_path();
    }
#elif defined(__APPLE__)
    char buf[4096];
    uint32_t size = sizeof buf;
    if (_NSGetExecutablePath(buf, &size) == 0) return fs::weakly_canonical(fs::path(buf)).parent_path();
#else
    std::error_code ec;
    fs::path p = fs::read_symlink("/proc/self/exe", ec);
    if (!ec) return p.parent_path();
#endif
    return fs::absolute(argv0).parent_path();
}

void usage(std::ostream& o) {
    o << "usage: rg-extract [options] <disc image .iso>\n"
         "\n"
         "Verifies a Rogue Galaxy (USA) v1.01 disc image (SCUS-97490) and unpacks its\n"
         "files into a data folder for the PC port.\n"
         "\n"
         "options:\n"
         "  -o, --out DIR        output folder (default: 'data' next to rg-extract)\n"
         "  -f, --force          replace an existing complete extraction\n"
         "  -l, --list           list the disc's files and exit (no hash check, no writes)\n"
         "  -q, --quiet          no progress line\n"
         "      --no-movies      do not write the converted movies (data/converted/MOVIE)\n"
         "      --expect-sha1 H  accept an image with SHA-1 H instead of the built-in one\n"
         "                       (for testing; the port only supports the built-in image)\n"
         "  -h, --help           this text\n"
         "\n"
         "single movie conversion (docs/MVI.md; extraction converts every movie):\n"
         "  rg-extract --convert-movie IN.MVI OUT\n"
         "                       writes OUT.mpg (MPEG-2 program stream, video only, not\n"
         "                       re-encoded) and OUT.wav (16-bit PCM, synced to the video)\n"
         "\n"
         "exit codes: 0 ok, 1 usage, 2 unreadable image, 3 wrong image, 4 output exists,\n"
         "            5 write failed or disk full, 6 malformed image\n";
}

int convert_movie(const std::vector<std::string>& args) {
    if (args.size() != 3) {
        std::cerr << "usage: rg-extract --convert-movie IN.MVI OUT\n";
        return rgx::kUsage;
    }
    fs::path in = fs::u8path(args[1]);
    fs::path out = fs::u8path(args[2]);
    std::string ext = out.extension().u8string();
    if (ext == ".mpg" || ext == ".MPG" || ext == ".wav" || ext == ".WAV") out.replace_extension();
    fs::path mpg = out, wav = out;
    mpg += ".mpg";
    wav += ".wav";
    if (!fs::exists(in)) {
        std::cerr << "error: cannot open '" << in.u8string() << "'\n";
        return rgx::kUnreadableIso;
    }
    rgx::mvi::MovieInfo mi;
    std::string err;
    if (!rgx::mvi::convert_movie(in, mpg, wav, &mi, &err)) {
        std::cerr << "error: " << in.u8string() << ": " << err << "\n";
        return err.rfind("write", 0) == 0 || err.rfind("cannot create", 0) == 0 ? rgx::kWriteFailed
                                                                                : rgx::kMalformedIso;
    }
    std::cout << in.u8string() << "\n"
              << "  video  " << mi.width << "x" << mi.height << " frame_rate_code " << mi.frame_rate_code
              << (mi.frame_rate_code == 4 ? " (30000/1001)" : mi.frame_rate_code == 5 ? " (30)" : "")
              << " aspect_code " << mi.aspect_code << " profile_level 0x" << std::hex << mi.profile_level
              << std::dec << ", " << mi.pictures << " pictures, first PTS " << mi.video_first_pts << "\n"
              << "  audio  " << mi.audio_rate << " Hz, " << mi.audio_channels << " ch, interleave "
              << mi.audio_interleave << ", " << mi.audio_frames_in << " frames in, " << mi.audio_frames_out
              << " out (shift " << mi.audio_shift_frames << "), first PTS " << mi.audio_first_pts << "\n"
              << "  packs  " << mi.packs << " (" << mi.video_packets << " video, " << mi.audio_packets
              << " audio -> padding)\n"
              << "  wrote  " << mpg.u8string() << ", " << wav.u8string() << "\n";
    return rgx::kOk;
}

int run(const std::vector<std::string>& args, const fs::path& argv0) {
    if (!args.empty() && args[0] == "--convert-movie") return convert_movie(args);
    rgx::Options opt;
    bool have_out = false;
    for (size_t i = 0; i < args.size(); ++i) {
        const std::string& a = args[i];
        auto need_value = [&](const char* name) -> const std::string* {
            if (i + 1 >= args.size()) {
                std::cerr << "error: " << name << " needs a value\n";
                return nullptr;
            }
            return &args[++i];
        };
        if (a == "-h" || a == "--help") {
            usage(std::cout);
            return rgx::kOk;
        } else if (a == "-o" || a == "--out") {
            const std::string* v = need_value("--out");
            if (!v) return rgx::kUsage;
            opt.out = fs::u8path(*v);
            have_out = true;
        } else if (a == "-f" || a == "--force") {
            opt.force = true;
        } else if (a == "-l" || a == "--list") {
            opt.list_only = true;
        } else if (a == "--no-movies") {
            opt.convert_movies = false;
        } else if (a == "-q" || a == "--quiet") {
            opt.progress = false;
        } else if (a == "--expect-sha1") {
            const std::string* v = need_value("--expect-sha1");
            if (!v) return rgx::kUsage;
            if (v->size() != 40 || v->find_first_not_of("0123456789abcdefABCDEF") != std::string::npos) {
                std::cerr << "error: --expect-sha1 needs 40 hex digits\n";
                return rgx::kUsage;
            }
            opt.expect_sha1 = *v;
        } else if (!a.empty() && a[0] == '-') {
            std::cerr << "error: unknown option '" << a << "'\n\n";
            usage(std::cerr);
            return rgx::kUsage;
        } else if (opt.iso.empty()) {
            opt.iso = fs::u8path(a);
        } else {
            std::cerr << "error: more than one image given\n";
            return rgx::kUsage;
        }
    }
    if (opt.iso.empty()) {
        usage(std::cerr);
        return rgx::kUsage;
    }
    if (!have_out) opt.out = exe_dir(argv0) / "data";
    try {
        return rgx::run_extract(opt);
    } catch (const std::exception& ex) {
        std::cerr << "\nerror: " << ex.what() << "\n";
        return rgx::kWriteFailed;
    }
}

}  // namespace

#ifdef _WIN32
int wmain(int argc, wchar_t** argv) {
    // Arguments arrive as UTF-16; carry them as UTF-8 internally.
    std::vector<std::string> args;
    for (int i = 1; i < argc; ++i) args.push_back(fs::path(argv[i]).u8string());
    return run(args, fs::path(argv[0]));
}
#else
int main(int argc, char** argv) {
    std::vector<std::string> args(argv + 1, argv + argc);
    return run(args, fs::path(argv[0]));
}
#endif
