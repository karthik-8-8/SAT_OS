import sys

from PyQt6.QtWidgets import QApplication
from PyQt6.QtCore import QTimer

from dashboard import Dashboard
from serial_reader import SerialReader

from parser import parse
from theme import DARK_THEME


app = QApplication(sys.argv)
app.setStyleSheet(DARK_THEME)

window = Dashboard()

reader = SerialReader()


def update():

    line = reader.read()

    if line:

        data = parse(line)

        if data:

            window.updateTelemetry(data)


timer = QTimer()

timer.timeout.connect(update)

timer.start(100)

window.show()

app.exec()