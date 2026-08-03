#include "input.h"
#include <QDialogButtonBox>
#include <QKeyEvent>
#include <QVBoxLayout>

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

ItemsInputDialog::ItemsInputDialog(QWidget* parent): QDialog(parent) {
    this->setModal(true);

    m_label = new QLabel(this);

    m_combobox = new QComboBox(this);
    m_combobox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

    auto* buttonbox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    auto* vbox = new QVBoxLayout(this);
    vbox->addWidget(m_label);
    vbox->addWidget(m_combobox);
    vbox->addWidget(buttonbox);

    connect(buttonbox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonbox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

QString ItemsInputDialog::current_text() const {
    return m_combobox->currentText();
}

void ItemsInputDialog::set_label(const QString& v) { m_label->setText(v); }

void ItemsInputDialog::set_items(QAbstractItemModel* m) {
    if(!m->parent()) m->setParent(this);
    m_combobox->setModel(m);
}

void ItemsInputDialog::set_items_column(int c) {
    m_combobox->setModelColumn(c);
}

void ItemsInputDialog::set_current_index(int idx) {
    m_combobox->setCurrentIndex(idx);
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
    if(ok) *ok = ret == QDialog::Accepted;
    return ret == QDialog::Accepted ? dlg.textValue() : QString{};
}

QString get_items(QWidget* parent, const QString& title, const QString& label,
                  QAbstractItemModel* model, int column, int current_row,
                  bool* ok) {
    ItemsInputDialog dlg{parent};
    dlg.setWindowTitle(title);
    dlg.set_label(label);
    dlg.set_items(model);
    dlg.set_items_column(column);

    if(current_row >= 0 && current_row < model->rowCount())
        dlg.set_current_index(current_row);
    else if(model->rowCount() > 0)
        dlg.set_current_index(0);

    dlg.adjustSize();

    int ret = dlg.exec();
    if(ok) *ok = ret == QDialog::Accepted;
    return ret == QDialog::Accepted ? dlg.current_text() : QString{};
}

} // namespace input_dialog
