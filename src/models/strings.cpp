#include "strings.h"
#include "support/utils.h"

StringsModel::StringsModel(RDContext* ctx, QObject* parent)
    : SymbolsFilterModel{ctx, RD_SYMBOL_TYPE, true, 1, parent} {}

RDAddress StringsModel::address(const QModelIndex& index) const {
    return this->symbols_model()->address(index);
}

QVariant StringsModel::data(const QModelIndex& index, int role) const {
    if(role == Qt::DisplayRole) {
        QModelIndex srcindex = this->mapToSource(index);
        RDContext* ctx = this->symbols_model()->context();
        RDSymbol sym = this->symbols_model()->symbol(srcindex);

        switch(index.column()) {
            case 0: {
                return utils::to_hex(sym.address,
                                     this->symbols_model()->context());
            }

            case 1: return QString::number(sym.type.count);
            case 2: return QString::fromUtf8(rd_typedef_name(sym.type.def));

            case 3: {
                RDSymbol symbol = this->symbols_model()->symbol(srcindex);
                return rd_symbol_to_string(&symbol, ctx);
            }

            case 4: {
                if(rd_has_refs_to(ctx, sym.address)) return "YES";
                return "NO";
            }

            default: break;
        }
    }
    else if(role == Qt::TextAlignmentRole) {
        if(index.column() == 0) return Qt::AlignRight;
        if((index.column() == 2) || (index.column() == 3)) return Qt::AlignLeft;
    }

    return SymbolsFilterModel::data(index, role);
}

QVariant StringsModel::headerData(int section, Qt::Orientation orientation,
                                  int role) const {
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch(section) {
            case 0: return "Address";
            case 1: return "Length";
            case 2: return "Type";
            case 3: return "String";
            case 4: return "Has XRefs";
            default: break;
        }
    }

    return SymbolsFilterModel::headerData(section, orientation, role);
}

int StringsModel::columnCount(const QModelIndex&) const { return 5; }

bool StringsModel::filterAcceptsRow(int source_row,
                                    const QModelIndex& source_parent) const {
    if(!SymbolsFilterModel::filterAcceptsRow(source_row, source_parent))
        return false;

    QModelIndex index = this->symbols_model()->index(source_row, 2);
    RDSymbol sym = this->symbols_model()->symbol(index);
    return sym.kind == RD_SYMBOL_TYPE && rd_type_is_string(&sym.type);
}
