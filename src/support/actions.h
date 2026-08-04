#pragma once

#include <QAction>

class QMainWindow;

namespace actions {

enum Type : quint8 {
    GOTO,
    COPY,
    SELECT_ALL,
    REFS_TO,
    RENAME,
    COMMENT,

    OP_AS_ADDRESS,
    OP_AS_IMMEDIATE,
    DO_UNDEFINE,
    DO_CODE,
    DO_DATA,
    CREATE_FUNCTION,
    PATCH_INSTRUCTION,
    REANALYZE,

    OPEN_DETAILS,

    OPEN_HOME,
    OPEN_GITHUB,
    OPEN_DISCORD,
    OPEN_X,
    OPEN_MASTODON,
    OPEN_FEEDBACK,

    OPEN_SETTINGS,
    OPEN_ABOUT,
};

void init(QMainWindow* mw);
QAction* get(Type t);

} // namespace actions
