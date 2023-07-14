/* C/C++ Includes */
#include <stdio.h>

/* Pico SDK Includes */
#include "MCP23017.hpp"

MCP23017::MCP23017(i2c_inst_t *i2c_instance,  uint8_t i2c_address)
{
    this->i2c_instance = i2c_instance;       
    this->i2c_address  = i2c_address;
}


/* Writes the current configuration values to the MCP23017 registers */
void MCP23017::write_configuration(void)
{
    uint8_t buffer[2];

    //IOCON
    buffer[0] = register_address_lookup[port_config.configured_mode][IOCON_A];
    buffer[1] = port_config.io_config;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    port_config.configured_mode = port_config.port_mode;

    //IODIR_A
    buffer[0] = register_address_lookup[port_config.port_mode][IODIR_A];
    buffer[1] = port_config.iodir_a;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //IODIR_B
    buffer[0] = register_address_lookup[port_config.port_mode][IODIR_B];
    buffer[1] = port_config.iodir_b;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //IPOL_A
    buffer[0] = register_address_lookup[port_config.port_mode][IPOL_A];
    buffer[1] = port_config.ipol_a;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //IPOL_B
    buffer[0] = register_address_lookup[port_config.port_mode][IPOL_B];
    buffer[1] = port_config.ipol_b;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //GPINTEN_A
    buffer[0] = register_address_lookup[port_config.port_mode][GPINTEN_A];
    buffer[1] = port_config.gpint_a;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);
    
    //GPINTEN_B
    buffer[0] = register_address_lookup[port_config.port_mode][GPINTEN_B];
    buffer[1] = port_config.gpint_b;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //DEFVAL_A
    buffer[0] = register_address_lookup[port_config.port_mode][DEFVAL_A];
    buffer[1] = port_config.defval_a;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //DEFVAL_B
    buffer[0] = register_address_lookup[port_config.port_mode][DEFVAL_B];
    buffer[1] = port_config.defval_b;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //INTCON_A
    buffer[0] = register_address_lookup[port_config.port_mode][INTCON_A];
    buffer[1] = port_config.intcon_a;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //INTCON_B
    buffer[0] = register_address_lookup[port_config.port_mode][INTCON_B];
    buffer[1] = port_config.intcon_b;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //GPPU_A
    buffer[0] = register_address_lookup[port_config.port_mode][GPPU_A];
    buffer[1] = port_config.gppu_a;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //GPPU_B
    buffer[0] = register_address_lookup[port_config.port_mode][GPPU_B];
    buffer[1] = port_config.gppu_b;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //INTF_A
    buffer[0] = register_address_lookup[port_config.port_mode][INTF_A];
    buffer[1] = port_config.intf_a;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);

    //INTF_B
    buffer[0] = register_address_lookup[port_config.port_mode][INTF_B];
    buffer[1] = port_config.intf_b;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, sizeof(buffer), false);
}


void MCP23017::write_mask(PORT port, uint8_t mask)
{
    uint8_t buffer[2];
    printf("MCP23017::write_mask()\n");
    switch(port)
    {
        case PORT_A:
            buffer[0] = register_address_lookup[port_config.port_mode][GPIO_A];
            break;
        case PORT_B:
            buffer[0] = register_address_lookup[port_config.port_mode][GPIO_B];
            break;
    }    

    buffer[1] = mask;
    i2c_write_blocking(i2c_instance, i2c_address, buffer, 2, false);

    port_state[port] = mask;
    
    printf("MCP23017::write_mask() DONE\n");
}


uint8_t MCP23017::read_input_mask(PORT port)
{
    uint8_t address;
    uint8_t data;

    switch(port)
    {
        case 0:
            address = register_address_lookup[port_config.port_mode][GPIO_A];
            break;
        case 1:
            address = register_address_lookup[port_config.port_mode][GPIO_B];
            break;
        default:
            break;
    }

    set_address_pointer(address);

    i2c_read_blocking(i2c_instance, i2c_address, &data, 1 , false);

    port_state[port] = data;

    return data;
}


uint8_t MCP23017::get_port_state(PORT port)
{
    return port_state[port];
}


uint8_t MCP23017::read_intcap_register(PORT port)
{
    uint8_t address;
    uint8_t data;

    switch(port)
    {
        case 0:
            address = register_address_lookup[port_config.port_mode][INTCAP_A];
            break;
        case 1:
            address = register_address_lookup[port_config.port_mode][INTCAP_B];
            break;
        default:
            break;
    }

    set_address_pointer(address);

    i2c_read_blocking(i2c_instance, i2c_address, &data, 1 , false);
    return data;
}


void MCP23017::write_pin(PORT port, uint16_t pin, uint8_t state)
{
     if(state)
    {
        port_state[port] |= (0x01 << pin);
    }
    else
    {
        port_state[port] ^= (0x00 << pin);
    }

    write_mask(port, port_state[port]);
}


void MCP23017::set_address_pointer(uint8_t register_location)
{
    uint8_t command = register_address_lookup[port_config.port_mode][register_location];

    i2c_write_blocking(i2c_instance, i2c_address, &command, 1 , false);
}


void MCP23017::set_port_mode(PORT_MODE port_mode)
{
    this->port_config.port_mode = port_mode;
}

void MCP23017::set_ioconfig(uint8_t io_config)
{
    this->port_config.io_config = io_config;
}

void MCP23017::set_iodir_a(uint8_t iodir_a)
{
    this->port_config.iodir_a = iodir_a;
}

void MCP23017::set_iodir_b(uint8_t iodir_b)
{
    this->port_config.iodir_b = iodir_b;
}

void MCP23017::set_ipol_a(uint8_t ipol_a)
{
    this->port_config.ipol_a = ipol_a;
}

void MCP23017::set_ipol_b(uint8_t ipol_b)
{
    this->port_config.ipol_b = ipol_b;
}

void MCP23017::set_gpint_a(uint8_t gpint_a)
{
    this->port_config.gpint_a = gpint_a;
}

void MCP23017::set_gpint_b(uint8_t gpint_b)
{
    this->port_config.gpint_b = gpint_b;
}

void MCP23017::set_defval_a(uint8_t defval_a)
{
    this->port_config.defval_a = defval_a;
}

void MCP23017::set_defval_b(uint8_t defval_b)
{
    this->port_config.defval_b = defval_b;
}

void MCP23017::set_intcon_a(uint8_t intcon_a)
{
    this->port_config.intcon_a = intcon_a;
}

void MCP23017::set_intcon_b(uint8_t intcon_b)
{
    this->port_config.intcon_b = intcon_b;
}

void MCP23017::set_gppu_a(uint8_t gppu_a)
{
    this->port_config.gppu_a = gppu_a;
}

void MCP23017::set_gppu_b(uint8_t gppu_b)
{
    this->port_config.gppu_b  = gppu_b;
}

void MCP23017::set_intf_a(uint8_t intf_a)
{
    this->port_config.intf_a = intf_a;
}

void MCP23017::set_intf_b(uint8_t intf_b)
{
    this->port_config.intf_b = intf_b;
}

void MCP23017::test_output(void)
{
    uint8_t counter = 0;
    printf("Starting Output Test\n");

    while(1)
    {
        write_mask(PORT_A, counter);
        write_mask(PORT_B, counter);

        sleep_ms(1000);

        counter++;
    }
}

void MCP23017::test_input(void)
{
    printf("Starting Input Test\n");

    while(1)
    {
        printf("Port A: %02x\n", read_input_mask(PORT_A));
        printf("Port B: %02x\n", read_input_mask(PORT_B));
        sleep_ms(1000);
    }
}