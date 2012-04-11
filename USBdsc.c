const unsigned int USB_VENDOR_ID = 0x1234;
const unsigned int USB_PRODUCT_ID = 0x0001;
const char USB_SELF_POWER = 0x80;            // Self powered 0xC0,  0x80 bus powered
const char USB_MAX_POWER = 50;               // Bus power required in units of 2 mA
const char HID_INPUT_REPORT_BYTES = 4;
const char HID_OUTPUT_REPORT_BYTES = 1;
const char USB_TRANSFER_TYPE = 0x03;         //0x03 Interrupt
const char EP_IN_INTERVAL = 1;
const char EP_OUT_INTERVAL = 1;

const char USB_INTERRUPT = 1;
const char USB_HID_EP = 1;
const char USB_HID_RPT_SIZE = 44;

#define USB_EP0_BUFF_SIZE               8
/* Device Descriptor */
const struct {
    char bLength;               // bLength         - Descriptor size in bytes (12h)
    char bDescriptorType;       // bDescriptorType - The constant DEVICE (01h)
    unsigned int bcdUSB;        // bcdUSB          - USB specification release number (BCD)
    char bDeviceClass;          // bDeviceClass    - Class Code
    char bDeviceSubClass;       // bDeviceSubClass - Subclass code
    char bDeviceProtocol;       // bDeviceProtocol - Protocol code
    char bMaxPacketSize0;       // bMaxPacketSize0 - Maximum packet size for endpoint 0
    unsigned int idVendor;      // idVendor        - Vendor ID
    unsigned int idProduct;     // idProduct       - Product ID
    unsigned int bcdDevice;     // bcdDevice       - Device release number (BCD)
    char iManufacturer;         // iManufacturer   - Index of string descriptor for the manufacturer
    char iProduct;              // iProduct        - Index of string descriptor for the product.
    char iSerialNumber;         // iSerialNumber   - Index of string descriptor for the serial number.
    char bNumConfigurations;    // bNumConfigurations - Number of possible configurations
} device_dsc = {
      0x12,                   // bLength
      0x01,                   // bDescriptorType
      0x0200,                 // bcdUSB
      0x00,                   // bDeviceClass
      0x00,                   // bDeviceSubClass
      0x00,                   // bDeviceProtocol
      USB_EP0_BUFF_SIZE,                      // bMaxPacketSize0
      USB_VENDOR_ID,          // idVendor
      USB_PRODUCT_ID,         // idProduct
      0x0003,                 // bcdDevice
      0x01,                   // iManufacturer
      0x02,                   // iProduct
      0x00,                   // iSerialNumber
      0x01                    // bNumConfigurations
  };

/* Configuration 1 Descriptor */
const char configDescriptor1[]= {
    // Configuration Descriptor
    0x09,                   // bLength             - Descriptor size in bytes
    0x02,                   // bDescriptorType     - The constant CONFIGURATION (02h)
    0x29,0x00,              // wTotalLength        - The number of bytes in the configuration descriptor and all of its subordinate descriptors
    1,                      // bNumInterfaces      - Number of interfaces in the configuration
    1,                      // bConfigurationValue - Identifier for Set Configuration and Get Configuration requests
    0,                      // iConfiguration      - Index of string descriptor for the configuration
    USB_SELF_POWER,         // bmAttributes        - Self/bus power and remote wakeup settings
    USB_MAX_POWER,          // bMaxPower           - Bus power required in units of 2 mA

    // Interface Descriptor
    0x09,                   // bLength - Descriptor size in bytes (09h)
    0x04,                   // bDescriptorType - The constant Interface (04h)
    0,                      // bInterfaceNumber - Number identifying this interface
    0,                      // bAlternateSetting - A number that identifies a descriptor with alternate settings for this bInterfaceNumber.
    1,                      // bNumEndpoint - Number of endpoints supported not counting endpoint zero
    0x03,                   // bInterfaceClass - Class code
    0,                      // bInterfaceSubclass - Subclass code
    0,                      // bInterfaceProtocol - Protocol code
    0,                      // iInterface - Interface string index

    // HID Class-Specific Descriptor
    0x09,                   // bLength - Descriptor size in bytes.
    0x21,             // bDescriptorType - This descriptor's type: 21h to indicate the HID class.
    0x101,              // bcdHID - HID specification release number (BCD).
    0x00,                   // bCountryCode - Numeric expression identifying the country for localized hardware (BCD) or 00h.
    1,                      // bNumDescriptors - Number of subordinate report and physical descriptors.
    0x22,                   // bDescriptorType - The type of a class-specific descriptor that follows
    0x32,  // wDescriptorLength - Total length of the descriptor identified above.

    // Endpoint Descriptor
    0x07,                   // bLength - Descriptor size in bytes (07h)
    0x05,                   // bDescriptorType - The constant Endpoint (05h)
    0b10000010,      // bEndpointAddress - Endpoint number and direction
    0b00000011,      // bmAttributes - Transfer type and supplementary information
    0x0008,              // wMaxPacketSize - Maximum packet size supported
    0x0A,         // bInterval - Service interval or NAK rate

   };

