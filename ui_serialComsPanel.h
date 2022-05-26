/********************************************************************************
** Form generated from reading UI file 'serialComsPanelBAHwCq.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef SERIALCOMSPANELBAHWCQ_H
#define SERIALCOMSPANELBAHWCQ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serialComsPanel
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_8;
    QTextEdit *console_rx_vars;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_4;
    //QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_10;
    QTextEdit *console_rx_raw;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_7;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_9;
    QTextEdit *console_tx_vars;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_5;
    //QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_4;
    QVBoxLayout *verticalLayout_11;
    QTextEdit *console_tx_raw;
    QFrame *line;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton_3;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton_6;
    QToolButton *toolButton_7;
    QToolButton *toolButton_2;
    QSpacerItem *horizontalSpacer_3;
    //QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QFrame *line_2;

    void setupUi(QWidget *serialComsPanel)
    {
        if (serialComsPanel->objectName().isEmpty())
            serialComsPanel->setObjectName(QString::fromUtf8("serialComsPanel"));
        serialComsPanel->resize(1423, 417);
        verticalLayout = new QVBoxLayout(serialComsPanel);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_2 = new QGroupBox(serialComsPanel);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setAlignment(Qt::AlignCenter);
        horizontalLayout_2 = new QHBoxLayout(groupBox_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setAlignment(Qt::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_7 = new QGroupBox(groupBox_3);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        verticalLayout_6 = new QVBoxLayout(groupBox_7);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        scrollArea = new QScrollArea(groupBox_7);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 648, 101));
        verticalLayout_8 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        console_rx_vars = new QTextEdit(scrollAreaWidgetContents);
        console_rx_vars->setObjectName(QString::fromUtf8("console_rx_vars"));
        console_rx_vars->setReadOnly(true);
        console_rx_vars->setMinimumHeight(2500);

        verticalLayout_8->addWidget(console_rx_vars);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_6->addWidget(scrollArea);


        verticalLayout_2->addWidget(groupBox_7);

        groupBox_5 = new QGroupBox(groupBox_3);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_4 = new QVBoxLayout(groupBox_5);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        //scrollArea_3 = new QScrollArea(groupBox_5);
        //scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        //scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 648, 100));
        verticalLayout_10 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        console_rx_raw = new QTextEdit(scrollAreaWidgetContents_3);
        console_rx_raw->setObjectName(QString::fromUtf8("console_rx_raw"));
        console_rx_raw->setReadOnly(true);

        verticalLayout_10->addWidget(console_rx_raw);

        //scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_4->addWidget(console_rx_raw);


        verticalLayout_2->addWidget(groupBox_5);


        horizontalLayout_2->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(groupBox_2);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setAlignment(Qt::AlignCenter);
        verticalLayout_3 = new QVBoxLayout(groupBox_4);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_8 = new QGroupBox(groupBox_4);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        verticalLayout_7 = new QVBoxLayout(groupBox_8);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        scrollArea_2 = new QScrollArea(groupBox_8);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 647, 101));
        verticalLayout_9 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        console_tx_vars = new QTextEdit(scrollAreaWidgetContents_2);
        console_tx_vars->setObjectName(QString::fromUtf8("console_tx_vars"));
        console_tx_vars->setReadOnly(true);
        console_tx_vars->setMinimumHeight(2500);
        verticalLayout_9->addWidget(console_tx_vars);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_7->addWidget(scrollArea_2);


        verticalLayout_3->addWidget(groupBox_8);

        groupBox_6 = new QGroupBox(groupBox_4);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        verticalLayout_5 = new QVBoxLayout(groupBox_6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        //scrollArea_4 = new QScrollArea(groupBox_6);
        //scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        //scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 647, 100));
        verticalLayout_11 = new QVBoxLayout(scrollAreaWidgetContents_4);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        console_tx_raw = new QTextEdit(scrollAreaWidgetContents_4);
        console_tx_raw->setObjectName(QString::fromUtf8("console_tx_raw"));
        console_tx_raw->setReadOnly(true);

        verticalLayout_11->addWidget(console_tx_raw);

        //scrollArea_4->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_5->addWidget(console_tx_raw);


        verticalLayout_3->addWidget(groupBox_6);


        horizontalLayout_2->addWidget(groupBox_4);

        QFrame *Vertical_gripline = new QFrame();
           Vertical_gripline->setLineWidth(2);
           Vertical_gripline->setGeometry(QRect(320, 150, 118, 3));
           Vertical_gripline->setFrameShape(QFrame::HLine);
           Vertical_gripline->setFrameShadow(QFrame::Plain);
           Vertical_gripline->setStyleSheet("color: #b78620;");

        verticalLayout->setContentsMargins(9,0,9,9);    //top margin needs to be zero for gripline to work right
        verticalLayout->addWidget(Vertical_gripline);
        verticalLayout->addWidget(groupBox_2);

        line = new QFrame(serialComsPanel);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        groupBox = new QGroupBox(serialComsPanel);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 5, 0, 5);
        toolButton_3 = new QToolButton(groupBox);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setEnabled(true);
        toolButton_3->setCheckable(false);
        toolButton_3->setAutoRaise(false);

        horizontalLayout->addWidget(toolButton_3);

        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        horizontalLayout->addWidget(toolButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        toolButton_4 = new QToolButton(groupBox);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));

        horizontalLayout->addWidget(toolButton_4);

        toolButton_5 = new QToolButton(groupBox);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));

        horizontalLayout->addWidget(toolButton_5);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButton_6 = new QToolButton(groupBox);
        toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));

        horizontalLayout->addWidget(toolButton_6);

        toolButton_7 = new QToolButton(groupBox);
        toolButton_7->setObjectName(QString::fromUtf8("toolButton_7"));

        horizontalLayout->addWidget(toolButton_7);

        toolButton_2 = new QToolButton(groupBox);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));

        horizontalLayout->addWidget(toolButton_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        //radioButton_2 = new QRadioButton(groupBox);
        //radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        //horizontalLayout->addWidget(radioButton_2);

        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        horizontalLayout->addWidget(radioButton);


        verticalLayout->addWidget(groupBox);

        line_2 = new QFrame(serialComsPanel);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        console_rx_raw->setFontPointSize(8);
        console_tx_raw->setFontPointSize(8);
        console_rx_vars->setFontPointSize(8);
        console_tx_vars->setFontPointSize(8);

        console_rx_raw->setPalette(QColor(80, 80, 80));
        console_tx_raw->setPalette(QColor(80, 80, 80));
        console_rx_vars->setPalette(QColor(128, 128, 128));
        console_tx_vars->setPalette(QColor(128, 128, 128));
        scrollArea->setPalette(QColor(128, 128, 128));
        scrollArea_2->setPalette(QColor(128, 128, 128));
        retranslateUi(serialComsPanel);

        QMetaObject::connectSlotsByName(serialComsPanel);
    } // setupUi

    void retranslateUi(QWidget *serialComsPanel)
    {
        serialComsPanel->setWindowTitle(QCoreApplication::translate("serialComsPanel", "Form", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("serialComsPanel", "Serial Coms Panel", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("serialComsPanel", "RECEIVE DATA", nullptr));
        groupBox_7->setTitle(QCoreApplication::translate("serialComsPanel", "Variables", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("serialComsPanel", "Raw RX", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("serialComsPanel", "SEND DATA", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("serialComsPanel", "Variables", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("serialComsPanel", "RAW TX", nullptr));
        groupBox->setTitle(QString());
        toolButton_3->setText(QCoreApplication::translate("serialComsPanel", "COM5", nullptr));
        toolButton->setText(QCoreApplication::translate("serialComsPanel", "Baudrate: 115200", nullptr));
        toolButton_4->setText(QCoreApplication::translate("serialComsPanel", "Vendor ID: 0x16c0", nullptr));
        toolButton_5->setText(QCoreApplication::translate("serialComsPanel", "Device Serial #: 7576620", nullptr));
        toolButton_6->setText(QCoreApplication::translate("serialComsPanel", "RX: 100Hz", nullptr));
        toolButton_7->setText(QCoreApplication::translate("serialComsPanel", "TX: 100Hz", nullptr));
        toolButton_2->setText(QCoreApplication::translate("serialComsPanel", "Lost packets: 0", nullptr));
        //radioButton_2->setText(QCoreApplication::translate("serialComsPanel", "Log raw TX / RX", nullptr));
        radioButton->setText(QCoreApplication::translate("serialComsPanel", "Log Variables", nullptr));
    } // retranslateUi

};

namespace Ui {
    class serialComsPanel: public Ui_serialComsPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // SERIALCOMSPANELBAHWCQ_H
