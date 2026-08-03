#include "types.h"
#include "models/typedefsfilter.h"

TypesDialog::TypesDialog(RDContext* ctx, QWidget* parent)
    : QDialog{parent}, m_ui{this} {

    auto* tdeffiltermodel = new TypedefsFilterModel(ctx, false, this);
    tdeffiltermodel->sort(0, Qt::AscendingOrder);

    m_ui.cbxtypes->setModel(tdeffiltermodel);
    m_ui.cbxtypes->setCurrentIndex(0);

    m_ui.cbxmod->addItem("NONE", RD_TYPE_NONE);
    m_ui.cbxmod->addItem("PTR", RD_TYPE_PTR);
    m_ui.cbxmod->addItem("CPTR", RD_TYPE_CPTR);

    m_ui.sbcount->setValue(0);
}

QString TypesDialog::selected_type() const {
    return m_ui.cbxtypes->currentText();
}

usize TypesDialog::selected_count() const {
    return static_cast<usize>(m_ui.sbcount->value());
}

RDTypeModifier TypesDialog::selected_modifier() const {
    return static_cast<RDTypeModifier>(m_ui.cbxmod->currentData().toUInt());
}
