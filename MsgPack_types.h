//
//
//
//      THIS IS WHERE WE DEFINE ALL OF OUR DELICIOUS CUSTOM TYPES
//
//      Now, we can just pass the class to the Serial Manager and let it handle all of the messy stuff.
//
//
//
//
//
//
//
//
//
//



#include "MsgPack.h"
#include "Packetizer.h"
#include <QDebug>
#include <QObject>
#include <QList>
#include <QMap>

#ifndef MSGPACK_TYPES_H
#define MSGPACK_TYPES_H

#define MSG_INT_ARRAY_ID            52
#define MSG_MAP_STRING_INT_ID       120
#define REGISTER_ABCDEF_ID          99

//#define PACKETIZER_USE_INDEX_AS_DEFAULT
//#define PACKETIZER_USE_CRC_AS_DEFAULT

class parent_MSG_class : public QObject
{
    Q_OBJECT

    public:
        int ID = 0;
        virtual QString getDescription() {return QString("Parent Class. Implementation per child."); }

        parent_MSG_class() {}

        parent_MSG_class(QObject *parent) : QObject(parent)
        {}

        virtual void print_all() {}
        virtual QList<QString> getStringListRepresentation() {}
        virtual void decode(Packetizer::Packet *_decoded) {  MsgPack::Unpacker unpacker;  unpacker.feed(_decoded->data.data(), _decoded->data.size());}
        virtual QByteArray encode() { QByteArray implemented_in_override; return implemented_in_override;}
        virtual ~parent_MSG_class() {}

        bool isReady() {return WRITE_NOW_BOOL;}
        void done() {WRITE_NOW_BOOL = false;}

    private:
        bool WRITE_NOW_BOOL = false;                            //THIS GETS FLIPPED WHEN WE WANT TO SEND SOMETHING.

    public slots:
        void write()  {  WRITE_NOW_BOOL = true;  }

    signals:


};

class typical_class : public parent_MSG_class
{
    Q_OBJECT

        public:

        QString getDescription() {return QString("Register Bank"); }

        struct REGISTERS
        {
            int             REGISTER_A;
            float           REGISTER_B;
            std::string     REGISTER_C;
            uint8_t         REGISTER_D;
            int8_t          REGISTER_E;
            char            REGISTER_F;

            MSGPACK_DEFINE(REGISTER_A, REGISTER_B, REGISTER_C, REGISTER_D, REGISTER_E, REGISTER_F);
        };

        REGISTERS registers;

        typical_class ()
        {
            parent_MSG_class::ID = REGISTER_ABCDEF_ID;
        }

        void print_all()
        {
            qDebug() << "------------DECODED MAP STRING_INT------------------------";
            qDebug() << "  Map Index: " << ID;
            qDebug() << "----------------------------------------------------------";
            qDebug() << "[REGISTER_A]: " << registers.REGISTER_A;
            qDebug() << "[REGISTER_B]: " << registers.REGISTER_B;
            qDebug() << "[REGISTER_C]: " << QString::fromUtf8(registers.REGISTER_C.c_str());
            qDebug() << "[REGISTER_D]: " << registers.REGISTER_D;
            qDebug() << "[REGISTER_E]: " << registers.REGISTER_E;
            qDebug() << "[REGISTER_F]: " << registers.REGISTER_F;
            qDebug();
        }

        QList<QString> getStringListRepresentation()
        {
            QList<QString> list;
            list.append("<int>:\t " + QString::number(registers.REGISTER_A));
            list.append("<float>:\t " + QString::number(registers.REGISTER_B));
            list.append("<std::string>:\t " + QString::fromUtf8(registers.REGISTER_C.c_str()));
            list.append("<uint8_t>:\t " + QString::number(registers.REGISTER_D));
            list.append("<int8_t>:\t " + QString::number(registers.REGISTER_E));
            list.append("<char>:\t " + QString(registers.REGISTER_F));

            return list;
        }

        void decode(Packetizer::Packet *_decoded)
        {
            if ((int)_decoded->index == ID)
            {
                MsgPack::Unpacker unpacker;
                unpacker.feed(_decoded->data.data(), _decoded->data.size());
                unpacker.deserialize(registers);
            }
            //qDebug() << "Updating registers signal, packet size: " << _decoded->data.size();
            emit REGISTERS_UPDATED(registers);
        }

