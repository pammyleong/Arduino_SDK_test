#include "usb_ch9.h"
#include "usb_defs.h"
#include "usb_gadget.h"

#if 1
//     <i> Enable high-speed functionality (if device supports it)
#define USBD_HS_ENABLE              1


// define string index
#define STRING_MANUFACTURER     1
#define STRING_PRODUCT          2
#define STRING_SERIALNUMBER     3
#define STRING_INTERFACE        4
#define STRING_VENDOR           5


#define DEV_CONFIG_VALUE    1

#define DRIVER_DESC     "USB Vendor"
#define DRIVER_VERSION  "Feb 2016"

#define MANUFACTURER    "Realtek Singapore Semiconductor"

static __attribute__((aligned(32))) char    string_manufacturer [64] = MANUFACTURER;
static __attribute__((aligned(32))) char    string_product [64] = DRIVER_DESC;
static __attribute__((aligned(32))) char    string_serial [32] = "0123456789";

__attribute__((aligned(32)))struct usb_string
	usbd_vendor_strings [] = {
	{ STRING_MANUFACTURER,  string_manufacturer, },
	{ STRING_PRODUCT,   string_product, },
	{ STRING_SERIALNUMBER,  string_serial, },
	{ STRING_INTERFACE,     "USB VENDOR Interface", },
	{ STRING_VENDOR,        "USB VENDOR", },
};

__attribute__((aligned(32)))struct usb_gadget_strings   vendor_stringtab = {
	.language   = 0x0409,   /* en-us */
	.strings    = usbd_vendor_strings,
};

__attribute__((aligned(32)))struct usb_gadget_strings *dev_vendor_strings[] = {
	&vendor_stringtab,
	NULL,
};
//---------------------------------------------------------------------
__attribute__((aligned(32)))static struct usb_device_descriptor
	usbd_vendor_device_desc = {
	.bLength =      sizeof usbd_vendor_device_desc,
	.bDescriptorType =  USB_DT_DEVICE,

	.bcdUSB = (0x0200),

	.bDeviceClass =     0x00,// define in interface descriptor
	.bDeviceSubClass =  0x00,
	.bDeviceProtocol =  0x00,

	.bMaxPacketSize0 =  64, // this will be set automatically depends on ep0 setting
	.idVendor =         0x0525,
	.idProduct =        0xa4a0,
//	.bcdDevice =         ,
	.iManufacturer =    STRING_MANUFACTURER,
	.iProduct =         STRING_PRODUCT,
	.iSerialNumber =    STRING_SERIALNUMBER,
	.bNumConfigurations = 0x01,
};
//---------------------------------------------------------------------
#if USBD_HS_ENABLE
/* USB Device Qualifier Descriptor (for Full Speed) */
#if 0
__attribute__((aligned(32)))static struct usb_qualifier_descriptor
	usbd_vendor_qualifier_desc_FS = {
	.bLength = sizeof usbd_vendor_qualifier_desc_FS,
	.bDescriptorType = USB_DT_DEVICE_QUALIFIER,
	.bcdUSB = 0x0200,
	.bDeviceClass = 0x00,
	.bDeviceSubClass = 0x00,
	.bDeviceProtocol = 0x00,
	.bMaxPacketSize0 = 64,
	.bNumConfigurations = 0x01,
	.bRESERVED = 0x00,
};

/* USB Device Qualifier Descriptor for High Speed */
__attribute__((aligned(32)))static struct usb_qualifier_descriptor
	usbd_vendor_qualifier_desc_HS = {
	.bLength = sizeof usbd_vendor_qualifier_desc_HS,
	.bDescriptorType = USB_DT_DEVICE_QUALIFIER,
	.bcdUSB = 0x0200,
	.bDeviceClass = 0x00,
	.bDeviceSubClass = 0x00,
	.bDeviceProtocol = 0x00,
	.bMaxPacketSize0 = 64,
	.bNumConfigurations = 0x01,
	.bRESERVED = 0x00,
};
#endif
#else
/* USB Device Qualifier Descriptor (for Full Speed) */
static struct usb_qualifier_descriptor
	usbd_vendor_qualifier_desc_FS    = { 0 };

