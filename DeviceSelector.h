/********************************************************************************
** Form generated from reading UI file 'designerJzepKg.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef DESIGNERJZEPKG_H
#define DESIGNERJZEPKG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <QObject>

QT_BEGIN_NAMESPACE

class Ui_DeviceSelector : public QObject
{
    Q_OBJECT

public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_7;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_8;
    QComboBox *comboBox_2;
    QPushButton *pushButton_2;

    void setupUi(QWidget *DeviceSelector)
    {
        if (DeviceSelector->objectName().isEmpty())
            DeviceSelector->setObjectName(QString::fromUtf8("DeviceSelector"));
        DeviceSelector->resize(451, 251);
        verticalLayout = new QVBoxLayout(DeviceSelector);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 9, -1, -1);
        tabWidget = new QTabWidget(DeviceSelector);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayout_4 = new QVBoxLayout(tab);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setPointSize(8);
        font.setBold(false);
        font.setWeight(50);
        groupBox->setFont(font);
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(-1, 20, -1, -1);
        scrollArea = new QScrollArea(groupBox);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 387, 114));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setSpacing(20);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(20, 20, 20, 20);
        comboBox = new QComboBox(groupBox_3);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout_5->addWidget(comboBox);


        verticalLayout_3->addWidget(groupBox_3);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);


        verticalLayout_4->addWidget(groupBox);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_9 = new QVBoxLayout(tab_2);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        verticalLayout_6 = new QVBoxLayout(groupBox_2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, 20, -1, -1);
        scrollArea_2 = new QScrollArea(groupBox_2);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 387, 114));
        verticalLayout_7 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        groupBox_4 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_8 = new QVBoxLayout(groupBox_4);
        verticalLayout_8->setSpacing(20);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(20, 20, 20, 20);
        comboBox_2 = new QComboBox(groupBox_4);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));

        verticalLayout_8->addWidget(comboBox_2);


        verticalLayout_7->addWidget(groupBox_4);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_6->addWidget(scrollArea_2);

        pushButton_2 = new QPushButton(groupBox_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_6->addWidget(pushButton_2);


        verticalLayout_9->addWidget(groupBox_2);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(DeviceSelector);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DeviceSelector);

        connect(pushButton, &QPushButton::clicked, DeviceSelector, &QWidget::close);
        connect(pushButton_2, &QPushButton::clicked, DeviceSelector, &QWidget::close);

    } // setupUi

    void retranslateUi(QWidget *DeviceSelector)
    {
        DeviceSelector->setWindowTitle(QCoreApplication::translate("DeviceSelector", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("DeviceSelector", "Multiple Devices with Vendor ID attached. Please select correct device from list:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("DeviceSelector", "Matching devices:", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("DeviceSelector", "Device #01", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("DeviceSelector", "Device #02", nullptr));

        pushButton->setText(QCoreApplication::translate("DeviceSelector", "SELECT", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("DeviceSelector", "Matching Vendor ID", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("DeviceSelector", "Select Alternate Device:", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("DeviceSelector", "Alternate Devices:", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("DeviceSelector", "Device #01", nullptr));
        comboBox_2->setItemText(1, QCoreApplication::translate("DeviceSelector", "Device #02", nullptr));

        pushButton_2->setText(QCoreApplication::translate("DeviceSelector", "SELECT", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("DeviceSelector", "Other devices", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DeviceSelector: public Ui_DeviceSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // DESIGNERJZEPKG_H
