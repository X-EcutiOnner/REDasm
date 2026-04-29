#include "loader.h"
#include "support/utils.h"
#include <QPushButton>

LoaderDialog::LoaderDialog(RDContextSlice ctxslice, QWidget* parent)
    : QDialog{parent}, m_ui{this}, m_contextslice{ctxslice} {
    utils::configure_hex_input(m_ui.leentrypoint);
    utils::configure_hex_input(m_ui.leaddress);
    utils::configure_hex_input(m_ui.leoffset);

    m_ui.gbaddressing->setEnabled(false);
    m_ui.leentrypoint->setText(QString{"0"}.repeated(sizeof(u32) * 2));
    m_ui.leaddress->setText(QString{"0"}.repeated(sizeof(u32) * 2));
    m_ui.leoffset->setText(QString{"0"}.repeated(sizeof(u32) * 2));

    this->populate_processors();

    for(usize i = 0; i < rd_slice_length(m_contextslice); i++) {
        const RDLoaderPlugin* lp =
            rd_get_loader_plugin(rd_slice_at(m_contextslice, i));
        m_ui.lwloaders->addItem(lp->name);
    }

    connect(m_ui.lwloaders, &QListWidget::currentRowChanged, this,
            &LoaderDialog::on_loader_changed);

    connect(m_ui.cbprocessors, &QComboBox::currentIndexChanged, this,
            &LoaderDialog::on_processor_changed);

    connect(m_ui.sbminstring, &QSpinBox::valueChanged, this,
            &LoaderDialog::update_min_string);

    connect(m_ui.leentrypoint, &QLineEdit::textChanged, this,
            &LoaderDialog::update_entry_point);

    connect(m_ui.leaddress, &QLineEdit::textChanged, this,
            &LoaderDialog::update_address);

    connect(m_ui.leoffset, &QLineEdit::textChanged, this,
            &LoaderDialog::update_offset);

    // Trigger "on_loader_changed"
    if(!rd_slice_is_empty(m_contextslice)) m_ui.lwloaders->setCurrentRow(0);

    this->validate_fields();
}

void LoaderDialog::on_loader_changed(int currentrow) {
    if(currentrow != -1) {
        this->context = rd_slice_at(m_contextslice, currentrow);
        m_ui.sbminstring->setValue(rd_get_min_string(this->context));

        const RDLoaderPlugin* l = rd_get_loader_plugin(this->context);
        const char* procid = rd_processor_get_id(this->context);

        m_ui.gbaddressing->setEnabled(l->flags & RD_LF_MANUAL);

        for(int i = 0; i < m_ui.cbprocessors->count(); i++) {
            if(m_ui.cbprocessors->itemData(i).toString() == procid) {
                m_ui.cbprocessors->setCurrentIndex(i);
                return;
            }
        }

        m_ui.cbprocessors->setCurrentIndex(-1);
    }
    else {
        m_ui.gbaddressing->setEnabled(false);
        this->context = nullptr;
    }

    this->validate_fields();
}

void LoaderDialog::on_processor_changed(int currentrow) {
    int loaderidx = m_ui.lwloaders->currentRow();

    if(loaderidx != -1 && currentrow != -1) {
        QVariant data = m_ui.cbprocessors->itemData(currentrow);
        this->processorplugin =
            rd_processor_find(qUtf8Printable(data.toString()));
    }
    else
        this->processorplugin = nullptr;

    this->validate_fields();
}

void LoaderDialog::populate_processors() const {
    RDPluginSlice plugins = rd_get_all_processor_plugins();

    const RDPlugin** it;
    rd_slice_each(it, plugins) {
        m_ui.cbprocessors->addItem((*it)->processor->name,
                                   (*it)->processor->id);
    }
}

void LoaderDialog::update_min_string() { // NOLINT
    if(!this->context) return;
    rd_set_min_string(this->context, m_ui.sbminstring->value());
}

void LoaderDialog::update_entry_point() {
    this->addressing.entrypoint =
        m_ui.leentrypoint->text().toULongLong(nullptr, 16);
    this->validate_fields();
}

void LoaderDialog::update_address() {
    this->addressing.address =
        m_ui.leentrypoint->text().toULongLong(nullptr, 16);
    this->validate_fields();
}

void LoaderDialog::update_offset() {
    this->addressing.offset = m_ui.leoffset->text().toULongLong(nullptr, 16);
    this->validate_fields();
}

void LoaderDialog::validate_fields() { // NOLINT
    QPushButton* pb = m_ui.buttonbox->button(QDialogButtonBox::Ok);

    if(!this->context || m_ui.cbprocessors->currentIndex() == -1) {
        pb->setEnabled(false);
        return;
    }

    const RDLoaderPlugin* l = rd_get_loader_plugin(this->context);

    if(l->flags & RD_LF_MANUAL) {
        pb->setEnabled(!m_ui.leentrypoint->text().isEmpty() &&
                       !m_ui.leaddress->text().isEmpty() &&
                       !m_ui.leoffset->text().isEmpty());
    }
    else
        pb->setEnabled(true);
}
