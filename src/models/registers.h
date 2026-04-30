#pragma once

#include <QAbstractListModel>
#include <redasm/redasm.h>

class RegistersModel: public QAbstractListModel {
    Q_OBJECT

public:
    explicit RegistersModel(RDContext* ctx, QObject* parent = nullptr);
    [[nodiscard]] RDAddress address(const QModelIndex& index) const;
    void update();

public:
    [[nodiscard]] int rowCount(const QModelIndex&) const override;
    [[nodiscard]] int columnCount(const QModelIndex&) const override;
    [[nodiscard]] QVariant data(const QModelIndex& index,
                                int role) const override;
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation,
                                      int role) const override;

private:
    RDContext* m_context;
    RDTrackedRegisterSlice m_registers{};
};
