import pywinusb.hid as hid
from time import sleep


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
target_usage = hid.get_full_usage_id(0x00, 0x3f)
print(target_usage)


report = device.find_output_reports()

print(report)
print(report[0])

buffer = [0x31]*2
buffer[0] = 0

# data to be transmitted from HID to UART
buffer[1] = 9  # data length;   Range->1 to 9



print(buffer)

report[0].set_raw_data(buffer)
report[0].send()


device.set_raw_data_handler(readData)

# just keep the device opened to receive events
sleep(0.5)