import asyncio
from bleak import BleakScanner, BleakClient
import readchar

device = None
client = None
writeCharacteristic = "0000ffe1-0000-1000-8000-00805f9b34fb"


async def main():
    global device
    global client

    await findDevices()

    await setupConnection()

    await sendData()

    print("-----Closing Connection-----")
    await client.disconnect()


async def findDevices():
    global device

    print("-----Discovering Devices-----")

    devices = await BleakScanner.discover()
    for i in range(len(devices)):
        print(i, "Discovered device:", devices[i])
    
    choice = input("Select which device you wish to connect to:")
    device = devices[int(choice)]


async def setupConnection():
    global device
    global writeCharacteristic
    global client

    print("-----Connecting to device:", device, "-----")

    try:
        client = BleakClient(device.address)
        await client.connect()

        # Showing Services/Characteristics of the Bluetooth Device
        # for service in client.services:
        #     print(f"[Service] {service}")
        #     for char in service.characteristics:
        #         if "read" in char.properties:
        #             try:
        #                 value = bytes(await client.read_gatt_char(char.uuid))
        #                 print(f"\t[Characteristic] {char} ({','.join(char.properties)}), Value: {value}")
        #             except Exception as e:
        #                 print(f"\t[Characteristic] {char} ({','.join(char.properties)}), Value: {e}")
        #         else:
        #             value = None
        #             print(f"\t[Characteristic] {char} ({','.join(char.properties)}), Value: {value}")

        print("Connection succesfull")
    except:
        print("Connection failed")


async def sendData():
    global writeCharacteristic
    global client

    try:
        print("Input data to send")
        while True:            
            data = readchar.readkey()
            if data in ('wsadop'):
                await client.write_gatt_char(writeCharacteristic, data.encode("utf-8"))
            elif data == '.':
                print("Exiting...")
                break
    except KeyboardInterrupt:
        print()
        return




asyncio.run(main())