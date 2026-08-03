#pragma once

#include "ui/typesdialog.h"
#include <redasm/redasm.h>

class TypesDialog: public QDialog {
    Q_OBJECT

public:
    explicit TypesDialog(RDContext* ctx, QWidget* parent = nullptr);
    [[nodiscard]] QString selected_type() const;
    [[nodiscard]] usize selected_count() const;
    [[nodiscard]] RDTypeModifier selected_modifier() const;

private:
    ui::TypesDialog m_ui;
};
