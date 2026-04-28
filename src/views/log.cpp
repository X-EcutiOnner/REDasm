#include "log.h"
#include "support/themeprovider.h"
#include <QFontDatabase>

LogView::LogView(QWidget* parent): QWidget{parent}, m_ui{this} {
    this->setVisible(false);

    QFont f = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    m_ui.telogs->setFont(f);
    m_ui.telogs->document()->setDocumentMargin(0);

    connect(m_ui.tbclear, &QToolButton::clicked, this, &LogView::clear);

    connect(m_ui.lefilter, &QLineEdit::textChanged, this, [&](const QString&) {
        m_ui.telogs->clear();

        for(const LogEntry& e : m_entries) {
            if(this->accept_log(e)) this->append_log(e, false);
        }

        m_ui.telogs->moveCursor(QTextCursor::End);
        m_ui.telogs->ensureCursorVisible();
    });
}

void LogView::clear() {
    this->setVisible(false);
    m_ui.lefilter->clear();
    m_ui.telogs->clear();
    m_entries.clear();
}

const LogView::LogEntry&
LogView::collect_log(RDLogLevel level, const QString& tag, const QString& msg) {
    m_entries.push_back(LogEntry{level, tag, msg});
    return m_entries.back();
}

bool LogView::accept_log(const LogEntry& e) const {
    QString s = m_ui.lefilter->text();
    if(s.isEmpty()) return true;
    return e.tag.contains(s, Qt::CaseInsensitive);
}

void LogView::append_log(const LogEntry& e, bool update) {
    this->setVisible(true);

    QTextCursor cursor = m_ui.telogs->textCursor();
    cursor.movePosition(QTextCursor::End);
    if(!m_ui.telogs->document()->isEmpty()) cursor.insertBlock();

    QTextCharFormat defaultfmt, tagfmt;
    tagfmt.setForeground(theme_provider::color(RD_THEME_COMMENT));
    cursor.insertText("[", defaultfmt);
    cursor.insertText(e.tag, tagfmt);
    cursor.insertText("] ", defaultfmt);

    QColor c;

    switch(e.level) {
        case RD_LOG_DEBUG: c = theme_provider::color(RD_THEME_MUTED); break;
        case RD_LOG_WARN: c = theme_provider::color(RD_THEME_WARNING); break;
        case RD_LOG_FAIL: c = theme_provider::color(RD_THEME_FAIL); break;
        default: c = theme_provider::color(RD_THEME_FOREGROUND); break;
    }

    QTextCharFormat fmt;
    fmt.setForeground(c);
    cursor.insertText(e.msg, fmt);

    if(!update) return;

    m_ui.telogs->moveCursor(QTextCursor::End);
    m_ui.telogs->ensureCursorVisible();
}

void LogView::log(RDLogLevel level, const QString& tag, const QString& msg) {
    const LogEntry& e = this->collect_log(level, tag, msg);
    if(this->accept_log(e)) this->append_log(e, true);
}
