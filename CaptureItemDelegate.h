#ifndef CAPTUREITEMDELEGATE_H
#define CAPTUREITEMDELEGATE_H


#include <QStyledItemDelegate>
#include <QMetaType>

class CaptureItemDelegate: public QStyledItemDelegate
{
public:
    CaptureItemDelegate(QObject *parent = nullptr);

    // painting
    void paint(QPainter *painter,
               const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const Q_DECL_OVERRIDE;
};

typedef struct {
    QString imgPath;
    QString snapshot;
} CaptureItemData;

Q_DECLARE_METATYPE(CaptureItemData)


#endif // CAPTUREITEMDELEGATE_H