/* USB Device Qualifier Descriptor for High Speed */
static struct usb_qualifier_descriptor
	usbd_vendor_qualifier_desc_HS = { 0 };
#endif
//---------------------------------------------------------------------
/* MSC Interface, Alternate Setting 0*/
__attribute__((aligned(32)))struct usb_interface_descriptor
	usbd_vendor_intf0_desc = {
	.bLength =      sizeof usbd_vendor_intf0_desc,
	.bDescriptorType =  USB_DT_INTERFACE,

	.bInterfaceNumber = 0x00, // this will be assign automatically
	.bAlternateSetting = 0x00,
	.bNumEndpoints =    0x05,   //20170831
	.bInterfaceClass =  USB_CLASS_VENDOR_SPEC,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface =       STRING_INTERFACE,
};

__attribute__((aligned(32)))struct usb_interface_descriptor
	usbd_vendor_intf1_desc = {
	.bLength =      sizeof usbd_vendor_intf1_desc,
	.bDescriptorType =  USB_DT_INTERFACE,

	.bInterfaceNumber = 0x00, // this will be assign automatically
	.bAlternateSetting = 0x01,
	.bNumEndpoints =    0x05,
	.bInterfaceClass =  USB_CLASS_VENDOR_SPEC,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface =       STRING_INTERFACE,
};
//---------------------------------------------------------------------
#if 1 //wei add
__attribute__((aligned(32)))struct usb_interface_descriptor
	usbd_vendor_intf2_desc = {
	.bLength =      sizeof usbd_vendor_intf2_desc,
	.bDescriptorType =  USB_DT_INTERFACE,

	.bInterfaceNumber = 0x00, // this will be assign automatically
	.bAlternateSetting = 0x02,
	.bNumEndpoints =    0x03,
	.bInterfaceClass =  USB_CLASS_VENDOR_SPEC,
	.bInterfaceSubClass = 0,
	.bInterfaceProtocol = 0,
	.iInterface =       STRING_INTERFACE,
};

#endif
//---------------------------------------------------------------------
/* MSC Endpoints for Low-speed/Full-speed */
/* Endpoint, EP Bulk IN */
__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_bulk_source_desc_FS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,

	.bEndpointAddress = USB_DIR_IN,
	.bmAttributes =     USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize = (64),
	.bInterval = 0x00,

};
/* Endpoint, EP Bulk OUT */
__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_bulk_sink_desc_FS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,

	.bEndpointAddress = USB_DIR_OUT,
	.bmAttributes =     USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize = (64),
	.bInterval = 0x00,
};
//---------------------------------------------------------------------
/* MSC Endpoints for High-speed */
/* Endpoint, EP Bulk IN */
__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_bulk_source_desc_HS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_IN,
	.bmAttributes =     USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize = (512),
	.bInterval = 0x00,
};

/* Endpoint, EP Bulk OUT */
__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_bulk_sink_desc_HS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_OUT,
	.bmAttributes =     USB_ENDPOINT_XFER_BULK,
	.wMaxPacketSize = (512),
	.bInterval = 0x00,
};

//---------------------------------------------------------------------

/* MSC Endpoints for Low-speed/Full-speed */
/* Endpoint, EP Bulk IN */
__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_iso_source_desc_FS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,

	.bEndpointAddress = USB_DIR_IN,
	.bmAttributes =     0X05,
	.wMaxPacketSize = (768),
	.bInterval = 0x01,

};
/* Endpoint, EP Bulk OUT */
__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_iso_sink_desc_FS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,

	.bEndpointAddress = USB_DIR_OUT,
	.bmAttributes =     0X05,
	.wMaxPacketSize = (768),
	.bInterval = 0x01,
};
//---------------------------------------------------------------------
/* MSC Endpoints for High-speed */
/* Endpoint, EP Bulk IN */
__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_iso_source_desc_HS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_IN,
	.bmAttributes =     0X05,
	.wMaxPacketSize = (768),
