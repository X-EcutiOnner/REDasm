#include "mainwindow.h"
#include "support/surfacerenderer.h"
#include "support/themeprovider.h"
#include <QApplication>
#include <QString>
#include <QStyleFactory>

namespace {

const QString REDASM_VERSION = "4.0";
bool running = true;

void on_log(RDLogLevel level, const char* tag, const char* msg,
            void* userdata) {
    auto* mw = reinterpret_cast<MainWindow*>(userdata);
    mw->log(level, QString::fromUtf8(tag), QString::fromUtf8(msg));
}

} // namespace

int main(int argc, char** argv) {
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QApplication app{argc, argv};
    app.setApplicationName("redasm");
    app.setApplicationDisplayName("REDasm " + REDASM_VERSION);

    theme_provider::apply_theme();
    surface_renderer::init();

    { // Scoping makes sure that widgets and context are freed before deinit
        MainWindow mw;
        mw.show();

        rd_set_log_callback(on_log, &mw);
        rd_init();
        mw.init_searchpaths();

        QObject::connect(&mw, &MainWindow::closed, []() { running = false; });

        while(running) {
            if(mw.loop())
                app.processEvents(QEventLoop::AllEvents);
            else
                app.processEvents(QEventLoop::WaitForMoreEvents);
        }

        rd_set_log_callback(nullptr, nullptr);
    }

    rd_deinit();
    return 0;
}
