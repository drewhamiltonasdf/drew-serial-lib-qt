#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtUiTools>




// You must define your device here...
// Look at the pre-defined device types in the "mcu-vendor-id-table.h" file
#define THIS_VENDOR_ID          TEENSY_VENDOR_ID



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    // Automatically find Teensy, and setup to read 3 message types asynchronously: see void setup_serial_protocol()
    // These 3 message types are defined in #include "MsgPack_types.h", and it is completely extensible.

    //Serial setup
        setup_serial_protocol(THIS_VENDOR_ID);
        setup_serialSignalsSlots();
        setup_layout_for_serialComs();
        setup_USB_vendor_downloader();

    //Real-time Chart
        setup_realtime_chart();

    //General Non-serial layout
        setup_layout_for_realtime_chart();

    //Load window geometry settings and default file path etc.
        setup_geometry_Settings();

     //Setup file logging
         setup_file_loggingSignalSlot();

         RX_freq_hz = 666;
         TX_freq_hz = 666;

}

void MainWindow::setup_file_loggingSignalSlot()
{
    MyDataLogger = new dataLogger(this);
    connect(serialComsPanel->radioButton, &QRadioButton::clicked, MyDataLogger, &dataLogger::log_file_selector);
}
void MainWindow::setup_layout_for_realtime_chart()
{
    QFrame *Vertical_gripline = new QFrame();
       Vertical_gripline->setLineWidth(2);
       Vertical_gripline->setGeometry(QRect(320, 150, 118, 3));
       Vertical_gripline->setFrameShape(QFrame::HLine);
       Vertical_gripline->setFrameShadow(QFrame::Plain);
       Vertical_gripline->setStyleSheet("color: #c41818;");
       Vertical_gripline->setContentsMargins(0,0,0,0);
    MainContainerLayout->addWidget(customPlot);
    MainContainerLayout->addWidget(Vertical_gripline);
}
void MainWindow::setup_USB_vendor_downloader()
{
    //Download vendor database locally. Who knows where.
    QUrl usbVendorInfoUrl("http://www.linux-usb.org/usb.ids");
    usb_vendor_downloader = new FileDownloader(usbVendorInfoUrl, this);
    connect(usb_vendor_downloader, SIGNAL (downloaded()), this, SLOT (loadVendorInfo()));
}

void MainWindow::update_RX_hz(float val)
{
    RX_freq_hz = val;      //0.001 just to avoid divide by zero
}
void MainWindow::update_TX_hz(float val)
{
    TX_freq_hz = val;      //0.001 just to avoid divide by zero
}

void MainWindow::update_read_queue_size(int _read_queue_size)
{
    read_queue_size = _read_queue_size;
}
void MainWindow::setup_realtime_chart()
{
  customPlot = new QCustomPlot();
    customPlot->setMinimumHeight(250);
    //demoName = "Real Time Data Demo";

  // include this section to fully disable antialiasing for higher performance:
  /*
  customPlot->setNotAntialiasedElements(QCP::aeAll);
  QFont font;
  font.setStyleStrategy(QFont::NoAntialias);
  customPlot->xAxis->setTickLabelFont(font);
  customPlot->yAxis->setTickLabelFont(font);
  customPlot->legend->setFont(font);
  */
  customPlot->addGraph(); // blue line
  customPlot->graph(0)->setPen(QPen(QColor(120, 120, 120), 2));

  QLinearGradient plotGradient;
  plotGradient.setStart(0, 0);
  plotGradient.setFinalStop(0, 350);
  plotGradient.setColorAt(0, QColor(80, 80, 80));
  plotGradient.setColorAt(1, QColor(50, 50, 50));
  customPlot->setBackground(plotGradient);

  customPlot->xAxis->setBasePen(QPen(Qt::white, 1));
  customPlot->yAxis->setBasePen(QPen(Qt::white, 1));
  customPlot->xAxis->setTickPen(QPen(Qt::white, 1));
  customPlot->yAxis->setTickPen(QPen(Qt::white, 1));
  customPlot->xAxis->setSubTickPen(QPen(Qt::white, 1));
  customPlot->yAxis->setSubTickPen(QPen(Qt::white, 1));
  customPlot->xAxis->setTickLabelColor(Qt::white);
  customPlot->yAxis->setTickLabelColor(Qt::white);
  customPlot->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  customPlot->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
  customPlot->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
  customPlot->xAxis->grid()->setSubGridVisible(true);
  customPlot->yAxis->grid()->setSubGridVisible(true);
  customPlot->xAxis->grid()->setZeroLinePen(Qt::NoPen);
  customPlot->yAxis->grid()->setZeroLinePen(Qt::NoPen);
  customPlot->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
  customPlot->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

  //customPlot->addGraph(); // red line
  //customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

  QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
  timeTicker->setTimeFormat("%h:%m:%s");
  customPlot->xAxis->setTicker(timeTicker);
  customPlot->axisRect()->setupFullAxesBox();
  customPlot->yAxis->setRange(-1.2, 1.2);

  // make left and bottom axes transfer their ranges to right and top axes:
  connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
  connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

}
void MainWindow::closeEvent(QCloseEvent *event)
{
    //Store current save directory so fussy Ophir doesn't have a fit.
    writeSettings();
}
void MainWindow::setup_geometry_Settings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}
void MainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("geometry", saveGeometry());
}

