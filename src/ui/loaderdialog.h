#pragma once

#include <QBoxLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QSpinBox>

namespace ui {

struct LoaderDialog {
    QListWidget* lwloaders;
    QGroupBox *gboptions, *gbloader, *gbaddressing;
    QComboBox* cbprocessors;
    QSpinBox* sbminstring;
    QLineEdit *leentrypoint, *leoffset, *leaddress;
    QDialogButtonBox* buttonbox;

    explicit LoaderDialog(QDialog* self) {
        self->setAttribute(Qt::WA_DeleteOnClose);
        self->setWindowTitle("Loader");
        self->resize(540, 550);
        self->setModal(true);

        auto* vbox = new QVBoxLayout(self);
        this->setup_top(vbox);
        this->setup_bottom(vbox);

        this->buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok |
                                               QDialogButtonBox::Cancel);

        QObject::connect(this->buttonbox, &QDialogButtonBox::accepted, self,
                         &QDialog::accept);
        QObject::connect(this->buttonbox, &QDialogButtonBox::rejected, self,
                         &QDialog::reject);

        vbox->addWidget(this->buttonbox);
    }

private:
    void setup_top(QVBoxLayout* l) {
        l->addWidget(new QLabel("Select a Loader from the list below"));

        this->lwloaders = new QListWidget();
        this->lwloaders->setEditTriggers(QAbstractItemView::NoEditTriggers);
        this->lwloaders->setUniformItemSizes(true);
        l->addWidget(this->lwloaders);
    }

    void setup_bottom(QVBoxLayout* l) {
        auto* vbox = new QVBoxLayout();
        this->setup_loader_part(vbox);
        this->setup_addressing_part(vbox);
        l->addLayout(vbox);
    }

    void setup_loader_part(QVBoxLayout* l) {
        this->gbloader = new QGroupBox();
        this->gbloader->setTitle("Loader");

        this->cbprocessors = new QComboBox();

        this->sbminstring = new QSpinBox();
        this->sbminstring->setMinimum(1);
        this->sbminstring->setMaximum(100);

        auto* form = new QFormLayout(this->gbloader);
        form->setLabelAlignment(Qt::AlignRight);
        form->addRow("Processor:", this->cbprocessors);
        form->addRow("Min String:", this->sbminstring);
        l->addWidget(this->gbloader);
    }

    void setup_addressing_part(QVBoxLayout* l) {
        this->gbaddressing = new QGroupBox();
        this->gbaddressing->setTitle("Addressing");

        this->leentrypoint = new QLineEdit();
        this->leaddress = new QLineEdit();
        this->leoffset = new QLineEdit();

        auto* form = new QFormLayout(this->gbaddressing);
        form->setLabelAlignment(Qt::AlignRight);
        form->addRow("Entry Point:", this->leentrypoint);
        form->addRow("Address:", this->leaddress);
        form->addRow("Offset:", this->leoffset);
        l->addWidget(this->gbaddressing);
    }
};

} // namespace ui
