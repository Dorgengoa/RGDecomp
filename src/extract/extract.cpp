// SPDX-License-Identifier: CC0-1.0
#include "extract.h"

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <future>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <system_error>
#include <vector>

#include "hash.h"
#include "iso9660.h"
#include "mvi.h"

namespace fs = std::filesystem;

namespace rgx {

// Established 2026-10-11 by hashing the project's own copy of the disc image; it equals the
// Redump entry for SCUS-97490 v1.01 (redump.org/disc/6567: 3402208 sectors, layer break
// 1646704, SHA-1 below). See docs/EXTRACT.md.
const AcceptedImage kAcceptedImage = {
    "Rogue Galaxy (USA)",
    "SCUS_974.90",
    "1.01",
    6967721984ull,
    "87377e721be58e8b6a5a7501721563500d237df7",
};

namespace {

const char* kPartialMarker = ".rg-extract-partial";
const char* kManifestName = "MANIFEST.tsv";
constexpr size_t kChunk = 8u << 20;

std::string human_bytes(uint64_t n) {
    std::ostringstream s;
    s << std::fixed << std::setprecision(2);
    if (n >= (1ull << 30))
        s << double(n) / double(1ull << 30) << " GiB";
    else if (n >= (1ull << 20))
        s << double(n) / double(1ull << 20) << " MiB";
    else if (n >= 1024)
        s << double(n) / 1024.0 << " KiB";
    else
        s << n << " B";
    return s.str();
}

std::string to_lower(std::string s) {
    for (auto& c : s) c = char(std::tolower(static_cast<unsigned char>(c)));
    return s;
}

std::string trim(std::string s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";
    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

std::FILE* open_write(const fs::path& p) {
#ifdef _WIN32
    return _wfopen(p.c_str(), L"wb");
#else
    return std::fopen(p.c_str(), "wb");
#endif
}

// "SCUS_974.90" -> "SCUS-97490"
std::string serial_from_boot_name(const std::string& name) {
    std::string s;
    for (char c : name) {
        if (c == '_')
            s += '-';
        else if (c != '.')
            s += char(std::toupper(static_cast<unsigned char>(c)));
    }
    return s;
}

struct Copy {
    int layer = 0;
    std::vector<Extent> extents;
    Sha256 hash;
    std::string sha256;
};

struct Output {
    std::string path;  // "BIN/FACTORY.BIN"
    uint64_t size = 0;
    std::vector<Copy> copies;  // [0] is the one written; others must match it
    std::FILE* fp = nullptr;
    uint64_t written = 0;
};

struct Target {
    uint64_t start = 0, end = 0;  // byte range in the image
    size_t out = 0, copy = 0;
};

struct Ctx {
    const Options& opt;
    std::ostream& log;
    std::ostream& err;
};

// Removes the partial directory on every exit path that doesn't commit it.
struct PartialGuard {
    fs::path dir;
    std::vector<Output>* outputs = nullptr;
    bool armed = false;
    ~PartialGuard() {
        if (outputs)
            for (auto& o : *outputs)
                if (o.fp) {
                    std::fclose(o.fp);
                    o.fp = nullptr;
                }
        if (armed) {
            std::error_code ec;
            fs::remove_all(dir, ec);
        }
    }
};

// Other Rogue Galaxy releases, so a wrong disc can be named (serials from Redump).
struct KnownRelease {
    const char* serial;
    const char* name;
};
const KnownRelease kKnownReleases[] = {
    {"SCUS-97490", "Rogue Galaxy (USA)"},
    {"SCUS-97572", "Rogue Galaxy demo (USA)"},
    {"SCES-54552", "Rogue Galaxy (Europe)"},
    {"SCPS-15102", "Rogue Galaxy (Japan)"},
    {"SCKA-30005", "Rogue Galaxy (Korea)"},
    {"SCPS-17013", "Rogue Galaxy: Director's Cut (Japan)"},
};

std::string describe_identity(const DiscIdentity& id) {
    if (id.serial.empty()) return "an image without a PS2 SYSTEM.CNF (not a PS2 game disc?)";
    std::string s = id.serial;
    for (const KnownRelease& k : kKnownReleases)
        if (id.serial == k.serial) s = std::string(k.name) + ", " + s;
    if (!id.region.empty()) s += " (" + id.region + ")";
    if (!id.version.empty()) s += " version " + id.version;
    return s;
}

int reject(Ctx& c, const DiscIdentity& id, const std::string& detail) {
    const AcceptedImage& a = kAcceptedImage;
    std::string want = serial_from_boot_name(a.serial);
    c.err << "error: wrong disc image.\n";
    if (!id.serial.empty() && id.serial != want) {
        c.err << "  This image is " << describe_identity(id) << ".\n";
    } else if (!id.serial.empty() && id.version != a.version) {
        c.err << "  This image is " << describe_identity(id) << ", a different release of the game.\n";
    } else if (!id.serial.empty()) {
        c.err << "  This image identifies as " << describe_identity(id)
              << ", but it is not a clean copy of that disc (a bad or modified dump).\n";
    } else {
        c.err << "  This is " << describe_identity(id) << ".\n";
    }
    c.err << "  " << detail << "\n";
    c.err << "  rg-extract needs " << a.title << ", " << want << ", VER " << a.version << " (" << a.size
          << " bytes, SHA-1 " << a.sha1 << ").\n";
    return kWrongImage;
}

// One converted output (docs/EXTRACT.md, "MANIFEST.tsv"): written under <out>/converted/.
struct Converted {
    std::string path;    // "converted/MOVIE/00/RUSH.mpg"
    std::string source;  // "MOVIE/00/RUSH.MVI"
    std::string kind;    // "movie-video" or "movie-audio"
    uint64_t size = 0;
    std::string sha256;
};

// "MOVIE/<dir>/<name>.MVI" (any case) -> "converted/MOVIE/<dir>/<name>", else "".
std::string movie_output_stem(const std::string& path) {
    std::string low = to_lower(path);
    if (low.size() < 11 || low.compare(0, 6, "movie/") != 0 || low.compare(low.size() - 4, 4, ".mvi") != 0)
        return "";
    return "converted/" + path.substr(0, path.size() - 4);
}

bool sha256_file(const fs::path& p, uint64_t* size, std::string* hex) {
#ifdef _WIN32
    std::FILE* f = _wfopen(p.c_str(), L"rb");
#else
    std::FILE* f = std::fopen(p.c_str(), "rb");
#endif
    if (!f) return false;
    std::vector<uint8_t> buf(1 << 20);
    Sha256 h;
    uint64_t n = 0;
    size_t got;
    while ((got = std::fread(buf.data(), 1, buf.size(), f)) > 0) {
        h.update(buf.data(), got);
        n += got;
    }
    bool ok = !std::ferror(f);
    std::fclose(f);
    *size = n;
    *hex = h.finish_hex();
    return ok;
}

bool is_dir_empty(const fs::path& p) {
    std::error_code ec;
    return fs::directory_iterator(p, ec) == fs::directory_iterator();
}

}  // namespace

DiscIdentity parse_system_cnf(const std::string& text) {
    DiscIdentity id;
    std::istringstream in(text);
    std::string line;
    while (std::getline(in, line)) {
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = to_lower(trim(line.substr(0, eq)));
        std::string val = trim(line.substr(eq + 1));
        if (key == "boot2")
            id.boot2 = val;
        else if (key == "ver")
            id.version = val;
    }
    if (!id.boot2.empty()) {
        std::string name = id.boot2;
        size_t p = name.find_last_of("\\/:");
        if (p != std::string::npos) name = name.substr(p + 1);
        size_t semi = name.find(';');
        if (semi != std::string::npos) name.resize(semi);
        id.serial = serial_from_boot_name(name);
        std::string pre = id.serial.substr(0, 4);
        if (pre == "SCUS" || pre == "SLUS")
            id.region = "USA (NTSC-U)";
        else if (pre == "SCES" || pre == "SLES" || pre == "SCED" || pre == "SLED")
            id.region = "Europe (PAL)";
        else if (pre == "SCPS" || pre == "SLPS" || pre == "SLPM" || pre == "SCAJ" || pre == "SLAJ" ||
                 pre == "SCKA" || pre == "SLKA")
            id.region = "Japan/Asia (NTSC-J)";
    }
    return id;
}

int run_extract(const Options& opt) {
    Ctx c{opt, opt.log ? *opt.log : std::cout, opt.err ? *opt.err : std::cerr};
    const bool use_accepted = opt.expect_sha1.empty();
    const std::string want_sha1 = use_accepted ? std::string(kAcceptedImage.sha1) : to_lower(opt.expect_sha1);

    // ---- open and parse ----
    IsoFile iso;
    std::string e;
    if (!iso.open(opt.iso, e)) {
        c.err << "error: " << e << "\n";
        return kUnreadableIso;
    }
    IsoImage img;
    if (!read_iso_tree(iso, img, e)) {
        c.err << "error: '" << opt.iso.u8string() << "' is not a readable ISO 9660 disc image: " << e << "\n";
        return kMalformedIso;
    }

    DiscIdentity id;
    for (const IsoEntry& f : img.files) {
        if (f.layer == 0 && f.path == "/SYSTEM.CNF") {
            std::string text;
            if (read_entry(iso, f, text, 64 * 1024)) id = parse_system_cnf(text);
            break;
        }
    }

    // ---- merge layers into one tree ----
    std::vector<Output> outputs;
    {
        std::map<std::string, size_t> by_path;
        for (const IsoEntry& f : img.files) {
            std::string rel = f.path.substr(1);
            auto it = by_path.find(rel);
            Copy cp;
            cp.layer = f.layer;
            cp.extents = f.extents;
            for (size_t i = 1; i < cp.extents.size(); ++i) {
                const Extent& a = cp.extents[i - 1];
                if (cp.extents[i].lba * kSectorSize < a.lba * kSectorSize + a.size) {
                    c.err << "error: multi-extent file '" << f.path
                          << "' has out-of-order extents, which rg-extract does not support\n";
                    return kMalformedIso;
                }
            }
            if (it == by_path.end()) {
                by_path[rel] = outputs.size();
                Output o;
                o.path = rel;
                o.size = f.size;
                o.copies.push_back(std::move(cp));
                outputs.push_back(std::move(o));
            } else {
                Output& o = outputs[it->second];
                if (o.size != f.size) {
                    c.err << "error: '" << f.path << "' exists on both layers with different sizes (" << o.size
                          << " vs " << f.size << ")\n";
                    return kMalformedIso;
                }
                o.copies.push_back(std::move(cp));
            }
        }
        // Case-insensitive collisions would overwrite each other on Windows/macOS.
        std::map<std::string, std::string> folded;
        for (const Output& o : outputs) {
            auto r = folded.emplace(to_lower(o.path), o.path);
            if (!r.second) {
                c.err << "error: '" << o.path << "' and '" << r.first->second << "' differ only in case\n";
                return kMalformedIso;
            }
        }
        std::sort(outputs.begin(), outputs.end(), [](const Output& a, const Output& b) { return a.path < b.path; });
    }
    uint64_t unique_bytes = 0;
    size_t dup_count = 0;
    for (const Output& o : outputs) {
        unique_bytes += o.size;
        if (o.copies.size() > 1) ++dup_count;
    }

    c.log << "Image:   " << opt.iso.u8string() << " (" << iso.size() << " bytes)\n";
    c.log << "Volumes: " << img.volumes.size() << " ISO 9660 (" << (img.volumes.size() > 1 ? "dual-layer" : "single-layer")
          << (img.has_udf_bridge ? ", UDF bridge ignored" : "") << ")\n";
    for (const IsoVolume& v : img.volumes)
        c.log << "  layer " << v.layer << ": sectors " << v.base_lba << ".." << (v.base_lba + v.volume_blocks - 1)
              << ", system '" << v.system_id << "'\n";
    if (img.unparsed_tail_bytes)
        c.log << "  (" << img.unparsed_tail_bytes << " bytes after the last volume are not a volume; ignored)\n";
    c.log << "Disc:    " << describe_identity(id) << "\n";
    c.log << "Files:   " << outputs.size() << " (" << human_bytes(unique_bytes) << "; " << dup_count
          << " stored on both layers)\n";

    if (opt.list_only) {
        c.log << "path\tsize\tcopies\n";
        for (const Output& o : outputs) {
            c.log << o.path << "\t" << o.size << "\t";
            for (size_t i = 0; i < o.copies.size(); ++i) {
                const Copy& cp = o.copies[i];
                c.log << (i ? "," : "") << "L" << cp.layer << ":"
                      << (cp.extents.empty() ? std::string("-") : std::to_string(cp.extents[0].lba));
            }
            c.log << "\n";
        }
        return kOk;
    }

    // ---- quick identity checks before the long pass ----
    if (use_accepted) {
        std::string want_serial = serial_from_boot_name(kAcceptedImage.serial);
        if (id.serial != want_serial || id.version != kAcceptedImage.version)
            return reject(c, id, "SYSTEM.CNF does not match.");
        if (iso.size() != kAcceptedImage.size)
            return reject(c, id,
                          "Image size is " + std::to_string(iso.size()) + " bytes, expected " +
                              std::to_string(kAcceptedImage.size) + ".");
    } else {
        c.err << "warning: --expect-sha1 overrides the built-in check; accepting SHA-1 " << want_sha1 << "\n";
    }

    // ---- output directory ----
    fs::path out = fs::absolute(opt.out).lexically_normal();
    if (out.filename().empty()) out = out.parent_path();
    fs::path partial = out.parent_path() / (out.filename().native() + fs::path(".partial").native());
    fs::path old = out.parent_path() / (out.filename().native() + fs::path(".old").native());
    std::error_code ec;
    bool out_exists = fs::exists(out, ec);
    if (out_exists) {
        if (!fs::is_directory(out, ec)) {
            c.err << "error: output path '" << out.u8string() << "' exists and is not a directory\n";
            return kOutputExists;
        }
        if (!opt.force) {
            if (fs::exists(out / kManifestName, ec)) {
                c.err << "error: '" << out.u8string()
                      << "' already holds a complete extraction (MANIFEST.tsv present). Use --force to redo it.\n";
                return kOutputExists;
            }
            if (!is_dir_empty(out)) {
                c.err << "error: '" << out.u8string() << "' exists and is not empty. Use --force to replace it.\n";
                return kOutputExists;
            }
        }
    }
    for (const fs::path& p : {partial, old}) {
        if (fs::exists(p, ec)) {
            bool ours = fs::exists(p / kPartialMarker, ec) || fs::exists(p / kManifestName, ec) || is_dir_empty(p);
            if (!ours) {
                c.err << "error: '" << p.u8string() << "' exists and was not made by rg-extract; move it away first\n";
                return kOutputExists;
            }
            fs::remove_all(p, ec);
            if (ec) {
                c.err << "error: cannot remove stale '" << p.u8string() << "': " << ec.message() << "\n";
                return kWriteFailed;
            }
        }
    }
    fs::create_directories(partial, ec);
    if (ec) {
        c.err << "error: cannot create '" << partial.u8string() << "': " << ec.message() << "\n";
        return kWriteFailed;
    }
    PartialGuard guard;
    guard.dir = partial;
    guard.outputs = &outputs;
    guard.armed = true;
    {
        std::FILE* m = open_write(partial / kPartialMarker);
        if (!m) {
            c.err << "error: cannot write in '" << partial.u8string() << "': " << std::strerror(errno) << "\n";
            return kWriteFailed;
        }
        std::fclose(m);
    }

    // Free space: the unique bytes plus slack for the manifest and filesystem overhead.
    {
        fs::space_info si = fs::space(partial, ec);
        // Converted movies take about 1.4x the MVI files (video is remuxed, not re-encoded;
        // the WAV holds the PCM). Reserve 1.5x.
        uint64_t movie_bytes = 0;
        if (opt.convert_movies)
            for (const Output& o : outputs)
                if (!movie_output_stem(o.path).empty()) movie_bytes += o.size;
        uint64_t need = unique_bytes + movie_bytes + movie_bytes / 2 + (64ull << 20);
        if (!ec && si.available < need) {
            c.err << "error: not enough free space on the output drive: need " << human_bytes(need) << ", "
                  << human_bytes(si.available) << " available\n";
            return kWriteFailed;
        }
        if (!ec) c.log << "Output:  " << out.u8string() << " (" << human_bytes(si.available) << " free)\n";
    }

    // Directories (including empty ones) and zero-length files.
    for (const std::string& d : img.dirs) {
        fs::create_directories(partial / fs::u8path(d.substr(1)), ec);
        if (ec) {
            c.err << "error: cannot create directory '" << d << "': " << ec.message() << "\n";
            return kWriteFailed;
        }
    }
    std::vector<Target> targets;
    for (size_t i = 0; i < outputs.size(); ++i) {
        Output& o = outputs[i];
        if (o.size == 0) {
            std::FILE* f = open_write(partial / fs::u8path(o.path));
            if (!f) {
                c.err << "error: cannot create '" << o.path << "': " << std::strerror(errno) << "\n";
                return kWriteFailed;
            }
            std::fclose(f);
        }
        for (size_t k = 0; k < o.copies.size(); ++k)
            for (const Extent& x : o.copies[k].extents)
                targets.push_back(Target{x.lba * kSectorSize, x.lba * kSectorSize + x.size, i, k});
    }
    std::sort(targets.begin(), targets.end(), [](const Target& a, const Target& b) { return a.start < b.start; });

    // ---- one sequential pass: SHA-1 of the image, SHA-256 of every file copy, writes ----
    c.log << "Verifying and extracting...\n";
    const uint64_t total = iso.size();
    if (!iso.seek(0)) {
        c.err << "error: seek failed on the image\n";
        return kUnreadableIso;
    }
    std::vector<std::unique_ptr<uint8_t[]>> bufs;
    for (int i = 0; i < 3; ++i) bufs.emplace_back(new uint8_t[kChunk]);
    Sha1 sha1;
    auto read_chunk = [&iso, total](uint8_t* dst, uint64_t pos) -> size_t {
        size_t want = size_t(std::min<uint64_t>(kChunk, total - pos));
        return want ? iso.read(dst, want) : 0;
    };
    std::future<size_t> fut_read = std::async(std::launch::async, read_chunk, bufs[0].get(), uint64_t(0));
    std::future<void> fut_sha1;
    size_t next = 0;
    std::vector<size_t> active;
    uint64_t pos = 0;
    auto t0 = std::chrono::steady_clock::now();
    auto last = t0;
    std::string write_error;
    for (uint64_t k = 0; pos < total; ++k) {
        uint8_t* cur = bufs[k % 3].get();
        size_t n = fut_read.get();
        if (n == 0) {
            if (fut_sha1.valid()) fut_sha1.get();
            c.err << "\nerror: read error in the image at byte " << pos << " (" << (iso.error() ? "I/O error" : "unexpected end of file")
                  << ")\n";
            return kUnreadableIso;
        }
        if (fut_sha1.valid()) fut_sha1.get();  // chunk k-1 done, so buffer (k+1)%3 is free
        uint64_t cend = pos + n;
        if (cend < total) fut_read = std::async(std::launch::async, read_chunk, bufs[(k + 1) % 3].get(), cend);
        fut_sha1 = std::async(std::launch::async, [&sha1, cur, n] { sha1.update(cur, n); });

        while (next < targets.size() && targets[next].start < cend) active.push_back(next++);
        for (size_t a : active) {
            const Target& t = targets[a];
            uint64_t s = std::max(t.start, pos), en = std::min(t.end, cend);
            if (s >= en) continue;
            const uint8_t* p = cur + (s - pos);
            size_t len = size_t(en - s);
            Output& o = outputs[t.out];
            o.copies[t.copy].hash.update(p, len);
            if (t.copy != 0 || !write_error.empty()) continue;
            if (!o.fp) {
                o.fp = open_write(partial / fs::u8path(o.path));
                if (!o.fp) {
                    write_error = "cannot create '" + o.path + "': " + std::strerror(errno);
                    continue;
                }
            }
            if (std::fwrite(p, 1, len, o.fp) != len) {
                int er = errno;
                write_error = (er == ENOSPC ? std::string("disk full while writing '") : std::string("write failed for '")) +
                              o.path + "': " + std::strerror(er);
                continue;
            }
            o.written += len;
            if (o.written == o.size) {
                if (std::fclose(o.fp) != 0) {
                    int er = errno;
                    write_error = (er == ENOSPC ? std::string("disk full while writing '") : std::string("write failed for '")) +
                                  o.path + "': " + std::strerror(er);
                }
                o.fp = nullptr;
            }
        }
        active.erase(std::remove_if(active.begin(), active.end(), [&](size_t a) { return targets[a].end <= cend; }),
                     active.end());
        pos = cend;

        if (!write_error.empty()) {
            if (fut_sha1.valid()) fut_sha1.get();
            if (fut_read.valid()) fut_read.get();
            c.err << "\nerror: " << write_error << "\n";
            return kWriteFailed;
        }
        auto now = std::chrono::steady_clock::now();
        if (opt.progress && (now - last > std::chrono::milliseconds(500) || pos == total)) {
            last = now;
            double secs = std::chrono::duration<double>(now - t0).count();
            double rate = secs > 0 ? double(pos) / secs : 0;
            double eta = rate > 0 ? double(total - pos) / rate : 0;
            char line[160];
            std::snprintf(line, sizeof line, "\r  %5.1f%%  %s / %s  %.0f MiB/s  ETA %d:%02d   ", 100.0 * double(pos) / double(total),
                          human_bytes(pos).c_str(), human_bytes(total).c_str(), rate / double(1 << 20), int(eta) / 60,
                          int(eta) % 60);
            c.err << line << std::flush;
        }
    }
    if (fut_sha1.valid()) fut_sha1.get();
    if (opt.progress) c.err << "\n";
    double secs = std::chrono::duration<double>(std::chrono::steady_clock::now() - t0).count();

    std::string got_sha1 = sha1.finish_hex();
    c.log << "SHA-1:   " << got_sha1 << "\n";
    if (got_sha1 != want_sha1) {
        if (use_accepted) return reject(c, id, "SHA-1 is " + got_sha1 + ".");
        c.err << "error: wrong disc image: SHA-1 is " << got_sha1 << ", expected " << want_sha1 << " (image is "
              << describe_identity(id) << ")\n";
        return kWrongImage;
    }

    for (Output& o : outputs) {
        if (o.copies[0].extents.size() && o.written != o.size) {
            c.err << "error: internal: '" << o.path << "' wrote " << o.written << " of " << o.size << " bytes\n";
            return kWriteFailed;
        }
        for (Copy& cp : o.copies) cp.sha256 = cp.hash.finish_hex();
        for (size_t i = 1; i < o.copies.size(); ++i) {
            if (o.copies[i].sha256 != o.copies[0].sha256) {
                c.err << "error: '" << o.path << "' differs between layer " << o.copies[0].layer << " and layer "
                      << o.copies[i].layer << "\n";
                return kMalformedIso;
            }
        }
    }

    // ---- movie conversion (docs/MVI.md): originals stay byte-identical, outputs go to converted/ ----
    std::vector<Converted> converted;
    std::vector<std::string> convert_failed;
    if (opt.convert_movies) {
        std::vector<size_t> movies;
        for (size_t i = 0; i < outputs.size(); ++i)
            if (!movie_output_stem(outputs[i].path).empty()) movies.push_back(i);
        if (!movies.empty()) c.log << "Converting " << movies.size() << " movies...\n";
        auto tc = std::chrono::steady_clock::now();
        for (size_t k = 0; k < movies.size(); ++k) {
            const Output& o = outputs[movies[k]];
            std::string stem = movie_output_stem(o.path);
            fs::path mpg = partial / fs::u8path(stem + ".mpg"), wav = partial / fs::u8path(stem + ".wav");
            fs::create_directories(mpg.parent_path(), ec);
            if (ec) {
                c.err << "error: cannot create '" << mpg.parent_path().u8string() << "': " << ec.message() << "\n";
                return kWriteFailed;
            }
            if (opt.progress) {
                char line[200];
                std::snprintf(line, sizeof line, "\r  %3u/%u  %-40s", unsigned(k + 1), unsigned(movies.size()),
                              o.path.c_str());
                c.err << line << std::flush;
            }
            mvi::MovieInfo mi;
            std::string why;
            if (!mvi::convert_movie(partial / fs::u8path(o.path), mpg, wav, &mi, &why)) {
                if (why.rfind("write", 0) == 0 || why.rfind("cannot create", 0) == 0) {
                    c.err << "\nerror: converting '" << o.path << "': " << why << "\n";
                    return kWriteFailed;
                }
                // A movie the converter cannot read stays usable in its original form.
                c.err << (opt.progress ? "\n" : "") << "warning: '" << o.path << "' not converted: " << why << "\n";
                convert_failed.push_back(o.path + "\t" + why);
                continue;
            }
            for (int w = 0; w < 2; ++w) {
                Converted cv;
                cv.path = stem + (w ? ".wav" : ".mpg");
                cv.source = o.path;
                cv.kind = w ? "movie-audio" : "movie-video";
                if (!sha256_file(w ? wav : mpg, &cv.size, &cv.sha256)) {
                    c.err << "\nerror: cannot read back '" << cv.path << "'\n";
                    return kWriteFailed;
                }
                converted.push_back(std::move(cv));
            }
        }
        if (opt.progress && !movies.empty()) c.err << "\n";
        if (!movies.empty())
            c.log << "Movies:  " << converted.size() / 2 << " converted, " << convert_failed.size() << " failed, in "
                  << std::fixed << std::setprecision(1)
                  << std::chrono::duration<double>(std::chrono::steady_clock::now() - tc).count() << " s\n";
    }

    // ---- manifest, then commit ----
    {
        std::ostringstream m;
        m << "# rg-extract manifest v2\n";
        m << "# source_sha1\t" << got_sha1 << "\n";
        m << "# source_size\t" << total << "\n";
        if (!id.serial.empty()) m << "# source_serial\t" << id.serial << "\tVER " << id.version << "\n";
        // ISO 9660 volume geometry (layer, image sector of the volume's sector 0, volume
        // blocks), for mapping CDVD sector numbers to files (docs/CDVD.md).
        for (const IsoVolume& v : img.volumes)
            m << "# volume\t" << v.layer << "\t" << v.base_lba << "\t" << v.volume_blocks << "\n";
        m << "path\tsize\tsha256\tlba\tcopies\n";
        for (const Output& o : outputs) {
            const Copy& p0 = o.copies[0];
            m << o.path << "\t" << o.size << "\t" << p0.sha256 << "\t"
              << (p0.extents.empty() ? std::string("-") : std::to_string(p0.extents[0].lba)) << "\t";
            for (size_t i = 0; i < o.copies.size(); ++i) {
                const Copy& cp = o.copies[i];
                m << (i ? "," : "") << "L" << cp.layer << ":"
                  << (cp.extents.empty() ? std::string("-") : std::to_string(cp.extents[0].lba));
            }
            m << "\n";
        }
        // Converted outputs: a separate section after the disc files, with its own header.
        m << "# section\tconverted\n";
        for (const std::string& f : convert_failed) m << "# convert_failed\t" << f << "\n";
        m << "path\tsize\tsha256\tsource\tkind\n";
        for (const Converted& cv : converted)
            m << cv.path << "\t" << cv.size << "\t" << cv.sha256 << "\t" << cv.source << "\t" << cv.kind << "\n";
        std::string s = m.str();
        std::FILE* f = open_write(partial / kManifestName);
        bool ok = f && std::fwrite(s.data(), 1, s.size(), f) == s.size();
        if (f && std::fclose(f) != 0) ok = false;
        if (!ok) {
            c.err << "error: cannot write " << kManifestName << ": " << std::strerror(errno) << "\n";
            return kWriteFailed;
        }
    }
    fs::remove(partial / kPartialMarker, ec);
    if (out_exists) {
        fs::rename(out, old, ec);
        if (ec) {
            c.err << "error: cannot move the old '" << out.u8string() << "' aside: " << ec.message() << "\n";
            return kWriteFailed;
        }
    }
    fs::rename(partial, out, ec);
    if (ec) {
        c.err << "error: cannot rename '" << partial.u8string() << "' to '" << out.u8string() << "': " << ec.message()
              << "\n";
        if (out_exists) fs::rename(old, out, ec);
        return kWriteFailed;
    }
    guard.armed = false;
    if (out_exists) fs::remove_all(old, ec);

    c.log << "Done: " << outputs.size() << " files, " << human_bytes(unique_bytes) << " written to " << out.u8string()
          << " in " << std::fixed << std::setprecision(1) << secs << " s\n";
    return kOk;
}

}  // namespace rgx
