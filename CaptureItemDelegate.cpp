#include <QPainter>
#include <QDebug>
#include "CaptureItemDelegate.h"

CaptureItemDelegate::CaptureItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{

}

void CaptureItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (index.isValid()) {
        painter->save();
        QVariant var = index.data(Qt::UserRole+1);
        CaptureItemData itemData = var.value<CaptureItemData>();


        QRectF rect;
        rect.setX(option.rect.x());
        rect.setY(option.rect.y());
        rect.setWidth(option.rect.width()-1);
        rect.setHeight(option.rect.height()-1);


        QPainterPath path;
        path.moveTo(rect.topRight());
        path.lineTo(rect.topLeft());
        path.quadTo(rect.topLeft(), rect.topLeft());
        path.lineTo(rect.bottomLeft());
        path.quadTo(rect.bottomLeft(), rect.bottomLeft());
        path.lineTo(rect.bottomRight());
        path.quadTo(rect.bottomRight(), rect.bottomRight());
        path.lineTo(rect.topRight());
        path.quadTo(rect.topRight(), rect.topRight());


        if (option.state.testFlag(QStyle::State_Selected)) {
            painter->setPen(QPen(QColor("#e3e3e5")));
            painter->setBrush(QColor("#e3e3e5"));
            painter->drawPath(path);
        }

        QRectF imgRect = QRect(rect.left()+5, rect.top()+15, 180, 180);
        QRectF filenameRect = QRect(rect.left()+5, rect.top(), 180, 20);


        painter->drawImage(imgRect, QImage(itemData.imgPath));
        painter->setPen(QPen(Qt::black));
        painter->setFont(QFont("Microsoft Yahei", 10));
        painter->drawText(filenameRect, itemData.snapshot);


        painter->restore();
    }
}

QSize CaptureItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index)
    return QSize(option.rect.width(), 200);
}
