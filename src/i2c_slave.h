
/**
 * Author: sascha_lammers@gmx.de
 */

#pragma once

#include "main.h"
#include "dimmer_protocol.h"
#include "helpers.h"
#include "config_storage.h"

// void dimmer_i2c_slave_setup();
// void dimmer_i2c_on_receive(int length,  Stream *in);
// void dimmer_i2c_on_request(Stream *out);

extern register_mem_union_t register_mem;

class RegisterMemory {
private:
    static constexpr register_mem_union_t &_mem = register_mem;
    static constexpr uint8_t *_start = &_mem.raw[0];
    static constexpr uint8_t *_end = &_mem.raw[sizeof(_mem.raw)];

public:
    class AddressPointer {
    public:
        AddressPointer();

        AddressPointer &operator=(uint8_t address);
        AddressPointer &operator=(void *pointer);
        AddressPointer &operator++();
        AddressPointer operator++(int);

        operator uint8_t() const;
        operator uint8_t *();
        uint8_t &operator*();

        bool isInvalid() const;
        bool isValid() const;

    private:
        static constexpr uint8_t &_address = _mem.data.address;
        uint8_t *_pointer;
    };

    RegisterMemory();

    void begin();

    void onReceive(int8_t length);
    void onRequest();

private:
    void setResponse(int8_t length, uint8_t address, uint8_t readLength);

    template<class T>
    void setResponse(int8_t length, T &address) {
        _mem.data.cmd.read_length += sizeof(address);
        _pointer = (length <= 1) ? (void *)&address : (void *)&_mem.data.address;
    }

    uint8_t write(uint8_t data);
    uint8_t read();

private:
    AddressPointer _pointer;
};

extern RegisterMemory regMem;
