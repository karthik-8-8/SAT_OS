import serial


class SerialReader:

    def __init__(self):

        self.serial = serial.Serial(
            port="COM3",          # Change later
            baudrate=115200,
            timeout=1
        )

    def read(self):

        try:
            return self.serial.readline().decode().strip()

        except:

            return ""