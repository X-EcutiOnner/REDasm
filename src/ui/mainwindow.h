#pragma once

#include "support/actions.h"
#include "support/fontawesome.h"
#include "views/log.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QSplitter>
#include <QStackedWidget>
#include <QStatusBar>
#include <QToolBar>
#include <QToolButton>

#if !defined(NDEBUG) && defined(Q_OS_UNIX) && !defined(Q_OS_MACOS)
#include <QProcessEnvironment>
#include <QString>
#include <QStringList>
#endif

namespace ui {

struct MainWindow {
    QStatusBar* statusbar;
    QStackedWidget* stackwidget;
    QMenu *mnufile, *mnuedit, *mnuview, *mnutools, *mnuwindow, *mnuhelp;
    QMenu *mnurecents, *mnuexport, *mnudev;
    QAction *actfileopen, *actfilesave, *actfilesaveas, *actfileexportdb,
        *actfileexportinput, *actfileexportpatch, *actfileclose, *actfileexit;
    QAction* actwinrestoredefault;
    QAction *actedit, *actview, *acttools;
    QAction *acttoolsflc, *acttoolsproblems;
    QAction *actdevdecoder, *actdevgraphs;
    QAction *actviewmemorymap, *actviewsegments, *actviewmappings,
        *actviewsegmentregs, *actviewstrings, *actviewtypedefs,
        *actviewimported, *actviewexported;
    QAction *acttbseparator1, *acttbseparator2, *acttbseparator3,
        *acttbseparator4;
    ::LogView* logview;

