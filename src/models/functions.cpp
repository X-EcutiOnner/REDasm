#include "functions.h"

FunctionsModel::FunctionsModel(RDContext* ctx, QObject* parent)
    : QAbstractListModel{parent}, m_context{ctx} {
    this->resync();
}

void FunctionsModel::resync() {
    this->beginResetModel();
    m_functions = rd_get_all_functions_address(m_context);
    this->endResetModel();
}

RDAddress FunctionsModel::address(const QModelIndex& index) const {
    return rd_slice_at(m_functions, index.row());
}

QVariant FunctionsModel::data(const QModelIndex& index, int role) const {
    if(role == Qt::DisplayRole) {
        RDAddress addr = rd_slice_at(m_functions, index.row());

        switch(index.column()) {
            case 0: return QString::fromUtf8(rd_to_hexaddr(m_context, addr));
            case 1: return QString::fromUtf8(rd_get_name(m_context, addr));
            default: break;
        }
    }
    else if(role == Qt::TextAlignmentRole)
        return Qt::AlignLeft;

    return {};
}

QVariant FunctionsModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
    if(orientation == Qt::Vertical || role != Qt::DisplayRole) return {};

    switch(section) {
        case 0: return "Address";
        case 1: return "Function";
        default: break;
    }

    return {};
}

int FunctionsModel::columnCount(const QModelIndex&) const { return 2; }

int FunctionsModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(rd_slice_length(m_functions));
}
