#include "input.h"
#include <QKeyEvent>

TextEditInputDialog::TextEditInputDialog(QWidget* parent, Qt::WindowFlags flags)
    : QInputDialog{parent, flags} {
    this->setOptions(QInputDialog::UsePlainTextEditForTextInput);
}

void TextEditInputDialog::keyPressEvent(QKeyEvent* event) {
    if(event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        if(event->modifiers() & Qt::ControlModifier) {
            this->accept();
            event->accept();
            return;
        }
    }

    QInputDialog::keyPressEvent(event);
}

namespace input_dialog {

QString get_multi_line_text(QWidget* parent, const QString& title,
                            const QString& label, const QString& text, bool* ok,
                            Qt::WindowFlags flags,
                            Qt::InputMethodHints ime_hints) {
    TextEditInputDialog dlg{parent, flags};
    dlg.setWindowTitle(title);
    dlg.setLabelText(label);
    dlg.setTextValue(text);
    dlg.setInputMethodHints(ime_hints);

    int ret = dlg.exec();
    if(ok) *ok = !!ret;
    return ret ? dlg.textValue() : QString{};
}

} // namespace input_dialog