    explicit MainWindow(QMainWindow* self) {
        self->setAcceptDrops(true);
        self->resize(1500, 850);

#if !defined(NDEBUG) && defined(Q_OS_UNIX) && !defined(Q_OS_MACOS)
        if(this->is_tiling_wm()) self->setFixedSize(1500, 850);
#endif

        actions::init(self);

        auto* menubar = new QMenuBar(self);
        this->mnufile = menubar->addMenu("&File");
        this->mnuedit = menubar->addMenu("&Edit");
        this->mnuview = menubar->addMenu("&View");
        this->mnutools = menubar->addMenu("&Tools");
        this->mnuwindow = menubar->addMenu("&Window");
        this->mnuhelp = menubar->addMenu("&?");

        this->actedit = this->mnuedit->menuAction();
        this->actedit->setVisible(false);

        this->actview = this->mnuview->menuAction();
        this->actview->setVisible(false);

        this->acttools = this->mnutools->menuAction();

        this->actfileopen = this->mnufile->addAction(
            FA_ICON(0xf07c), "&Open", QKeySequence{Qt::CTRL | Qt::Key_O});

        this->actfilesave = this->mnufile->addAction(
            FA_ICON(0xf0c7), "Save", QKeySequence{Qt::CTRL | Qt::Key_S});
        this->actfilesave->setVisible(false);

        this->actfilesaveas = this->mnufile->addAction(
            "Save as…", QKeySequence{Qt::CTRL | Qt::SHIFT | Qt::Key_S});
        this->actfilesaveas->setVisible(false);

        this->mnuexport = this->mnufile->addMenu(FA_ICON(0xf30b), "Export…");
        this->mnuexport->setVisible(false);

        this->actfileexportdb = this->mnuexport->addAction("Database");
        this->actfileexportinput = this->mnuexport->addAction("Input");
        this->actfileexportpatch = this->mnuexport->addAction("Patched Input");

        this->actfileclose = this->mnufile->addAction("Close");
        this->actfileclose->setVisible(false);

        this->mnufile->addSeparator();
        this->mnurecents = new QMenu("&Recent Files", menubar);
        this->mnufile->addMenu(this->mnurecents);
        this->mnufile->addAction(actions::get(actions::OPEN_SETTINGS));
        this->actfileexit = this->mnufile->addAction("&Exit");

        this->actwinrestoredefault =
            this->mnuwindow->addAction("Restore Default");

        this->acttoolsproblems = this->mnutools->addAction("&Problems");
        this->acttoolsproblems->setVisible(false);

        this->acttoolsflc = this->mnutools->addAction(
            "&FLC", QKeySequence{Qt::CTRL | Qt::Key_L});
        this->acttoolsflc->setVisible(false);

        this->acttbseparator1 = this->mnutools->addSeparator();

        this->mnudev = this->mnutools->addMenu("Dev");
        this->actdevdecoder = this->mnudev->addAction("&Decoder/Encoder");
        this->actdevgraphs = this->mnudev->addAction("&Graphs");

        this->mnuhelp->addAction(actions::get(actions::OPEN_HOME));
        this->mnuhelp->addAction(actions::get(actions::OPEN_GITHUB));
        this->mnuhelp->addAction(actions::get(actions::OPEN_FEEDBACK));
        this->mnuhelp->addSeparator();
        this->mnuhelp->addAction(actions::get(actions::OPEN_ABOUT));

        this->mnuedit->addAction(actions::get(actions::COPY));
        this->mnuedit->addAction(actions::get(actions::SELECT_ALL));
        this->mnuedit->addSeparator();
        this->mnuedit->addAction(actions::get(actions::REANALYZE));

        this->actviewmemorymap = this->mnuview->addAction(
            "Memory Map", QKeySequence{Qt::SHIFT | Qt::Key_F1});

        this->actviewmappings = this->mnuview->addAction(
            FA_ICON(0xe697), "Mappings", QKeySequence{Qt::SHIFT | Qt::Key_F2});

        this->actviewsegments = this->mnuview->addAction(
            FA_ICON(0xf200), "Segments", QKeySequence{Qt::SHIFT | Qt::Key_F3});

        this->actviewsegmentregs = this->mnuview->addAction(
            "Segment Registers", QKeySequence{Qt::SHIFT | Qt::Key_F4});

        this->actviewstrings = this->mnuview->addAction(
            FA_ICON(0xf031), "&Strings", QKeySequence{Qt::SHIFT | Qt::Key_F5});

        this->actviewtypedefs =
            this->mnuview->addAction(FA_ICON(0xf1b3), "&Type Definitions",
                                     QKeySequence{Qt::SHIFT | Qt::Key_F6});

        this->mnuview->addSeparator();

        this->actviewexported = this->mnuview->addAction(
            FA_ICON(0xf56e), "&Exported", QKeySequence{Qt::SHIFT | Qt::Key_F7});

        this->actviewimported = this->mnuview->addAction(
            FA_ICON(0xf56f), "&Imported", QKeySequence{Qt::SHIFT | Qt::Key_F8});

        auto* toolbar = new QToolBar(self);
        toolbar->setObjectName("MainToolBar");
        toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolbar->setFloatable(false);
        toolbar->setMovable(false);
        toolbar->addAction(this->actfileopen);
        toolbar->addAction(this->actfilesave);
        this->acttbseparator2 = toolbar->addSeparator();
        toolbar->addAction(actions::get(actions::GOTO));
        this->acttbseparator3 = toolbar->addSeparator();
        toolbar->addAction(this->actviewsegments);
        toolbar->addAction(this->actviewmappings);
        this->acttbseparator4 = toolbar->addSeparator();
        toolbar->addAction(this->actviewexported);
        toolbar->addAction(this->actviewimported);
        toolbar->addAction(this->actviewstrings);
        self->addToolBar(toolbar);

        self->setMenuBar(menubar);

        this->statusbar = new QStatusBar(self);
        self->setStatusBar(this->statusbar);

        this->stackwidget = new QStackedWidget();
        this->logview = new ::LogView();

        auto* vsplit = new QSplitter(Qt::Vertical);
        vsplit->addWidget(this->stackwidget);
        vsplit->addWidget(this->logview);
        vsplit->setStretchFactor(0, 10);
        vsplit->setStretchFactor(1, 1);

        self->setCentralWidget(vsplit);
    }

#if !defined(NDEBUG) && defined(Q_OS_UNIX) && !defined(Q_OS_MACOS)
private:
    bool is_tiling_wm() {
        const QProcessEnvironment ENV =
            QProcessEnvironment::systemEnvironment();

        // Most tiling WMs set their own IPC socket env var
        // the most reliable signal
        static const QStringList TILING_ENV_HINTS = {
            "I3SOCK",                      // i3
            "SWAYSOCK",                    // sway
            "HYPRLAND_INSTANCE_SIGNATURE", // Hyprland
            "BSPWM_SOCKET",                // bspwm
            "QTILE_XEPHYR",                // qtile (partial)
        };

        for(const auto& var : TILING_ENV_HINTS) {
            if(ENV.contains(var)) return true;
        }

        // Fallback: match XDG_CURRENT_DESKTOP / DESKTOP_SESSION against known
        // tiling WM names (covers ones without a dedicated socket env var)
        static const QStringList TILING_WM_NAMES = {
            "i3",           "sway",  "bspwm",    "awesome", "dwm",  "xmonad",
            "herbstluftwm", "qtile", "spectrwm", "leftwm",  "river"};

        QString desktop = ENV.value("XDG_CURRENT_DESKTOP").toLower();
        QString session = ENV.value("DESKTOP_SESSION").toLower();

        for(const auto& name : TILING_WM_NAMES) { // NOLINT
            if(desktop.contains(name) || session.contains(name)) return true;
        }

        return false;
    }

#endif
};

} // namespace ui