        QByteArray encode()
        {
            MsgPack::Packer packer;
            packer.serialize(registers);

            Packetizer::Packet p_buff = Packetizer::encode(REGISTER_ABCDEF_ID, packer.data(), packer.size(), true);

            QByteArray packet;

            for (unsigned int i = 0; i < p_buff.data.size(); i++)
            {
                packet.append(p_buff.data.at(i));
            }

            return packet;

        }

    private:

    signals:
        void REGISTERS_UPDATED(REGISTERS _registers);

};

class array_of_ints : public parent_MSG_class
{

     Q_OBJECT

    public:

        QString getDescription() {return QString("Array of Integers"); }
        MsgPack::arr_t<int> _int_array;
        QList<int> Q_int_array = {0, 0, 0};

        array_of_ints ()
        {
            parent_MSG_class::ID = MSG_INT_ARRAY_ID;
        }

        void print_all()
        {
            qDebug() << "------------DECODED ARRAY OF INTS ------------------------";
            qDebug() << "  Int_array Index: " << ID;
            qDebug() << "----------------------------------------------------------";
            for (unsigned int i = 0; i < _int_array.size(); i++)
            {
                qDebug() << "[Int (" << i << ")]: " << _int_array.at(i);
            }
            qDebug();
        }

        void decode(Packetizer::Packet *_decoded)
        {
            if ((int)_decoded->index == ID)
            {
                MsgPack::Unpacker unpacker;
                unpacker.feed(_decoded->data.data(), _decoded->data.size());
                unpacker.deserialize(_int_array);
            }

            Q_int_array.clear();
            for (unsigned int i = 0; i < _int_array.size(); i++)
            {
                Q_int_array.append(_int_array.at(i));
            }
            emit INT_ARRAY_UPDATED(Q_int_array);
        }

        QByteArray encode()
        {
            MsgPack::Packer packer;
            packer.serialize(_int_array);

            Packetizer::Packet p_buff = Packetizer::encode(MSG_INT_ARRAY_ID, packer.data(), packer.size(), true);

            QByteArray packet;

            for (unsigned int i = 0; i < p_buff.data.size(); i++)
            {
                packet.append(p_buff.data.at(i));
            }

            return packet;
        }

        QList<QString> getStringListRepresentation()
        {
            QList<QString> list;
            for (int i = 0; i < Q_int_array.size(); i++)
            {
                list.append("<int>:\t " + QString::number(Q_int_array.at(i)));
            }
            return list;
        }

    signals:
        void INT_ARRAY_UPDATED(QList<int>);
};


class map_int_class : public parent_MSG_class
{

    Q_OBJECT

public:

        map_int_class ()
        {
            parent_MSG_class::ID = MSG_MAP_STRING_INT_ID;
        }

        QString getDescription() {return QString("Map <QString, int>"); }
        MsgPack::map_t<MsgPack::str_t, int> map;
        QMap<QString, int> qt_map;

        void print_all()
        {
            qDebug() << "------------DECODED MAP STRING_INT------------------------";
            qDebug() << "  Map Index: " << ID;
            qDebug() << "----------------------------------------------------------";
            for (const auto& [key, value] : map) {
                qDebug() << "[Key]: [" << QString::fromUtf8(key.c_str()) << "], [Value]: " << value;
            }
            qDebug();
        }

        void decode(Packetizer::Packet *_decoded)
        {
            if ((int)_decoded->index == ID)
            {
                MsgPack::Unpacker unpacker;
                unpacker.feed(_decoded->data.data(), _decoded->data.size());
                unpacker.deserialize(map);
            }
            qt_map.clear();
            for (const auto& [key, value] : map) {
                QString qkey = QString::fromUtf8(key.c_str());
                qt_map[qkey] = value;
            }
            emit MAP_INT_UPDATED(qt_map);
        }

        QByteArray encode()
        {
            QByteArray not_implemented;
            //MsgPack::Packer packer;
            //packer.serialize(registers);
            return not_implemented;
        }

        QList<QString> getStringListRepresentation()
        {
            QList<QString> list;
            QMapIterator<QString, int> i(qt_map);
            while (i.hasNext()) {
                i.next();
                list.append("<map>:\t " + QString(i.key()) + ":" + QString::number(i.value()));
            }
            return list;
        }

    private:

    signals:
        void MAP_INT_UPDATED(QMap<QString, int>);

};


#endif // MSGPACK_TYPES_H