void MainWindow::realtimeDataSlot()
{
  static QTime timeStart = QTime::currentTime();
  // calculate two new data points:
  double key = timeStart.msecsTo(QTime::currentTime())/1000.0; // time elapsed since start of demo, in seconds
  static double lastPointKey = 0;

  int number_of_seconds_to_show_on_chart = 100;

  if (key-lastPointKey > 0.010) // at most add point every 10 ms
  {
    customPlot->graph(0)->addData(key, test_read_class->registers.REGISTER_B);
    customPlot->graph(0)->rescaleValueAxis();
    lastPointKey = key;

    customPlot->xAxis->setRange(key, number_of_seconds_to_show_on_chart, Qt::AlignRight);
    customPlot->replot();

    customPlot->graph(0)->data()->removeBefore(lastPointKey - (number_of_seconds_to_show_on_chart + 1));
  }
}

void MainWindow::loadVendorInfo()
{
 QByteArray vendorInfo;
 vendorInfo = usb_vendor_downloader->downloadedData();

 QString path = qApp->applicationDirPath() + "/local-usb.ids";
 QFile usb_ids_file(path);
 usb_ids_file.open(QIODevice::WriteOnly);
 usb_ids_file.write(vendorInfo);
 usb_ids_file.close();

 //qDebug() << "File written locally";

}
QString MainWindow::findVendorDescription(QString vendor_id_in_hex, QString product_id)
{
    vendor_id_in_hex = vendor_id_in_hex.toLower();
    product_id = product_id.toLower();

    QString returnString_with_description = "not found in database";
    QString companyName;

    QString path = qApp->applicationDirPath() + "/local-usb.ids";

    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "LOCAL COPY NOT FOUND! Implement some backup plan";
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split("  ");

        if (fields.size() > 1)
        {
            if (fields.at(0) == vendor_id_in_hex && !fields.at(0).startsWith("\t"))
            {
                companyName = fields.at(1).trimmed();
                while(!in.atEnd())
                {
                    //"/t0483[space][space]Teensyduino Serial"
                    QString innerline = in.readLine();
                    //if (innerline.startsWith("\t"))
                    //{
                        QStringList innerfield = innerline.split("  ");
                        if (innerfield.size() > 1)
                        {
                            QString prodID = innerfield.at(0).trimmed();
                            //removeLeadingzeros(prodID);
                            //removeLeadingzeros(product_id);
                            if (prodID == product_id)
                            {
                                returnString_with_description = innerfield.at(1) + " by " + companyName;
                                goto breakout;
                            }
                        }
                    //}
//                    else
//                    {
//                        //End of list by vendor
//                        goto breakout;
//                    }
                }
            }
        }
    }
    breakout:
    file.close();

    return returnString_with_description;
}
void MainWindow::setup_layout_for_serialComs()
{
    serialComsPanelParentWidget = new QWidget(this);
    serialComsPanel = new Ui_serialComsPanel();
    serialComsPanel->setupUi(serialComsPanelParentWidget);

    MainContainerWidget = new QWidget();
    MainContainerLayout = new QVBoxLayout();
    MainContainerWidget->setLayout(MainContainerLayout);
    //MainContainerWidget->setContentsMargins(0,0,0,0);

    splitter_SerialComs_MainWindow = new QSplitter();
    splitter_SerialComs_MainWindow->setOrientation(Qt::Orientation::Vertical);

    splitter_SerialComs_MainWindow->setHandleWidth(5);
    splitter_SerialComs_MainWindow->addWidget(MainContainerWidget);
    splitter_SerialComs_MainWindow->addWidget(serialComsPanelParentWidget);

    centralWidget()->layout()->addWidget(splitter_SerialComs_MainWindow);

    serialComsPanel->console_rx_raw->document()->setMaximumBlockCount(150);
    serialComsPanel->console_tx_raw->document()->setMaximumBlockCount(150);
    serialComsPanel->console_rx_vars->document()->setMaximumBlockCount(150);
    serialComsPanel->console_tx_vars->document()->setMaximumBlockCount(150);
    serialComsPanelParentWidget->show();

    this->statusBar()->hide();
}
void MainWindow::setup_serialSignalsSlots()
{
    serial_write_timer = new QTimer();
    serial_write_timer->start(1000);

    qRegisterMetaType<typical_class::REGISTERS>("REGISTERS");
    qRegisterMetaType<typical_class::REGISTERS>("typical_class::REGISTERS");
    qRegisterMetaType<QList<int>>("QList<int>");
    qRegisterMetaType<QMap<QString, int>>("QMap<QString, int>");
    qRegisterMetaType<QList<QString>>("QList<QSerialPortInfo>");
    qRegisterMetaType<QList<QString>>("QList<QString>");

    connect(serial_mgr, &serial_manager::device_conflict, this, &MainWindow::device_conflict);
    connect(int_list_class, &array_of_ints::INT_ARRAY_UPDATED, this, &MainWindow::INT_ARRAY_UPDATED);
    connect(test_read_class, &typical_class::REGISTERS_UPDATED, this, &MainWindow::REGISTERS_UPDATED);
    connect(map_ints_class, &map_int_class::MAP_INT_UPDATED, this, &MainWindow::MAP_INT_UPDATED);
    connect(serial_write_timer, &QTimer::timeout, test_write_class, &typical_class::write);                 //This slot just flips a bool, the serial manager does the sending.
    connect(serial_mgr, &serial_manager::log_RX_packet_decoded_SIGNAL, this, &MainWindow::log_RX_packet_decoded_SIGNAL);
    connect(serial_mgr, &serial_manager::log_TX_packet_decoded_SIGNAL, this, &MainWindow::log_TX_packet_decoded_SIGNAL);
    connect(serial_mgr, &serial_manager::log_TX_packet_raw_SIGNAL, this, &MainWindow::log_TX_packet_raw_SIGNAL);
    connect(serial_mgr, &serial_manager::log_RX_packet_raw_SIGNAL, this, &MainWindow::log_RX_packet_raw_SIGNAL);

    connect(serial_mgr, &serial_manager::RX_Hz_updated, this, &MainWindow::update_RX_hz);
    connect(serial_mgr, &serial_manager::TX_Hz_updated, this, &MainWindow::update_TX_hz);

    connect(serial_mgr, &serial_manager::updatedReadQueueSize, this, &MainWindow::update_read_queue_size);
}
void MainWindow::log_RX_packet_decoded_SIGNAL(QList<QString> decoded)
{
    serialComsPanel->console_rx_vars->clear();
    serialComsPanel->console_rx_vars->append("<font color=\"Lime\">" + QDateTime::currentDateTime().toString(MyDataLogger->date_time_format_string) + "</font>: ");
    serialComsPanel->console_rx_vars->append("");
    for (QString thing : decoded)
    {
        serialComsPanel->console_rx_vars->append("\t" + thing);
    }

    //Also update all the buttons here, why not.
    serialComsPanel->toolButton_3->setText(serial_mgr->COM_port);
    serialComsPanel->toolButton->setText("Baudrate: " + serial_mgr->baudString);
    serialComsPanel->toolButton_4->setText("Vendor ID: 0x" + serial_mgr->vendor_id);
    serialComsPanel->toolButton_5->setText("Device Serial #: " + serial_mgr->device_serial_number);
    //QString RX_freq_hz_readout; if (RX_freq_hz < 1000) {RX_freq_hz_readout = QString::number(RX_freq_hz, 'f', 2) + " Hz";} else {RX_freq_hz_readout = QString::number(RX_freq_hz / (float)1000, 'f', 2) + " kHz";}
    //QString TX_freq_hz_readout; if (TX_freq_hz < 1000) {TX_freq_hz_readout = QString::number(TX_freq_hz, 'f', 2) + " Hz";} else {TX_freq_hz_readout = QString::number(TX_freq_hz / (float)1000, 'f', 2) + " kHz";}

    QString RX_freq_hz_readout = (RX_freq_hz < 1000) ?
        QString("%1 Hz").arg(RX_freq_hz) :
        QString("%1 kHz").arg(float(RX_freq_hz)/1000, 0, 'f', 2);

    QString TX_freq_hz_readout = (TX_freq_hz < 1000) ?
        QString("%1 Hz").arg(TX_freq_hz) :
        QString("%1 kHz").arg(float(TX_freq_hz)/1000, 0, 'f', 2);

    serialComsPanel->toolButton_6->setText("RX: " + RX_freq_hz_readout);
    serialComsPanel->toolButton_7->setText("TX: " + TX_freq_hz_readout);
    serialComsPanel->toolButton_2->setText("Lost Packets: " +  QString::number(serial_mgr->get_number_of_CRC_errors()));

}
void MainWindow::log_TX_packet_decoded_SIGNAL(QList<QString> decoded)
{
    serialComsPanel->console_tx_vars->clear();
    serialComsPanel->console_tx_vars->append("<font color=\"Lime\">" + QDateTime::currentDateTime().toString(MyDataLogger->date_time_format_string) + "</font>: ");
    serialComsPanel->console_tx_vars->append("");
    for (QString thing : decoded)
    {
        serialComsPanel->console_tx_vars->append("\t" + thing);
    }
}
void MainWindow::log_RX_packet_raw_SIGNAL(QByteArray encoded)
{
    QString line;
    for (auto thing : encoded)
    {
        QString char_to_display;
        if ((int)thing >= 32 && (int)thing <= 126) {
            char_to_display = QChar(thing);
        }
        else {
            char_to_display = "[" + QString::number((int)thing) + "]";
        }
        line.append(char_to_display);
    }
    serialComsPanel->console_rx_raw->append("<font color=\"Lime\">" + QDateTime::currentDateTime().toString(MyDataLogger->date_time_format_string) + "</font>: " + "<font color=\"Aqua\">" + line + "</font>: ");
}
void MainWindow::log_TX_packet_raw_SIGNAL(QByteArray encoded)
{

    QString line;
    for (auto thing : encoded)
    {
        QString char_to_display;
        if ((int)thing >= 32 && (int)thing <= 126) {
            char_to_display = QChar(thing);
        }
        else {
            char_to_display = "[" + QString::number((int)thing) + "]";
        }
        line.append(char_to_display);
    }
    serialComsPanel->console_tx_raw->append("<font color=\"Lime\">" + QDateTime::currentDateTime().toString(MyDataLogger->date_time_format_string) + "</font>: " + "<font color=\"Aqua\">" + line + "</font>: ");
}

