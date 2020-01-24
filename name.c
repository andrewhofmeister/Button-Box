// Change the device name

#include "usb_names.h"

#define DEVICE_NAME {'B','u','t','t','o','n',' ', 'B','o','x'}
#define DEVICE_NAME_LEN 10

struct usb_string_descriptor_struct usb_string_product_name = {
        2 + DEVICE_NAME_LEN * 2,
        3,
        DEVICE_NAME
};
