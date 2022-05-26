#include "serial_manager.h"


serial_manager::serial_manager(QString _vendor_id, int _update_rate_millis)
{
    vendor_id = _vendor_id;
    update_rate_millis = _update_rate_millis;
}
serial_manager::~serial_manager() {

    send_command_timer->stop();

    delete serialPort;
    delete MCU_reader;
    delete MCU_writer;

}

void serial_manager::init()
{
    serialPort = new QSerialPort(this);
    send_command_timer = new QTimer(this);

    const QStringList argumentList;

    const auto infos = QSerialPortInfo::availablePorts();

    QString serialPortName;
    int num_matching_vendor_ids = 0;
    for (const QSerialPortInfo &info : infos) {
                    QString s = QObject::tr("Port: ") + info.portName() + "\n"
                    + QObject::tr(" Location: ") + info.systemLocation() + "\n"
                    + QObject::tr(" Description: ") + info.description() + "\n"
                    + QObject::tr(" Manufacturer: ") + info.manufacturer() + "\n"
                    + QObject::tr(" Serial number: ") + info.serialNumber() + "\n"
                    + QObject::tr("Vendor Identifier: ") + (info.hasVendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : QString()) + "\n"
                    + QObject::tr("Product Identifier: ") + (info.hasProductIdentifier() ? QString::number(info.productIdentifier(), 16) : QString()) + "\n";

                    product_id = info.hasProductIdentifier();
                    device_serial_number = info.serialNumber();


        //Full barf-out of COM port info
        //if (debugOutput)
        //{
            qDebug() << s;
        //}

        if (QString::number(info.vendorIdentifier(), 16) == vendor_id)
        {
            if (debugOutput) {qDebug() << "Device attached on port: " << info.portName();}          serialPortName = QString(info.portName());
            if (num_matching_vendor_ids == 0) {newSerialPortName = serialPortName;} //The default will be what is auto-selected. this is the first item in the drop-down list.
            num_matching_vendor_ids++;
        }

    }

    if (num_matching_vendor_ids == 1)
    {
        qDebug() << "Using default device.";
        complete_serial_connection(serialPortName);
    }
    else
    {
        qDebug() << "Resolving multiple device conflict...";
        emit device_conflict(infos);
    }

}
void serial_manager::complete_serial_connection(QString serialPortName)
{
    COM_port = serialPortName;
    serialPort->setPortName(serialPortName);

    const int serialPortBaudRate = QSerialPort::Baud115200;
    baudString = "115200";
    serialPort->setBaudRate(serialPortBaudRate);

    qDebug() << "Attempting to open serial connection: " << serialPortName;
    if (!serialPort->open(QIODevice::ReadWrite))    {  qDebug() << "Failed to open port" << serialPortName << ", Error: " << serialPort->errorString();   }
    else {qDebug() << "Connection successfully established.";}

    QString error_string;

    MCU_reader = new SerialPortReader(serialPort);
    MCU_writer = new SerialPortWriter(serialPort);

    send_command_timer->start(20);  //20 millisecond send update

    connect(MCU_reader, SIGNAL(commandRecieved(Packetizer::Packet)), this, SLOT(handleResults(Packetizer::Packet)));

    connect(this->send_command_timer, &QTimer::timeout, this, &serial_manager::sendCommands);                 //This slot just flips a bool, the serial manager does the sending.
    connect(this, &serial_manager::send_commands_SIGNAL, MCU_writer, &SerialPortWriter::write_slot);

    connect(MCU_reader, &SerialPortReader::raw_RX_Packet_log_SIGNAL, this, &serial_manager::handle_RX_raw_logging);
    connect(MCU_reader, &SerialPortReader::updatedReadQueueSize, this, &serial_manager::handle_updatedReadQueueSize);

    elapsed_timer_RX.start();
    elapsed_timer_TX.start();
}
void serial_manager::register_new_writer_class(parent_MSG_class *thing)
{
    registered_writer_class_pointers.append(thing);

    if (debugOutput) {
        qDebug() << "WRITER THING_ID = " << thing->ID;
        thing->print_all();
        qDebug() << "---------------";

        qDebug() << "Current List of Writer things:";
        for (int i = 0; i < registered_writer_class_pointers.size(); i++)
        {
                qDebug() << "ID: " << registered_writer_class_pointers.at(i)->ID;

                //registered_reader_class_pointers.at(i)->_data_;
                //Packetizer::Packet _decoded;
                //decode(&thing->_data_, &_decoded);
        }
        qDebug();
   }
}
void serial_manager::register_new_reader_class(parent_MSG_class *thing)
{

    registered_reader_class_pointers.append(thing);

    if (debugOutput) {
        qDebug() << "THING_ID = " << thing->ID;
        thing->print_all();
        qDebug() << "---------------";

        qDebug() << "Current List of things:";
        for (int i = 0; i < registered_reader_class_pointers.size(); i++)
        {
                qDebug() << "ID: " << registered_reader_class_pointers.at(i)->ID;

                //registered_reader_class_pointers.at(i)->_data_;
                //Packetizer::Packet _decoded;
                //decode(&thing->_data_, &_decoded);
        }
        qDebug();
   }
}
void serial_manager::turnOnDebugOutput()
{
    debugOutput = true;
}
void serial_manager::turnOffDebugOutput()
{
    debugOutput = false;
}
int serial_manager::get_number_of_CRC_errors()
{

    return CRC_ERRORS;
}

