#pragma once

#include <QComboBox>
#include <QInputDialog>
#include <QLabel>

class TextEditInputDialog: public QInputDialog {
    Q_OBJECT

public:
    explicit TextEditInputDialog(QWidget* parent = nullptr,
                                 Qt::WindowFlags flags = {});

protected:
    void keyPressEvent(QKeyEvent* event) override;
};

class ItemsInputDialog: public QDialog {
    Q_OBJECT

public:
    explicit ItemsInputDialog(QWidget* parent = nullptr);
    [[nodiscard]] QString current_text() const;
    void set_label(const QString& v);
    void set_items(QAbstractItemModel* m);
    void set_items_column(int c);
    void set_current_index(int idx);

private:
    QComboBox* m_combobox;
    QLabel* m_label;
};

namespace input_dialog {

QString get_multi_line_text(QWidget* parent, const QString& title,
                            const QString& label, const QString& text = {},
                            bool* ok = nullptr, Qt::WindowFlags flags = {},
                            Qt::InputMethodHints ime_hints = {});

QString get_items(QWidget* parent, const QString& title, const QString& label,
                  QAbstractItemModel* model, int column = 0,
                  int current_row = -1, bool* ok = nullptr);

} // namespace input_dialog
