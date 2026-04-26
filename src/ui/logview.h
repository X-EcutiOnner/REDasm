#pragma once

#include "support/fontawesome.h"
#include <QHBoxLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWidget>

namespace ui {

struct LogView {
    QTextEdit* telogs;
    QLineEdit* lefilter;
    QToolButton* tbclear;

    explicit LogView(QWidget* self) {
        this->tbclear = new QToolButton(self);
        this->tbclear->setIcon(FA_ICON(0xf51a));
        this->tbclear->setAutoRaise(true);
        this->tbclear->setToolTip("Clear");

        auto* hbox = new QHBoxLayout();
        hbox->setContentsMargins(4, 0, 4, 0);
        hbox->setSpacing(2);
        hbox->addStretch();
        hbox->addWidget(this->tbclear);

        this->lefilter = new QLineEdit(self);
        this->lefilter->setPlaceholderText("Filter...");
        this->lefilter->setClearButtonEnabled(true);
        this->lefilter->setFocusPolicy(Qt::ClickFocus);

        this->telogs = new QTextEdit(self);
        this->telogs->setWordWrapMode(QTextOption::NoWrap);
        this->telogs->setUndoRedoEnabled(false);
        this->telogs->setReadOnly(true);

        this->telogs->setStyleSheet("QTextEdit {"
                                    "  border: none;"
                                    "  border-top: 1px solid palette(mid);"
                                    "}");

        auto* vbox = new QVBoxLayout(self);
        vbox->addLayout(hbox);
        vbox->addWidget(this->telogs, 1);
        vbox->addWidget(this->lefilter);
        vbox->setContentsMargins(0, 0, 0, 0);
        vbox->setSpacing(0);
    }
};

} // namespace ui
