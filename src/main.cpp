#include "mainwindow.h"
#include "support/surfacerenderer.h"
#include "support/themeprovider.h"
#include "support/utils.h"
#include <QApplication>
#include <QDirIterator>
#include <QFileInfo>
#include <QStandardPaths>
#include <QString>
#include <QStyleFactory>

namespace {

const QString REDASM_VERSION = "4.0";

void on_log(RDLogLevel level, const char* tag, const char* msg,
            void* userdata) {
    auto* mw = reinterpret_cast<MainWindow*>(userdata);
    mw->log(level, QString::fromUtf8(tag), QString::fromUtf8(msg));
}

void configure_searchpaths() {
#if !defined(_WIN32)
    const char* appimage_dir = std::getenv("APPDIR");
    bool is_appimage = appimage_dir && std::getenv("APPIMAGE");
#else
    constexpr bool is_appimage = false;
#endif

    // clang-format off
    if(is_appimage) {
        // 1. user plugins
        const QString USER_DIR = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
        utils::search_paths.append(USER_DIR + "/plugins");
        utils::kb_search_paths.append((USER_DIR + "/kb").toUtf8());

        // 2. bundled plugins
        const QString APP_DIR = QString::fromUtf8(appimage_dir);
        utils::search_paths.append(APP_DIR + "/usr/lib/redasm/plugins");
        utils::kb_search_paths.append((APP_DIR + "/usr/share/redasm/kb").toUtf8());

        // 3. system plugins
        for(const QString& sp : QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)) {
            if(sp == USER_DIR) continue; // already added, skip

            utils::search_paths.append(sp + "/plugins");
            utils::kb_search_paths.append((sp + "/kb").toUtf8());
        }
    }
    else {
        const QString APP_DIR = qApp->applicationDirPath();

        utils::search_paths.append(APP_DIR + QDir::separator() + "plugins");
        utils::kb_search_paths.append((APP_DIR + QDir::separator() + "kb").toUtf8());

        for(const QString& sp : QStandardPaths::standardLocations(QStandardPaths::AppDataLocation)) {
            utils::search_paths.append(sp + QDir::separator() + "plugins");
            utils::kb_search_paths.append((sp + QDir::separator() + "kb").toUtf8());
        }

    }
    // clang-format on
}

QVector<const char*> get_kb_searchpaths() {
    QVector<const char*> v;

    for(const QByteArray& ba : utils::kb_search_paths)
        v.push_back(ba.constData());

    v.push_back(nullptr);
    return v;
}

void load_modules() {
    for(const QString& searchpath : utils::search_paths) {
        QDirIterator it{searchpath, QDirIterator::Subdirectories};

        while(it.hasNext()) {
            QFileInfo fi = it.nextFileInfo();

            if(fi.isFile() && ("." + fi.suffix() == SHARED_OBJECT_EXT))
                rd_module_load(qUtf8Printable(fi.filePath()));
        }
    }
}

} // namespace

#if !defined(__has_feature)
#define __has_feature(x) 0
#endif

#if __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)

extern "C" const char* __asan_default_options() { // NOLINT
    return "suppressions=asan.supp:print_suppressions=0";
}

extern "C" const char* __lsan_default_options() { // NOLINT
    return "suppressions=lsan.supp:print_suppressions=0";
}

extern "C" const char* __lsan_default_suppressions() { // NOLINT
    return "";
}

#endif

int main(int argc, char** argv) {
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QApplication app{argc, argv};
    app.setApplicationName("redasm");
    app.setApplicationDisplayName("REDasm " + REDASM_VERSION);

    theme_provider::apply_theme();
    surface_renderer::init();
    int res = 0;

    { // Scoping makes sure that widgets and context are freed before deinit
        MainWindow mw;
        mw.show();

        configure_searchpaths();
        rd_set_log_callback(on_log, &mw);

        QVector<const char*> kb_paths = get_kb_searchpaths();

        RDInitParams params = {};
        params.kb_paths = kb_paths.data();
        rd_init(&params);

        load_modules();

        res = app.exec();
        rd_set_log_callback(nullptr, nullptr);
    }

    rd_deinit();
    return res;
}
