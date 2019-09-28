#include "widget.h"
#include "ui_widget.h"

#include "CaptureItemDelegate.h"
#include <QDebug>
#include <QStandardItemModel>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Set the directory manually
    QDir dir ("/home/dmvictor/Pictures");

    dir.setSorting(QDir::Time);

    QFileInfoList pathList = dir.entryInfoList(QDir::Files);
    QStringList images = dir.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);

    QStandardItemModel *pModel = new QStandardItemModel();

    for (int i=0; i<pathList.size(); ++i) {
        QStandardItem *pItem = new QStandardItem;
        CaptureItemData itemData;
        itemData.snapshot = images.at(pathList.size()-1-i);
        itemData.imgPath = pathList.at(pathList.size()-1-i).filePath();
        pItem->setData(QVariant::fromValue(itemData), Qt::UserRole+1);
        pModel->appendRow(pItem);
    }

    CaptureItemDelegate *pItemDelegate = new CaptureItemDelegate(this);
    ui->listView->setItemDelegate(pItemDelegate);
    ui->listView->setModel(pModel);

    QItemSelectionModel * selectionModel = ui->listView->selectionModel();
    connect(selectionModel,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,
            SLOT(selectionChangedSlot(QItemSelection,QItemSelection)));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::selectionChangedSlot(const QItemSelection &oldSelection, const QItemSelection &newSelection)
{
    QModelIndex currentIndex = ui->listView->selectionModel()->currentIndex();

    QVariant var = currentIndex.data(Qt::UserRole+1);
    CaptureItemData itemData = var.value<CaptureItemData>();

    qDebug() << itemData.imgPath << + " clicked in the list";

    ui->imgLabel->setPixmap(QPixmap::fromImage(QImage(itemData.imgPath)));
}
