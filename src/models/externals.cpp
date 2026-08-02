#include "externals.h"
#include "support/utils.h"

ExternalsModel::ExternalsModel(RDContext* ctx, RDExternalKind kind,
                               QObject* parent)
    : QAbstractListModel{parent}, m_context{ctx} {
    m_externals = rd_get_all_externals(ctx, kind);
}

RDAddress ExternalsModel::address(const QModelIndex& index) const {
    return rd_slice_at(m_externals, index.row()).address;
}

QVariant ExternalsModel::data(const QModelIndex& index, int role) const {
    if(role == Qt::DisplayRole) {
        RDExternal ext = rd_slice_at(m_externals, index.row());

        switch(index.column()) {
            case 0: return utils::to_hex(ext.address, m_context);

            case 1:
                return ext.ordinal.has_value
                           ? QString::number(ext.ordinal.value, 10)
                           : QString{};

            case 2: return rd_get_name(m_context, ext.address);

            case 3:
                return ext.module ? QString::fromUtf8(ext.module) : QString{};

            case 4: {
                if(rd_has_refs_to(m_context, ext.address)) return "YES";
                return "NO";
            }

            default: break;
        }
    }
    else if(role == Qt::TextAlignmentRole) {
        if(index.column() <= 1) return Qt::AlignRight;
        return Qt::AlignLeft;
    }

    return {};
}

QVariant ExternalsModel::headerData(int section, Qt::Orientation orientation,
                                    int role) const {
    if(orientation == Qt::Vertical || role != Qt::DisplayRole) return {};

    switch(section) {
        case 0: return "Address";
        case 1: return "Ordinal";
        case 2: return "Name";
        case 3: return "Module";
        case 4: return "Has XRefs";
        default: break;
    }

    return {};
}

int ExternalsModel::columnCount(const QModelIndex&) const { return 5; }

int ExternalsModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(rd_slice_length(m_externals));
}