void MainWindow::setup_serial_protocol(QString _vendor_id_)
{
    auto serial_mgr_thread = new QThread;
    serial_mgr = new serial_manager(_vendor_id_, 100);      //Will connect to first detected device with a matching vendor id. See mcu-vendor-id-table.h for the list.

    // Move everything to new thread in MainWindow, or it really doesn't work. Has to be in MainWindow
    serial_mgr->moveToThread(serial_mgr_thread);
    QApplication::connect(serial_mgr_thread, &QThread::finished, serial_mgr_thread, &QThread::deleteLater);
    QApplication::connect(serial_mgr_thread, &QThread::finished, serial_mgr, &serial_manager::deleteLater);
    QApplication::connect(serial_mgr_thread, &QThread::started, serial_mgr, &serial_manager::init);
    serial_mgr_thread->start();

    //READ ONLY
    test_read_class = new typical_class();
    int_list_class = new array_of_ints();
    map_ints_class = new map_int_class();
    serial_mgr->register_new_reader_class(test_read_class);
    serial_mgr->register_new_reader_class(int_list_class);
    serial_mgr->register_new_reader_class(map_ints_class);

    //WRITE ONLY
    test_write_class = new typical_class();
        test_write_class->registers.REGISTER_A = 123;
        test_write_class->registers.REGISTER_B = 99.62;
        test_write_class->registers.REGISTER_C = "MCU is reading properly";
        test_write_class->registers.REGISTER_D = 0;
        test_write_class->registers.REGISTER_E = -33;
        test_write_class->registers.REGISTER_F = 'J';
    serial_mgr->register_new_writer_class(test_write_class);

    serial_mgr->turnOffDebugOutput();

}
void MainWindow::REGISTERS_UPDATED(typical_class::REGISTERS _registers)
{
    realtimeDataSlot();
    QString log_fields;

    QString RX_freq_hz_readout; if (RX_freq_hz < 1000) {RX_freq_hz_readout = QString::number(RX_freq_hz, 'f', 2) + " Hz";} else {RX_freq_hz_readout = QString::number(RX_freq_hz / 1000, 'f', 2) + " kHz";}
    QString TX_freq_hz_readout; if (TX_freq_hz < 1000) {TX_freq_hz_readout = QString::number(TX_freq_hz, 'f', 2) + " Hz";} else {TX_freq_hz_readout = QString::number(TX_freq_hz / 1000, 'f', 2) + " kHz";}

    log_fields.append(QString::number(_registers.REGISTER_A)                    + ",");
    log_fields.append(QString::number(_registers.REGISTER_B)                    + ",");
    log_fields.append(QString::fromUtf8(_registers.REGISTER_C.c_str())          + ",");
    log_fields.append(QString::number(_registers.REGISTER_D)                    + ",");
    log_fields.append(QString::number(_registers.REGISTER_E)                    + ",");
    log_fields.append(QString(_registers.REGISTER_F)                            + ",");
    log_fields.append(RX_freq_hz_readout +                                      + ",");
    log_fields.append(TX_freq_hz_readout +                                      + ",");
    log_fields.append(QString::number(serial_mgr->get_number_of_CRC_errors())   + ",");
    log_fields.append(QString::number(read_queue_size)                          + ",");
    log_fields.append(QString::number(customPlot->graph(0)->data()->size())          );
    MyDataLogger->logSomething(log_fields);
}

