#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <QSettings>
#include <QFile>
#include <QWidget>

class dataLogger : public QWidget
{
    Q_OBJECT

public:
    dataLogger(QWidget *parent = 0);
    virtual ~dataLogger();

    QSettings MySettings;
    QFile data_log;
    QString data_log_filename;
    QString date_time_format_string = "ddd.MMM.dd.yyyy hh:mm:ss.zzz";
    QString LOG_HEADER = "DATE (" + date_time_format_string + "),<int>,<float>,<string>,<uint8_t>,<int8_t>,<char>,RX hz,TX hz,CRC Errors,read_queue_size,graph(0)->data.size()\n";
    QString CSV_date_time_format_string = "yyyy_MM_dd_hh_mm_";
    bool file_successfully_opened = false;
    bool DATA_LOGGING_ACTIVATED = false;

    void log_file_selector(bool selected);

    void logSomething(QString thing);
};

#endif // DATALOGGER_H