const struct {
  char report[USB_HID_RPT_SIZE];
}hid_rpt_desc =
  {
     {0x05, 0x01, /* Usage Page (Generic Desktop)             */
    0x09, 0x02, /* Usage (Mouse)                            */
    0xA1, 0x01, /* Collection (Application)                 */
    0x09, 0x01, /*  Usage (Pointer)                         */
    0xA1, 0x00, /*  Collection (Physical)                   */
    0x05, 0x09, /*      Usage Page (Buttons)                */
    0x19, 0x01, /*      Usage Minimum (01)                  */
    0x29, 0x03, /*      Usage Maximum (03)                  */
    0x15, 0x00, /*      Logical Minimum (0)                 */
    0x25, 0x01, /*      Logical Maximum (0)                 */
    0x95, 0x03, /*      Report Count (3)                    */
    0x75, 0x01, /*      Report Size (1)                     */
    0x81, 0x02, /*      Input (Data, Variable, Absolute)    */
    0x95, 0x01, /*      Report Count (1)                    */
    0x75, 0x05, /*      Report Size (5)                     */
    0x81, 0x01, /*      Input (Constant)    ;5 bit padding  */
    0x05, 0x01, /*      Usage Page (Generic Desktop)        */
    0x09, 0x30, /*      Usage (X)                           */
    0x09, 0x31, /*      Usage (Y)                           */
    0x15, 0x81, /*      Logical Minimum (-127)              */
    0x25, 0x7F, /*      Logical Maximum (127)               */
    0x75, 0x08, /*      Report Size (8)                     */
    0x95, 0x02, /*      Report Count (2)                    */
    0x81, 0x06, /*      Input (Data, Variable, Relative)    */
    0xC0, 0xC0}
}                   // End Collection
  };

//Language code string descriptor
const struct {
  char bLength;
  char bDscType;
  unsigned int string[1];
  } strd1 = {
      4,
      0x03,
      {0x0409}
    };


//Manufacturer string descriptor
const struct{
  char bLength;
  char bDscType;
  unsigned int string[3];
  }strd2={
    8,           //sizeof this descriptor string
    0x03,
    {'A',' ','J'}
  };

//Product string descriptor
const struct{
  char bLength;
  char bDscType;
  unsigned int string[5];
}strd3={
    12,          //sizeof this descriptor string
    0x03,
    {'M','o','u','s','e'}
 };

//Array of configuration descriptors
const char* USB_config_dsc_ptr[1];

//Array of string descriptors
const char* USB_string_dsc_ptr[3];

void USB_Init_Desc(){
  USB_config_dsc_ptr[0] = &configDescriptor1;
  USB_string_dsc_ptr[0] = (const char*)&strd1;
  USB_string_dsc_ptr[1] = (const char*)&strd2;
  USB_string_dsc_ptr[2] = (const char*)&strd3;
}