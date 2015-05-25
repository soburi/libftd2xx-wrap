#include "ftdi.h"
#include <Windows.h>

#include <stdio.h>
#include <stdlib.h>

#undef NDEBUG
#include <assert.h>

#define DBGPRINT(fmt, ...)
//#define DBGPRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)

int ftdi_init(struct ftdi_context *ftdi)
{
	ftdi->handle = (FT_HANDLE)NULL;
	return 0;
}

struct ftdi_context* ftdi_new(void)
{
	struct ftdi_context* p = (struct ftdi_context*)malloc(sizeof(struct ftdi_context));
	return p;
}

int ftdi_set_interface(struct ftdi_context *ftdi, enum ftdi_interface xinterface)
{
	assert(0);
	return 0;
}

void ftdi_deinit(struct ftdi_context *ftdi)
{
	assert(0);
}

void ftdi_free(struct ftdi_context *ftdi)
{
	free(ftdi);
}

void ftdi_set_usbdev (struct ftdi_context *ftdi, usb_dev_handle *usb)
{
	assert(0);
}

int ftdi_usb_find_all(struct ftdi_context *ftdi, struct ftdi_device_list **devlist, int vendor, int product)
{
	assert(0);
	return 0;
}

void ftdi_list_free(struct ftdi_device_list **devlist)
{
	assert(0);
}

void ftdi_list_free2(struct ftdi_device_list *devlist)
{
	assert(0);
}

int ftdi_usb_get_strings(struct ftdi_context * ftdi, struct usb_device * dev,
                         char * manufacturer, int mnf_len, char * description, int desc_len, char * serial, int serial_len)
{
	assert(0);
	return 0;
}

int ftdi_usb_open_dev(struct ftdi_context *ftdi, struct usb_device *dev)
{
	assert(0);
	return 0;
}

int ftdi_usb_open(struct ftdi_context *ftdi, int vendor, int product)
{
	FT_STATUS ret;
	ULONG i = 0;
	DWORD devnum = 0;
	FT_DEVICE_LIST_INFO_NODE* devinfo = NULL;
	int found = -1;

	DBGPRINT("ftdi_usb_open %x %d %04x %04x\n", ftdi, ftdi->handle, vendor, product);

	FT_CreateDeviceInfoList(&devnum);
	
	devinfo = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE*) * devnum);

	for (i = 0; i < devnum; i++)
	{
		FT_STATUS ftStatus;
		FT_HANDLE ftHandleTemp;
		DWORD Flags;
		DWORD ID;
		DWORD Type;
		DWORD LocId;
		char SerialNumber[16];
		char Description[64];

		ftStatus = FT_GetDeviceInfoDetail(i, &Flags, &Type, &ID, &LocId, SerialNumber, Description, &ftHandleTemp);

		if (((ID & 0xFFFF0000) >> 16) == vendor && (ID & 0xFFFF) == product)
		{
			found = i;
		}
	}

	free(devinfo);

	if (found < 0) return -1;
	
	ret = FT_Open(found, &(ftdi->handle) );

	DBGPRINT("FT_Open %x %x %x\n", ret, ftdi, ftdi->handle);

	return ret;
}


int ftdi_usb_open_desc(struct ftdi_context *ftdi, int vendor, int product,
	const char* description, const char* serial)
{
	assert(0);
	return 0;
}

int ftdi_usb_open_desc_index(struct ftdi_context *ftdi, int vendor, int product,
	const char* description, const char* serial, unsigned int index)
{
	assert(0);
	return 0;
}


int ftdi_usb_open_string(struct ftdi_context *ftdi, const char* description)
{
	assert(0);
	return 0;
}

int ftdi_usb_reset(struct ftdi_context *ftdi)
{
	DBGPRINT("ftdi_usb_reset\n");
	return FT_ResetDevice(ftdi->handle);
}

int ftdi_usb_purge_rx_buffer(struct ftdi_context *ftdi)
{
	assert(0);
	return 0;
}

int ftdi_usb_purge_tx_buffer(struct ftdi_context *ftdi)
{
	assert(0);
	return 0;
}

