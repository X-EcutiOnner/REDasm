#pragma once

#include <QInputDialog>

class TextEditInputDialog: public QInputDialog {
    Q_OBJECT

public:
    explicit TextEditInputDialog(QWidget* parent = nullptr,
                                 Qt::WindowFlags flags = {});

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

namespace input_dialog {

QString get_multi_line_text(QWidget* parent, const QString& title,
                            const QString& label, const QString& text = {},
                            bool* ok = nullptr, Qt::WindowFlags flags = {},
                            Qt::InputMethodHints ime_hints = {});

}
