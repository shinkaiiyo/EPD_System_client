#include "iteminformation.h"
#include "ui_iteminformation.h"
#include <QStandardItemModel>
#include "javaconnect.h"
#include "success.h"

ItemInformation::ItemInformation(const QString& items,QWidget *parent) :
    QWidget(parent),items(items),
    ui(new Ui::itemInformation)
{
    ui->setupUi(this);
    setBaseSize(380,380);
    setWindowTitle("商品信息");
    QStringList itemsList = this->items.split(",");
    QStringList nameList,finalList;
    for (int m = 0; m < itemsList.length(); m++)
    {
        nameList = itemsList[m].split("\u0001");
        finalList.append(nameList[0]);
    }
    this->ui->cbItems->addItems(finalList);
    this->ui->cbItems->show();
    auto standItemModel = new QStandardItemModel();
    //添加表头
    standItemModel->setColumnCount(8);
    standItemModel->setHeaderData(0,Qt::Horizontal,QStringLiteral("商品名称"));
    standItemModel->setHeaderData(1,Qt::Horizontal,QStringLiteral("品牌"));
    standItemModel->setHeaderData(2,Qt::Horizontal,QStringLiteral("产地"));
    standItemModel->setHeaderData(3,Qt::Horizontal,QStringLiteral("规格"));
    standItemModel->setHeaderData(4,Qt::Horizontal,QStringLiteral("货号"));
    standItemModel->setHeaderData(5,Qt::Horizontal,QStringLiteral("条码"));
    standItemModel->setHeaderData(6,Qt::Horizontal,QStringLiteral("售价"));
    standItemModel->setHeaderData(7,Qt::Horizontal,QStringLiteral("原价"));
    for (int i = 0; i < itemsList.length(); i++) {
        QStringList itemList = itemsList[i].split("\u0001");
        for(int j = 0;j<itemList.length();j++)
        {
            QStandardItem *standItem1 = new QStandardItem(itemList[j]);
            standItemModel->setItem(i,j,standItem1);                                //表格第i行，第j列添加一项内容
            standItemModel->item(i,j)->setForeground(QBrush(QColor(0,0,0)));      //设置字符颜色
            standItemModel->item(i,j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    ui->tableView->setModel(standItemModel);
    connect(this->ui->btnExit,SIGNAL(clicked(bool)),this,SLOT(shutdown()));
    connect(this->ui->btnDelete,SIGNAL(clicked(bool)),this,SLOT(del()));
}

void ItemInformation::del()
{
    QString itemToDelete = this->ui->cbItems->currentText();
    JavaConnect * jc = new JavaConnect;
    jc->client();
    jc->sendmsg("14");
    jc->sendmsg(itemToDelete);
    jc->sendmsg(spname);
    Success * sc = new Success;
    sc->show();
}

void ItemInformation::shutdown()
{
    this->close();
}

ItemInformation::~ItemInformation()
{
    delete ui;
}
