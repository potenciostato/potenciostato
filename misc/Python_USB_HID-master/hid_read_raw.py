import pywinusb.hid as hid


def readData(data):
    #print(data)
    print("Raw data: {0}".format(data))
    return None

# VID and PID customization changes here...
filter = hid.HidDeviceFilter(vendor_id = 0x1fc9, product_id = 0x0081)
hid_device = filter.get_devices()
device = hid_device[0]
device.open()
print(hid_device)

device.set_raw_data_handler(readData)