int ftdi_usb_purge_buffers(struct ftdi_context *ftdi)
{
	FT_STATUS ret;
	DBGPRINT("ftdi_usb_purge_buffers %x %x\n", ftdi, ftdi->handle);
	ret = FT_Purge(ftdi->handle, FT_PURGE_RX|FT_PURGE_TX);
	DBGPRINT("ftdi_usb_purge_buffers %x\n", ret);
	return ret;
}

int ftdi_usb_close(struct ftdi_context *ftdi)
{
	FT_STATUS ret;

	DBGPRINT("ftdi_usb_close\n");

	ret = FT_Close(ftdi->handle);

	DBGPRINT("FT_Close %x\n", ret);

	return ret;
}

int ftdi_set_baudrate(struct ftdi_context *ftdi, int baudrate)
{
	FT_STATUS ret;
	DBGPRINT("ftdi_set_baudrate %x %d\n", ftdi->handle, baudrate);
	ret = FT_SetBaudRate(ftdi->handle, baudrate);
	DBGPRINT("ftdi_set_baudrate %d\n", ret);
	return ret;
}

int ftdi_set_line_property(struct ftdi_context *ftdi, enum ftdi_bits_type bits,
enum ftdi_stopbits_type sbit, enum ftdi_parity_type parity)
{
	DBGPRINT("ftdi_set_line_property\n");
	return FT_SetDataCharacteristics(ftdi->handle, bits, sbit, parity);
}

int ftdi_set_line_property2(struct ftdi_context *ftdi, enum ftdi_bits_type bits,
                            enum ftdi_stopbits_type sbit, enum ftdi_parity_type parity,
                            enum ftdi_break_type break_type)
{
	assert(0);
	return 0;
}

int ftdi_write_data(struct ftdi_context *ftdi, unsigned char *buf, int size)
{
	DWORD writebytes = 0;
	FT_STATUS ret;
	DBGPRINT("ftdi_write_data %x %x %x %d\n", ftdi, ftdi->handle, buf, size);
	ret = FT_Write(ftdi->handle, buf, size, &writebytes);

	DBGPRINT("ftdi_write_data %d %d\n", ret, writebytes);
	if (ret > 0) return ret * -1;
	return writebytes;
}

void ftdi_async_complete(struct ftdi_context *ftdi, int wait_for_more)
{
	assert(0);
}

int ftdi_write_data_async(struct ftdi_context *ftdi, unsigned char *buf, int size)
{
	assert(0);
	return 0;
}

int ftdi_write_data_set_chunksize(struct ftdi_context *ftdi, unsigned int chunksize)
{
	assert(0);
	return 0;
}

int ftdi_write_data_get_chunksize(struct ftdi_context *ftdi, unsigned int *chunksize)
{
	assert(0);
	return 0;
}

int ftdi_read_data(struct ftdi_context *ftdi, unsigned char *buf, int size)
{
	DWORD eventdw;
	DWORD txbytes;
	DWORD rxbytes;
	DWORD readbytes = 0;
	DWORD toread = size;
	FT_STATUS ret;

	//DBGPRINT("ftdi_read_data %x %x %x %d\n", ftdi, ftdi->handle, buf, size);
	do {
		int readlen = 0;
		ret = FT_GetStatus(ftdi->handle, &rxbytes, &txbytes, &eventdw);
		DBGPRINT("FT_GetStatus %x %d %d %d\n", ftdi->handle, ret, rxbytes, txbytes);
		if(ret != 0) break;
		//if(rxbytes == 0) break;

		readlen = toread < rxbytes ? toread : rxbytes;

		ret = FT_Read(ftdi->handle, buf, readlen, &readbytes);

		buf += readbytes;
		toread -= readbytes;

	} while(toread > 0);


	//DBGPRINT("ftdi_read_data %d %d\n", ret, (size - toread));

	if (ret > 0) return ret * -1;
	return (size - toread);
}
int ftdi_read_data_set_chunksize(struct ftdi_context *ftdi, unsigned int chunksize)
{
	assert(0);
	return 0;
}

int ftdi_read_data_get_chunksize(struct ftdi_context *ftdi, unsigned int *chunksize)
{
	assert(0);
	return 0;
}

