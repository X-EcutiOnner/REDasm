#pragma once

#include "ui/decoderdialog.h"
#include <QDialog>

class DecoderDialog: public QDialog {
    Q_OBJECT

public:
    explicit DecoderDialog(QWidget* parent = nullptr);

private:
    void populate_processors() const;

private Q_SLOTS:
    void check_decode();
    void do_decode();

private:
    ui::DecoderDialog m_ui;
};
