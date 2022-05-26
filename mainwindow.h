#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "serial_manager.h"
#include "MsgPack_types.h"
#include <QThread>
#include <QObject>
#include <QLabel>
#include <QSplitter>
#include "ui_serialComsPanel.h"
#include "QCustomPlot/qcustomplot.h"
#include "filedownloader.h"
#include <QFile>
#include <QRadioButton>

#include "drew_util.h"
#include "datalogger.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setup_layout_for_serialComs();
    void setup_serialSignalsSlots();
    void setup_realtime_chart();

    dataLogger *MyDataLogger;

    QSettings MySettings;

    ///////////////////////////////////////////////
        //Serial manager and custom read protocol specifics
        serial_manager *serial_mgr;
        typical_class *test_read_class;
        array_of_ints *int_list_class;
        map_int_class *map_ints_class;

        typical_class *test_write_class;
        void setup_serial_protocol(QString _vendor_id_);
    ///////////////////////////////////////////////

        QThread *serial_mgr_thread = nullptr;

        QTimer *serial_write_timer;

        QWidget *MainContainerWidget;
        QVBoxLayout *MainContainerLayout;

        QSplitter *splitter_SerialComs_MainWindow;

        QWidget* serialComsPanelParentWidget;
        Ui_serialComsPanel *serialComsPanel;

        QCustomPlot* customPlot;
        QTimer dataTimer;

        float RX_freq_hz = 666;
        float TX_freq_hz = 666;
        int read_queue_size;

        //Window geometry and default directory settings
        virtual void closeEvent(QCloseEvent *event);
        void setup_geometry_Settings();
        void writeSettings();

        void setup_USB_vendor_downloader();
        void setup_layout_for_realtime_chart();
        void setup_file_loggingSignalSlot();

public slots:
    void REGISTERS_UPDATED(typical_class::REGISTERS _registers);
    void INT_ARRAY_UPDATED(QList<int> _list);
    void MAP_INT_UPDATED(QMap<QString, int>);

    void device_conflict(QList<QSerialPortInfo> all_ports);

    void log_RX_packet_decoded_SIGNAL(QList<QString> decoded);
    void log_TX_packet_decoded_SIGNAL(QList<QString> decoded);
    void log_RX_packet_raw_SIGNAL(QByteArray encoded);
    void log_TX_packet_raw_SIGNAL(QByteArray encoded);

private slots:
    void realtimeDataSlot();
    void loadVendorInfo();

    void update_RX_hz(float val);
    void update_TX_hz(float val);

    void update_read_queue_size(int _read_queue_size);
private:
    FileDownloader *usb_vendor_downloader;
    QString findVendorDescription(QString vendor_id_in_hex, QString product_id);

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