//	.bInterval = 0x01,
	.bInterval = 0x8,
};

/* Endpoint, EP Bulk OUT */
__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_iso_sink_desc_HS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_OUT,
	.bmAttributes =     0X05,
	.wMaxPacketSize = (768),
//	.bInterval = 0x01,
	.bInterval = 0x8,
};
//--------------------------------------------------
__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_iso2_source_desc_FS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_IN,
	.bmAttributes =     0X05,
	.wMaxPacketSize = (768),
	.bInterval = 0x01,
};

/* Endpoint, EP Bulk OUT */
__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_iso2_sink_desc_FS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_OUT,
	.bmAttributes =     0X05,
	.wMaxPacketSize = (768),
	.bInterval = 0x01,
};

__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_iso2_source_desc_HS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_IN,
	.bmAttributes =     0X05,
	.wMaxPacketSize = (768),
	.bInterval = 0x01,
};

/* Endpoint, EP Bulk OUT */
__attribute__((aligned(32)))struct usb_endpoint_descriptor
	usbd_vendor_iso2_sink_desc_HS = {
	.bLength =      USB_DT_ENDPOINT_SIZE,
	.bDescriptorType =  USB_DT_ENDPOINT,
	.bEndpointAddress = USB_DIR_OUT,
	.bmAttributes =     0X05,
	.wMaxPacketSize = (768),
	.bInterval = 0x01,
};


//---------------------------------------------------

__attribute__((aligned(32))) struct usb_descriptor_header *usbd_vendor_descriptors_FS [] = {
	/* data interface has no altsetting */
	(struct usb_descriptor_header *) &usbd_vendor_intf0_desc,
	(struct usb_descriptor_header *) &usbd_vendor_bulk_source_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_bulk_sink_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso_source_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso_sink_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_intf1_desc,
	(struct usb_descriptor_header *) &usbd_vendor_bulk_source_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_bulk_sink_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso_source_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso_sink_desc_HS,
#if 1 //wei add
	(struct usb_descriptor_header *) &usbd_vendor_intf2_desc,
	(struct usb_descriptor_header *) &usbd_vendor_iso_source_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso_sink_desc_HS,
//	(struct usb_descriptor_header *) &usbd_vendor_iso2_source_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso2_sink_desc_HS,
#endif
	NULL,
};

__attribute__((aligned(32))) struct usb_descriptor_header *usbd_vendor_descriptors_HS [] = {
	/* data interface has no altsetting */
	(struct usb_descriptor_header *) &usbd_vendor_intf0_desc,
	(struct usb_descriptor_header *) &usbd_vendor_bulk_source_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_bulk_sink_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso_source_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso_sink_desc_HS,
#if 1 //wei add for isox2
	(struct usb_descriptor_header *) &usbd_vendor_iso2_source_desc_HS,
#endif
//
	(struct usb_descriptor_header *) &usbd_vendor_intf1_desc,
	(struct usb_descriptor_header *) &usbd_vendor_bulk_source_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_bulk_sink_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso_source_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso_sink_desc_HS,
#if 1 //wei add for isox2
	(struct usb_descriptor_header *) &usbd_vendor_iso2_source_desc_HS,
#endif
#if 1 //wei add
	(struct usb_descriptor_header *) &usbd_vendor_intf2_desc,
	(struct usb_descriptor_header *) &usbd_vendor_iso_source_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso_sink_desc_HS,
	(struct usb_descriptor_header *) &usbd_vendor_iso2_source_desc_HS,
//	(struct usb_descriptor_header *) &usbd_vendor_iso2_sink_desc_HS,
#endif
	NULL,
};
#endif
