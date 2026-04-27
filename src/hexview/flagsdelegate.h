#pragma once

#include <QHexView/qhexview.h>
#include <redasm/redasm.h>

class FlagsDelegate: public QHexDelegate {
    Q_OBJECT

public:
    explicit FlagsDelegate(QObject* parent = nullptr);
    void set_flags_buffer(const RDFlagsBuffer* flags);

public:
    QString comment(quint64 offset, quint8 b,
                    const QHexView* hexview) const override;
    bool renderByte(quint64 offset, quint8 b, QHexCharFormat& outcf,
                    const QHexView* hexview) const override;

private:
    const RDFlagsBuffer* m_flags{nullptr};
};
