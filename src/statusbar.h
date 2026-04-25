#pragma once

#include "views/surface/isurface.h"
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <redasm/redasm.h>

namespace statusbar {

// Widgets
QLabel* create_status_label(QWidget* parent);
QPushButton* create_problems_button(int size, QWidget* parent);
QPushButton* create_status_button(int size, QWidget* parent);
QPushButton* problems_button();
QPushButton* status_button();

// Functions
void set_busy_status();
void set_pause_status();
void set_ready_status();
void set_status_text(const QString& s);
void set_address(ISurface* surface);
void check_problems(const RDContext* ctx);

} // namespace statusbar
