from math import atan2, sqrt, degrees

from PyQt6.QtCore import Qt
from PyQt6.QtGui import QFont, QPixmap
from PyQt6.QtWidgets import (
    QWidget,
    QLabel,
    QVBoxLayout,
    QHBoxLayout,
    QGroupBox,
)

from widgets import TelemetryCard


class Dashboard(QWidget):

    def __init__(self):

        super().__init__()

        self.setWindowTitle("🛰 SAT-OS Ground Station")
        self.resize(1200, 720)

        # ===================================================
        # MAIN LAYOUT
        # ===================================================

        mainLayout = QVBoxLayout()
        mainLayout.setSpacing(15)

        # ===================================================
        # TITLE
        # ===================================================

        title = QLabel("🛰 SAT-OS Ground Station")

        title.setAlignment(Qt.AlignmentFlag.AlignCenter)

        title.setFont(
            QFont(
                "Segoe UI",
                24,
                QFont.Weight.Bold,
            )
        )

        title.setStyleSheet("color:#00D8FF;")

        mainLayout.addWidget(title)

        # ===================================================
        # STATUS BAR
        # ===================================================

        self.status = QLabel(
            "🟢 Connected      COM3      115200 Baud      💾 Logging"
        )

        self.status.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.status.setFont(QFont("Segoe UI", 11))

        self.status.setStyleSheet("""
            background:#23262E;
            border-radius:8px;
            padding:8px;
            color:#7CFC00;
        """)

        mainLayout.addWidget(self.status)

        # ===================================================
        # CENTER
        # ===================================================

        center = QHBoxLayout()

        # ===================================================
        # LEFT PANEL
        # ===================================================

        imageBox = QGroupBox("SAT-OS")

        imageLayout = QVBoxLayout()

        self.image = QLabel()

        self.image.setAlignment(Qt.AlignmentFlag.AlignCenter)

        pix = QPixmap("assets/sat_os.png")

        if not pix.isNull():

            self.image.setPixmap(
                pix.scaled(
                    320,
                    320,
                    Qt.AspectRatioMode.KeepAspectRatio,
                    Qt.TransformationMode.SmoothTransformation,
                )
            )

        else:

            self.image.setText(
                "SAT-OS\n\nImage Missing"
            )

            self.image.setFont(
                QFont("Segoe UI", 16)
            )

        imageLayout.addWidget(self.image)

        imageBox.setLayout(imageLayout)

        # ===================================================
        # RIGHT PANEL
        # ===================================================

        sensorBox = QGroupBox("Live Telemetry")

        sensorLayout = QVBoxLayout()

        self.tempCard = TelemetryCard(
            "🌡 Temperature",
            "-- °C",
        )

        self.pressureCard = TelemetryCard(
            "🌍 Pressure",
            "-- hPa",
        )

        self.altitudeCard = TelemetryCard(
            "⛰ Altitude",
            "-- m",
        )

        self.airCard = TelemetryCard(
            "💨 Air Quality",
            "--",
        )

        sensorLayout.addWidget(self.tempCard)
        sensorLayout.addWidget(self.pressureCard)
        sensorLayout.addWidget(self.altitudeCard)
        sensorLayout.addWidget(self.airCard)

        sensorBox.setLayout(sensorLayout)

        center.addWidget(imageBox, 1)
        center.addWidget(sensorBox, 2)

        mainLayout.addLayout(center)

        # ===================================================
        # ORIENTATION
        # ===================================================

        orientation = QGroupBox("Orientation")

        orientLayout = QHBoxLayout()

        self.roll = QLabel("Roll : 0.0°")
        self.pitch = QLabel("Pitch : 0.0°")

        for lbl in [self.roll, self.pitch]:

            lbl.setFont(
                QFont(
                    "Consolas",
                    15,
                    QFont.Weight.Bold,
                )
            )

            orientLayout.addWidget(lbl)

        orientation.setLayout(orientLayout)

        mainLayout.addWidget(orientation)

        # ===================================================
        # ACCELEROMETER
        # ===================================================

        accelBox = QGroupBox("Accelerometer")

        accelLayout = QHBoxLayout()

        self.ax = QLabel("X : 0.00 g")
        self.ay = QLabel("Y : 0.00 g")
        self.az = QLabel("Z : 0.00 g")

        for lbl in [self.ax, self.ay, self.az]:

            lbl.setFont(
                QFont(
                    "Consolas",
                    13,
                    QFont.Weight.Bold
                )
            )

            accelLayout.addWidget(lbl)

        accelBox.setLayout(accelLayout)

        mainLayout.addWidget(accelBox)

        # ===================================================
        # GYROSCOPE
        # ===================================================

        gyroBox = QGroupBox("Gyroscope")

        gyroLayout = QHBoxLayout()

        self.gx = QLabel("X : 0.00 °/s")
        self.gy = QLabel("Y : 0.00 °/s")
        self.gz = QLabel("Z : 0.00 °/s")

        for lbl in [self.gx, self.gy, self.gz]:

            lbl.setFont(
                QFont(
                    "Consolas",
                    13,
                    QFont.Weight.Bold
                )
            )

            gyroLayout.addWidget(lbl)

        gyroBox.setLayout(gyroLayout)

        mainLayout.addWidget(gyroBox)

        self.setLayout(mainLayout)

    # =======================================================
    # UPDATE TELEMETRY
    # =======================================================

    def updateTelemetry(self, data):

        self.tempCard.value.setText(
            f"{data['temp']:.2f} °C"
        )

        self.pressureCard.value.setText(
            f"{data['pressure']:.2f} hPa"
        )

        self.altitudeCard.value.setText(
            f"{data['altitude']:.2f} m"
        )

        quality = data["mq2"]

        self.airCard.value.setText(quality)

        if quality == "CLEAN":
            self.airCard.value.setStyleSheet(
                "color:#00FF7F;"
            )

        elif quality == "MODERATE":
            self.airCard.value.setStyleSheet(
                "color:yellow;"
            )

        elif quality == "POOR":
            self.airCard.value.setStyleSheet(
                "color:orange;"
            )

        else:
            self.airCard.value.setStyleSheet(
                "color:red;"
            )

        self.ax.setText(
            f"X : {data['ax']:.2f} g"
        )

        self.ay.setText(
            f"Y : {data['ay']:.2f} g"
        )

        self.az.setText(
            f"Z : {data['az']:.2f} g"
        )

        self.gx.setText(
            f"X : {data['gx']:.2f} °/s"
        )

        self.gy.setText(
            f"Y : {data['gy']:.2f} °/s"
        )

        self.gz.setText(
            f"Z : {data['gz']:.2f} °/s"
        )

        # Roll & Pitch

        roll = degrees(
            atan2(
                data["ay"],
                data["az"]
            )
        )

        pitch = degrees(
            atan2(
                -data["ax"],
                sqrt(
                    data["ay"]**2 +
                    data["az"]**2
                )
            )
        )

        self.roll.setText(
            f"Roll : {roll:.1f}°"
        )

        self.pitch.setText(
            f"Pitch : {pitch:.1f}°"
        )