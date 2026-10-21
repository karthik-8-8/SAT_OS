from PyQt6.QtWidgets import (
    QFrame,
    QLabel,
    QVBoxLayout,
)
from PyQt6.QtGui import QFont
from PyQt6.QtCore import Qt


class TelemetryCard(QFrame):

    def __init__(self, title, value):

        super().__init__()

        self.setMinimumHeight(110)

        self.setStyleSheet("""
        QFrame{
            background:#2C313C;
            border:1px solid #3F4756;
            border-radius:12px;
        }

        QLabel{
            border:none;
            background:transparent;
        }
        """)

        layout = QVBoxLayout()

        layout.setContentsMargins(15, 10, 15, 10)

        self.title = QLabel(title)

        self.title.setFont(QFont("Segoe UI", 10))

        self.title.setStyleSheet("""
        color:#00D8FF;
        font-weight:bold;
        """)

        self.value = QLabel(value)

        self.value.setAlignment(Qt.AlignmentFlag.AlignCenter)

        self.value.setFont(
            QFont(
                "Segoe UI",
                22,
                QFont.Weight.Bold
            )
        )

        self.value.setStyleSheet("""
        color:white;
        """)

        layout.addWidget(self.title)

        layout.addStretch()

        layout.addWidget(self.value)

        layout.addStretch()

        self.setLayout(layout)