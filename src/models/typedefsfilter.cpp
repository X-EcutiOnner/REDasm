#include "typedefsfilter.h"

TypedefsFilterModel::TypedefsFilterModel(RDContext* ctx, QObject* parent)
    : QSortFilterProxyModel{parent} {
    this->setSourceModel(new TypedefsModel(ctx, this));
    this->setFilterKeyColumn(0);
}

const RDTypeDef* TypedefsFilterModel::type_def(const QModelIndex& index) const {
    QModelIndex srcindex = this->mapToSource(index);
    return this->typedefs_model()->type_def(srcindex);
}

bool TypedefsFilterModel::filterAcceptsRow(int source_row,
                                           const QModelIndex&) const {
    QModelIndex index = this->sourceModel()->index(source_row, 0);
    const RDTypeDef* tdef = this->typedefs_model()->type_def(index);
    if(rd_typedef_is_builtin(tdef)) return false;

    QString s = index.data().toString();
    return s.contains(this->filterRegularExpression());
}
