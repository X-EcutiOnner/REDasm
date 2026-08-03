#pragma once

#include "typedefs.h"
#include <QSortFilterProxyModel>
#include <redasm/redasm.h>

class TypedefsFilterModel: public QSortFilterProxyModel {
    Q_OBJECT

public:
    explicit TypedefsFilterModel(RDContext* ctx, bool filter_builtins,
                                 QObject* parent = nullptr);
    [[nodiscard]] const RDTypeDef* type_def(const QModelIndex& index) const;

    [[nodiscard]] const TypedefsModel* typedefs_model() const {
        return qobject_cast<const TypedefsModel*>(this->sourceModel());
    }

protected:
    [[nodiscard]] bool lessThan(const QModelIndex& source_left,
                                const QModelIndex& source_right) const override;
    [[nodiscard]] bool filterAcceptsRow(int source_row,
                                        const QModelIndex&) const override;

private:
    bool m_filterbuiltins;
};
