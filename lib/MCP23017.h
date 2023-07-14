#ifndef MCP2301_H
#define MCP2301_H

/* C/C++ Includes */

/* Pico SDK Includes */
#include "pico/stdlib.h"
#include "hardware/i2c.h"

typedef enum port
{
    PORT_NULL = -1,
    PORT_A    = 0,
    PORT_B    = 1
} PORT;

typedef enum device_mode
{
    PORT_16_BIT,
    PORT_8_BIT
} PORT_MODE;

/* Struct to hold values to apply to each register initialised to defaults so changes can be applied on a differential basis */
typedef struct mcp23017_config_x
{
    uint8_t port_mode       = PORT_16_BIT;
    uint8_t configured_mode = PORT_16_BIT;
    uint8_t io_config       = 0x00;
    uint8_t iodir_a         = 0xFF;
    uint8_t iodir_b         = 0xFF;
    uint8_t ipol_a          = 0x00;
    uint8_t ipol_b          = 0x00;
    uint8_t gpint_a         = 0x00;
    uint8_t gpint_b         = 0x00;
    uint8_t defval_a        = 0x00;
    uint8_t defval_b        = 0x00;
    uint8_t intcon_a        = 0x00;
    uint8_t intcon_b        = 0x00;
    uint8_t gppu_a          = 0x00;
    uint8_t gppu_b          = 0x00;
    uint8_t intf_a          = 0x00;
    uint8_t intf_b          = 0x00;
} MCP23017_CONFIG_X;

class MCP23017
{
    private:
        i2c_inst_t *i2c_instance;
        uint8_t i2c_address;
        
        MCP23017_CONFIG_X port_config;
        uint8_t port_state[2];

    public:
        MCP23017() = delete; // prevent default construction - requires i2c instance pointer and an address to be set
        MCP23017(i2c_inst_t *i2c_instance,  uint8_t i2c_address);
		
        void write_configuration(void);
        void write_mask(PORT port, uint8_t mask);

        uint8_t read_input_mask(PORT port);
        uint8_t get_port_state(PORT port);

        uint8_t read_intcap_register(PORT port);
        void write_pin(PORT port, uint16_t pin, uint8_t state);

        void set_address_pointer(uint8_t register_location);

        void set_port_mode(PORT_MODE port_mode);
        void set_ioconfig(uint8_t io_config);
        void set_iodir_a(uint8_t iodir_a);
        void set_iodir_b(uint8_t iodir_b);
        void set_ipol_a(uint8_t ipol_a);
        void set_ipol_b(uint8_t ipol_b);
        void set_gpint_a(uint8_t gpint_a);
        void set_gpint_b(uint8_t gpint_b);
        void set_defval_a(uint8_t defval_a);
        void set_defval_b(uint8_t defval_b);
        void set_intcon_a(uint8_t intcon_a);
        void set_intcon_b(uint8_t intcon_b);
        void set_gppu_a(uint8_t gppu_a);
        void set_gppu_b(uint8_t gppu_b);
        void set_intf_a(uint8_t intf_a);
        void set_intf_b(uint8_t intf_b);
		
		void test_output();
        void test_input();
};



typedef enum register_position
{
    IODIR_A,
    IODIR_B,
    IPOL_A,
    IPOL_B,
    GPINTEN_A,
    GPINTEN_B,
    DEFVAL_A,
    DEFVAL_B,
    INTCON_A,
    INTCON_B,
    IOCON_A,
    IOCON_B,
    GPPU_A,
    GPPU_B,
    INTF_A,
    INTF_B,
    INTCAP_A,
    INTCAP_B,
    GPIO_A,
    GPIO_B,
    OLAT_A,
    OLAT_B
} REGISTER_POSITION;


const uint8_t register_address_lookup[2][22]
{
    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15}, // 16Bit
    {0x00, 0x10, 0x01, 0x11, 0x02, 0x12, 0x03, 0x13, 0x04, 0x14, 0x05, 0x15, 0x06, 0x16, 0x07, 0x17, 0x08, 0x18, 0x09, 0x19, 0x0A, 0x1A}  // 8Bit
};

#endif