void MainWindow::INT_ARRAY_UPDATED(QList<int> _list)
{
//    if (_list.size() >= 3)
//    {
//        label_INT_ARRAY_1->setText("INT_LIST_1: " + QString::number(_list.at(0)));
//        label_INT_ARRAY_2->setText("INT_LIST_2: " + QString::number(_list.at(1)));
//        label_INT_ARRAY_3->setText("INT_LIST_3: " + QString::number(_list.at(2)));
//    }
}
void MainWindow::MAP_INT_UPDATED(QMap<QString, int> new_map)
{
//    label_MAP_1->setText("MAP_1: 'a' = " + QString::number(new_map.value("a")));
//    label_MAP_2->setText("MAP_1: 'b' = " + QString::number(new_map.value("b")));
}
void MainWindow::device_conflict(QList<QSerialPortInfo> all_ports)
{
    qDebug() << "MainWindow device conflict handler..";

    QWidget* parent_widgey;
    parent_widgey = new QWidget();
    Ui_DeviceSelector *asdf;
    asdf = new Ui_DeviceSelector();
    asdf->setupUi(parent_widgey);

    asdf->comboBox->clear();
    asdf->comboBox_2->clear();
    for (auto info : all_ports)
    {
        if (QString::number(info.vendorIdentifier(), 16) == THIS_VENDOR_ID)
        {
            QString vendy; vendy = QString("%1").arg(info.vendorIdentifier(), 4, 16, QLatin1Char( '0' ));
            QString proddy; proddy = QString("%1").arg(info.productIdentifier(), 4, 16, QLatin1Char( '0' ));
            qDebug() << "Looking for " + proddy + " from " + QString::number(info.vendorIdentifier());
            qDebug() << "and " + vendy + " from " + QString::number(info.productIdentifier());
            asdf->comboBox->addItem( info.portName() + "\t: " + findVendorDescription(vendy, proddy));
            //asdf->comboBox->addItem( info.portName());
            asdf->comboBox->setCurrentText(info.portName());
        }
        else
        {
            QString vendy; vendy = QString("%1").arg(info.vendorIdentifier(), 4, 16, QLatin1Char( '0' ));
            QString proddy; proddy = QString("%1").arg(info.productIdentifier(), 4, 16, QLatin1Char( '0' ));
            qDebug() << "Looking for " + proddy + " from " + QString::number(info.vendorIdentifier());
            qDebug() << "and " + vendy + " from " + QString::number(info.productIdentifier());
            asdf->comboBox_2->addItem( info.portName() + "\t: " + findVendorDescription(vendy, proddy));
            //asdf->comboBox_2->addItem( info.portName());
            asdf->comboBox_2->setCurrentText(info.portName());
        }
    }

    if (asdf->comboBox_2->count() < 1)
    {
        asdf->tab_2->setDisabled(true);
    }

    parent_widgey->show();

    connect(asdf->comboBox, &QComboBox::textHighlighted, serial_mgr, &serial_manager::update_port_SLOT);
    connect(asdf->comboBox_2, &QComboBox::textHighlighted, serial_mgr, &serial_manager::update_port_SLOT);

    connect(asdf->pushButton, &QPushButton::clicked, serial_mgr, &serial_manager::device_conflict_resolved);
    connect(asdf->pushButton_2, &QPushButton::clicked, serial_mgr, &serial_manager::device_conflict_resolved);
}
MainWindow::~MainWindow()
{
    serial_write_timer->stop();
    dataTimer.stop();

    delete ui;

    delete serial_mgr;
    delete test_read_class;
    delete int_list_class;
    delete map_ints_class;
    delete serial_write_timer;
    delete serial_mgr_thread;
}

