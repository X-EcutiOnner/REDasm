#pragma once

#include <QDialog>
#include "../../models/referencesmodel.h"

namespace Ui {
class ReferencesDialog;
}

class ReferencesDialog : public QDialog
{
    Q_OBJECT

    public:
        explicit ReferencesDialog(const RDContextPtr& ctx, const RDSymbol *symbol, QWidget *parent = nullptr);
        ~ReferencesDialog();

    private slots:
        void on_tvReferences_doubleClicked(const QModelIndex &index);

    private:
        Ui::ReferencesDialog *ui;
        RDContextPtr m_context;
        ReferencesModel* m_referencesmodel;
};
