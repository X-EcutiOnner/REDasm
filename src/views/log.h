#pragma once

#include "ui/logview.h"
#include <redasm/redasm.h>

class LogView: public QWidget {
    Q_OBJECT

    struct LogEntry {
        RDLogLevel level;
        QString tag;
        QString msg;
    };

public:
    explicit LogView(QWidget* parent = nullptr);

public Q_SLOTS:
    void clear();
    void log(RDLogLevel level, const QString& tag, const QString& msg);

private:
    [[nodiscard]] bool accept_log(const LogEntry& e) const;
    void append_log(const LogEntry& e, bool update);
    const LogEntry& collect_log(RDLogLevel level, const QString& tag,
                                const QString& msg);

private:
    ui::LogView m_ui;
    QList<LogEntry> m_entries;
};
