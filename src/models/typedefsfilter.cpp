#include "typedefsfilter.h"
#include <cstring>

TypedefsFilterModel::TypedefsFilterModel(RDContext* ctx, bool filter_builtins,
                                         QObject* parent)
    : QSortFilterProxyModel{parent}, m_filterbuiltins{filter_builtins} {
    this->setFilterKeyColumn(0);
    this->setDynamicSortFilter(true);
    this->setSourceModel(new TypedefsModel(ctx, this));
}

const RDTypeDef* TypedefsFilterModel::type_def(const QModelIndex& index) const {
    QModelIndex srcindex = this->mapToSource(index);
    return this->typedefs_model()->type_def(srcindex);
}

bool TypedefsFilterModel::lessThan(const QModelIndex& source_left,
                                   const QModelIndex& source_right) const {
    const RDTypeDef* l_tdef = this->typedefs_model()->type_def(source_left);
    const RDTypeDef* r_tdef = this->typedefs_model()->type_def(source_right);

    int s = strcmp(rd_typedef_name(l_tdef), rd_typedef_name(r_tdef));
    if(s == 0) return rd_typedef_kind(l_tdef) < rd_typedef_kind(r_tdef);
    return s < 0;
}

bool TypedefsFilterModel::filterAcceptsRow(int source_row,
                                           const QModelIndex&) const {
    QModelIndex index = this->sourceModel()->index(source_row, 0);
    const RDTypeDef* tdef = this->typedefs_model()->type_def(index);
    if(m_filterbuiltins && rd_typedef_is_builtin(tdef)) return false;

    QString s = index.data().toString();
    return s.contains(this->filterRegularExpression());
}
