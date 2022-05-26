// #define MSGPACKETIZER_DEBUGLOG_ENABLE
#include <MsgPacketizer.h>

// for STL enabled boards:
// MsgPack::arr_t<T> = std::vector<T>
// MsgPack::map_t<T, U> = std::map<T, U>
// MsgPack::bin_t<T> = std::vector<T = uint8_t || char>

// for NO-STL boards(AVR, megaAVR, SAMD, SPRESENSE):
// MsgPack::arr_t<T> = arx::vector<T>
// MsgPack::map_t<T, U> = arx::map<T, U>
// MsgPack::bin_t<T> = arx::vector<T = uint8_t || char>

#define PACKETIZER_USE_CRC_AS_DEFAULT
#define PACKETIZER_USE_INDEX_AS_DEFAULT

// msgpac input && output
MsgPack::arr_t<int> a {99, 2, 3};                     // json: [1, 2, 3]
MsgPack::map_t<String, int> m {{"a", 1}, {"b", 2}};  // json {{"a", 1}, {"b", 2}}

const uint8_t recv_index_arr = 0x12;    //18 decimal
const uint8_t send_index_arr = 0x34;    //52 decimal
const uint8_t recv_index_map = 0x56;    //86 decimal
const uint8_t send_index_map = 0x78;    //120 decimal

const uint8_t send_index_registers = 99;    //120 decimal
const uint8_t recieve_index_registers = 99;    //120 decimal


struct REGISTERS
{
    int             REGISTER_A  = 13;
    float           REGISTER_B  = -32768;
    String          REGISTER_C  = "Hello world!";
    uint8_t         REGISTER_D  = 253;
    int8_t          REGISTER_E  = -12;
    char            REGISTER_F  = 'G';
    
    MSGPACK_DEFINE(REGISTER_A, REGISTER_B, REGISTER_C, REGISTER_D, REGISTER_E, REGISTER_F);
};

REGISTERS registers;
REGISTERS recieve_registers;

void setup() {
    Serial.begin(115200);
    delay(2000);

    // update received data directly
    //MsgPacketizer::subscribe(Serial, recv_index_arr, a);
    MsgPacketizer::subscribe(Serial, recieve_index_registers, recieve_registers);

    // register variables to publish repeatedly
    MsgPacketizer::publish(Serial, send_index_arr, a)
        ->setFrameRate(3.f);
    
    MsgPacketizer::publish(Serial, send_index_map, m)
        ->setFrameRate(6.f);

    MsgPacketizer::publish(Serial, send_index_registers, registers)
        ->setFrameRate(60.f);
}

float iter=0.00001;
float x_val = 0;
void loop() {
  
    // must be called to trigger callback and publish data
    x_val+=iter;
    registers.REGISTER_B=sin(x_val)*5 + 1*sin(x_val*5) + 1*sin(x_val*11);
    if (x_val >= TWO_PI) {x_val = -TWO_PI;}

    registers.REGISTER_C = recieve_registers.REGISTER_C;
    
    MsgPacketizer::update();
    MsgPacketizer::parse();
}