template <typename T>
void serial_manager::decode(T *target_thing, Packetizer::Packet *_decoded)
{
    MsgPack::Unpacker unpacker;
    unpacker.feed(_decoded->data.data(), _decoded->data.size());
    unpacker.deserialize(*target_thing);
}
void serial_manager::handleResults(Packetizer::Packet _decoded)
{

    QList <QString> ALL_VARS;
    for (int i = 0; i < registered_reader_class_pointers.size(); i++)
    {

            registered_reader_class_pointers.at(i)->decode(&_decoded);

            ALL_VARS.append("---------------------");
            ALL_VARS.append(registered_reader_class_pointers.at(i)->getDescription());
            ALL_VARS.append("---------------------");
            for (int j = 0; j < registered_reader_class_pointers.at(i)->getStringListRepresentation().size(); j++)
            {
                ALL_VARS.append("  " + registered_reader_class_pointers.at(i)->getStringListRepresentation().at(j));
            }
            ALL_VARS.append("---------------------");
            ALL_VARS.append("");

            if (debugOutput) {
                //qDebug() << "ID: " << registered_reader_class_pointers.at(i)->ID;
                registered_reader_class_pointers.at(i)->print_all();
            }

    }

    calculate_and_emit_average_RX_hz();
    emit log_RX_packet_decoded_SIGNAL(ALL_VARS);

    CRC_ERRORS = MCU_reader->get_number_of_CRC_errors();

}
void serial_manager::calculate_and_emit_average_RX_hz()
{
    RX_Hz_average = 666;
    if (RX_array_iter < 25)
    {
        RX_Hz_array[RX_array_iter] = elapsed_timer_RX.elapsed();
        RX_array_iter++;
        if (RX_array_iter >= 25) {RX_array_iter = 0;}
        for (int i = 0; i < 25; i++)        {            RX_Hz_average+=RX_Hz_array[i];        }
        RX_Hz_average /= 25;
        elapsed_timer_RX.start();
        RX_Hz_average = 1000 / (float)(RX_Hz_average + 0.001);
        emit RX_Hz_updated(RX_Hz_average);
    }
}
void serial_manager::calculate_and_emit_average_TX_hz()
{
    TX_Hz_average = 666;
    if (TX_array_iter < 25)
    {
        TX_Hz_array[TX_array_iter] = elapsed_timer_TX.elapsed();
        TX_array_iter++;
        if (TX_array_iter >= 25) {TX_array_iter = 0;}
        for (int i = 0; i < 25; i++)        {            TX_Hz_average+=TX_Hz_array[i];        }
        TX_Hz_average /= 25;
        TX_Hz_average = 1000 / (float)(TX_Hz_average + 0.001);
        elapsed_timer_TX.start();
        emit TX_Hz_updated(TX_Hz_average);
    }
}

//Transmit handler
void serial_manager::sendCommands()
{
    for (int i = 0; i < registered_writer_class_pointers.size(); i++)
    {
        if (registered_writer_class_pointers.at(i)->isReady())
        {
            QByteArray encoded_packet;
            encoded_packet = registered_writer_class_pointers.at(i)->encode();
            emit(log_TX_packet_raw_SIGNAL(encoded_packet));
            QList <QString> ALL_VARS;
            ALL_VARS.append("---------------------");
            ALL_VARS.append(registered_reader_class_pointers.at(i)->getDescription());
            ALL_VARS.append("---------------------");
            ALL_VARS.append(registered_writer_class_pointers.at(i)->getStringListRepresentation());
            emit(log_TX_packet_decoded_SIGNAL(ALL_VARS));
            //qDebug() << "ID = " << registered_writer_class_pointers.at(0)->ID;
            //qDebug() << "Send Packet Size = " << encoded_packet.size();
            if (encoded_packet.size() > 1)
            {
                calculate_and_emit_average_TX_hz();
                emit send_commands_SIGNAL(encoded_packet);
                //                qDebug() << "SEND COMMAND SLOT CALLED IN SERIAL MANAGER with packet:";
                //                qDebug() << encoded_packet;
                //                for (auto asdf : encoded_packet)
                //                {
                //                    qDebug() << (int)asdf << ":::" << (char)asdf;
                //                }

            }
        }
        registered_writer_class_pointers.at(i)->done();
    }
}
void serial_manager::device_conflict_resolved()
{
    qDebug() << "DEVICE CONFLICT RESOLVED: Using port: " << newSerialPortName;
    complete_serial_connection(newSerialPortName);
}
void serial_manager::update_port_SLOT(QString text)
{
    qDebug() << "Updating port to connect to: " << text;
    vendor_id = "";
    product_id = "";
    device_serial_number = "";
    newSerialPortName = text.split(":").at(0).trimmed();
}
void serial_manager::handle_RX_raw_logging(QByteArray rawpack)
{
    emit(log_RX_packet_raw_SIGNAL(rawpack));
}

void serial_manager::handle_updatedReadQueueSize(int read_queue_size)
{
    emit updatedReadQueueSize(read_queue_size);
}

