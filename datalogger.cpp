#include "datalogger.h"

#include <QDateTime>
#include <QTextStream>
#include <QDir>
#include <QFileDialog>

dataLogger::dataLogger(QWidget *parent) : QWidget(parent)
{

}

dataLogger::~dataLogger()
{

}

void dataLogger::log_file_selector(bool selected)
{
    if (selected)
    {
        DATA_LOGGING_ACTIVATED = true;

        //MySettings.setValue("DEFAULT_DIR_KEY", "/data");

        QDateTime dt_for_file_prepend = QDateTime::currentDateTime();
        QString CSV_date = dt_for_file_prepend.toString(CSV_date_time_format_string);


        //filename = QFileDialog::getSaveFileName(this, "CSV Log File Save Location", CSV_date + QString(".csv"), 0, 0); // getting the filename (full path)
        //         QFileDialog::getSaveFileName(this, const QString &caption = QString(), const QString &dir = QString(), const QString &filter = QString(), QString *selectedFilter = nullptr, QFileDialog::Options options = Options())
        //filename = QFileDialog::getSaveFileName(this, "CSV Log File Save Location", MySettings.value("DEFAULT_DIR_KEY").toString(), CSV_date + QString(".csv"), 0, 0);
        data_log_filename = QFileDialog::getSaveFileName(this, "CSV Serial DataLogger File Save Location", MySettings.value("DEFAULT_DIR_KEY").toString(), "Logs (*.csv)", 0, 0);


        QFile data_log(data_log_filename);


        QDir CurrentDir;
        if(data_log.open(QFile::WriteOnly |QFile::Truncate))
        {
          QTextStream output(&data_log);
          QDateTime dt = QDateTime::currentDateTime();

          output << LOG_HEADER;

          file_successfully_opened = true;


          MySettings.setValue("DEFAULT_DIR_KEY", CurrentDir.absoluteFilePath(data_log_filename));

        }

        //Initialize our temporary comments file
        //    QFile file(comments_tempfile);
        //    file.open(QIODevice::WriteOnly | QIODevice::Truncate);          //Overwrite, initialize empty
        //    file.close();
    }
    else
    {
        DATA_LOGGING_ACTIVATED = false;
    }
}

void dataLogger::logSomething(QString thing)
{
    if (file_successfully_opened && (DATA_LOGGING_ACTIVATED == true))
    {
            QFile data_log(data_log_filename);
            if (data_log.open(QFile::WriteOnly | QIODevice::Append))
            {
                QTextStream tstream(&data_log);
                QDateTime dt = QDateTime::currentDateTime();

                QString formatted_date = dt.toString(date_time_format_string);

                //QString number = QStringLiteral("%1").arg(val, 7, 10, QLatin1Char('0'));
                //tstream << formatted_date << "," << number << "\n";

                tstream << formatted_date << "," << thing << "\n";

                data_log.close();
            }
    }
}
