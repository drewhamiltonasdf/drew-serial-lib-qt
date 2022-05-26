/****************************************************************************
**
** Copyright (C) 2013 Laszlo Papp <lpapp@kde.org>
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtSerialPort module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "serialportreader-async.h"
#include "serialportreader-async.h"

#include <QCoreApplication>
#include <QDebug>


SerialPortReader::SerialPortReader(QSerialPort *serialPort, QObject *parent) :
    QObject(parent),
    m_serialPort(serialPort),
    m_standardOutput(stdout)
{
    connect(m_serialPort, &QSerialPort::readyRead, this, &SerialPortReader::handleReadyRead);
    connect(m_serialPort, &QSerialPort::errorOccurred, this, &SerialPortReader::handleError);
    connect(&m_timer, &QTimer::timeout, this, &SerialPortReader::handleParseQueue);
    connect(&command_parse_timer, &QTimer::timeout, this, &SerialPortReader::handleParseCommands);

    //This is how often we take the raw data from the serialport and add it to our raw_data_queue
    m_timer.start(150);

    //How often do we sift through the queue for full commands
    command_parse_timer.start(155);     //155ms - queue ends up being around 300-400 chars long by the time we get around to it, when Arduino is spitting out at 65Hz

    turnOffDebugOutput();
}

void SerialPortReader::turnOnDebugOutput()
{
    debugOutput = true;
}

void SerialPortReader::turnOffDebugOutput()
{
    debugOutput = false;
}

SerialPortReader::~SerialPortReader()
{
    m_timer.stop();
    command_parse_timer.stop();
}

int SerialPortReader::get_number_of_CRC_errors()
{
    return CRC_ERRORS;
}

void SerialPortReader::handleReadyRead()
{
    raw_serial_queue.append(m_serialPort->readAll());
}

void SerialPortReader::handleParseQueue()
{
    emit updatedReadQueueSize(raw_serial_queue.size());

    ////////////////////////////////////////////////////////////
    ///    SPLIT up raw queue into char(0) delimited chunks   //
    ////////////////////////////////////////////////////////////
        QQueue<QByteArray> temp_queue;
        QByteArray inner_temp;
        for (int i = 0; i < raw_serial_queue.size(); i++)
        {
               inner_temp.append(raw_serial_queue.at(i));
               if (raw_serial_queue.at(i) == 0)
               {
                   temp_queue.enqueue(inner_temp);
                   inner_temp.clear();
               }
        }
        raw_serial_queue.clear();

      //qDebug() << "Size of raw serial queue after clearing: " << raw_serial_queue.size();
    ////////////////////////////////////////////////////////////
    ///    SPLIT up raw queue into char(0) delimited chunks   //
    ////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    ///    Decode raw queue and add it to command queue....   //
    ////////////////////////////////////////////////////////////
        while (!temp_queue.isEmpty())
        {
            QByteArray new_data = temp_queue.dequeue();
            Packetizer::Packet new_pack;

            for (int i = 0; i < new_data.size(); i++) {  new_pack.data.push_back(new_data.at(i));   }
            emit(raw_RX_Packet_log_SIGNAL(new_data));
            Packetizer::Packet decoded;
            decoded = Packetizer::decode(new_pack.data.data(), new_pack.data.size(), USE_INDEX, USE_CRC);

            int CRC_received = 0;
                if (new_pack.data.size() > 2) { CRC_received = new_pack.data.at(static_cast<int>(new_pack.data.size()) - 2); }
            int CRC_expected = (int)crcx::crc8(    decoded.data.data(), decoded.data.size()   );
            if (CRC_expected == 0) {CRC_expected = 1;} //<-- COBS Quirk, can't do zero.

            if (CRC_received == CRC_expected)  { decoded_packet_queue.enqueue(decoded);  }
            else
            {
                if (debugOutput) {
                    qDebug() << "***********************";
                    qDebug() << "CRC ERROR: [" << CRC_received << " vs. " << CRC_expected << "] ";
                    //qDebug() << "Last char = " << last_char;
                    qDebug() << "***********************"; }
                CRC_ERRORS++;
            }
        }
    ////////////////////////////////////////////////////////////
    ///    Decode raw queue and add it to command queue....   //
    ////////////////////////////////////////////////////////////

}


void SerialPortReader::handleParseCommands()
{
    if (debugOutput)
    {
        qDebug() << "Decoded Packet Queue Size = " << decoded_packet_queue.size();
        qDebug() << "Cumulative Errors: [" << CRC_ERRORS << "]: ";
        qDebug();
    }

    //qDebug() << "Size of decoded packet queue: " << decoded_packet_queue.size();

    while (!decoded_packet_queue.isEmpty())
    {
        Packetizer::Packet decoded = decoded_packet_queue.dequeue();
        emit commandRecieved(decoded);
    }
}

void SerialPortReader::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        m_standardOutput << QObject::tr("An I/O error occurred while reading "
                                        "the data from port %1, error: %2")
                            .arg(m_serialPort->portName())
                            .arg(m_serialPort->errorString())
                         << endl;
        //QCoreApplication::exit(1);
    }
}