int ftdi_enable_bitbang(struct ftdi_context *ftdi, unsigned char bitmask)
{
	assert(0);
	return 0;
}

int ftdi_disable_bitbang(struct ftdi_context *ftdi)
{
	DBGPRINT("ftdi_disable_bitbang\n");
	return FT_SetBitMode(ftdi->handle, 0, 0);
}

int ftdi_set_bitmode(struct ftdi_context *ftdi, unsigned char bitmask, unsigned char mode)
{
	DBGPRINT("ftdi_set_bitmode\n");
	return FT_SetBitMode(ftdi->handle, bitmask, mode);
}

int ftdi_read_pins(struct ftdi_context *ftdi, unsigned char *pins)
{
	assert(0);
	return 0;
}

int ftdi_set_latency_timer(struct ftdi_context *ftdi, unsigned char latency)
{
	assert(0);
	return 0;
}

int ftdi_get_latency_timer(struct ftdi_context *ftdi, unsigned char *latency)
{
	assert(0);
	return 0;
}

int ftdi_poll_modem_status(struct ftdi_context *ftdi, unsigned short *status)
{
	assert(0);
	return 0;
}

int ftdi_setflowctrl(struct ftdi_context *ftdi, int flowctrl)
{
	DBGPRINT("ftdi_setflowctrl\n");
	//TODO if (flowctrl == SIO_XON_XOFF_HS) 
	return FT_SetFlowControl(ftdi->handle, flowctrl, 0, 0);
}

int ftdi_setdtr(struct ftdi_context *ftdi, int state)
{
	assert(0);
	return 0;
}

int ftdi_setrts(struct ftdi_context *ftdi, int state)
{
	DBGPRINT("ftdi_setrts\n");
	if (state == SIO_SET_RTS_HIGH) 
		return FT_SetRts(ftdi->handle);
	else 
		return FT_ClrRts(ftdi->handle);
}

int ftdi_setdtr_rts(struct ftdi_context *ftdi, int dtr, int rts)
{
	assert(0);
	return 0;
}

int ftdi_set_event_char(struct ftdi_context *ftdi,
                        unsigned char eventch, unsigned char enable)
{
	assert(0);
	return 0;
}

int ftdi_set_error_char(struct ftdi_context *ftdi,
                        unsigned char errorch, unsigned char enable)
{
	assert(0);
	return 0;
}

void ftdi_eeprom_setsize(struct ftdi_context *ftdi, struct ftdi_eeprom *eeprom, int size)
{
	assert(0);
}

void ftdi_eeprom_initdefaults(struct ftdi_eeprom *eeprom)
{
	assert(0);
}

void ftdi_eeprom_free(struct ftdi_eeprom *eeprom)
{
	assert(0);
}

int ftdi_eeprom_build(struct ftdi_eeprom *eeprom, unsigned char *output)
{
	assert(0);
	return 0;
}

int ftdi_eeprom_decode(struct ftdi_eeprom *eeprom, unsigned char *buf, int size)
{
	assert(0);
	return 0;
}
int ftdi_read_eeprom_location (struct ftdi_context *ftdi, int eeprom_addr, unsigned short *eeprom_val)
{
	assert(0);
	return 0;
}
int ftdi_read_eeprom(struct ftdi_context *ftdi, unsigned char *eeprom)
{
	assert(0);
	return 0;
}
int ftdi_read_chipid(struct ftdi_context *ftdi, unsigned int *chipid)
{
	assert(0);
	return 0;
}
int ftdi_read_eeprom_getsize(struct ftdi_context *ftdi, unsigned char *eeprom, int maxsize)
{
	assert(0);
	return 0;
}
int ftdi_write_eeprom_location(struct ftdi_context *ftdi, int eeprom_addr, unsigned short eeprom_val)
{
	assert(0);
	return 0;
}
int ftdi_write_eeprom(struct ftdi_context *ftdi, unsigned char *eeprom)
{
	assert(0);
	return 0;
}
int ftdi_erase_eeprom(struct ftdi_context *ftdi)
{
	assert(0);
	return 0;
}

char *ftdi_get_error_string(struct ftdi_context *ftdi)
{
	DBGPRINT("ftdi_get_error_string\n");
	return "not supported";
}
