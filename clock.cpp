#include "clock.h"

Clock::Clock(QWidget *parent)
    : QWidget(parent),
      updateClock(new QTimer(this)),
      hoursInClock(12),
      minutesInHour(60),
      secondsInMinute(60),
      degreesPerHour(30),
      degreesPerMinutes(6)
{
    connect(updateClock, SIGNAL(timeout()), SLOT(update()));
    updateClock->start(1000 * 60);
    QFont font;
    font.setPointSize(5);
    setFont(font);
}

void Clock::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int side = qMin(width(), height());
    painter.setViewport((width() - height()) / 2, (height() - side) / 2, side, side);
    painter.setWindow(-100, -100, 200, 200);

    QRadialGradient haloGradient(0, 0, 20, 0, 0);
    haloGradient.setColorAt(0.2, QColor(238,207,186));
    haloGradient.setColorAt(0.9, QColor(216,215,212));
    haloGradient.setColorAt(1.0, QColor(197, 221, 232));

    painter.setPen(Qt::NoPen);
    painter.setBrush(haloGradient);
    painter.drawEllipse(-40, -40, 80, 80);

    painter.setPen(QPen(Qt::black, 2, Qt::SolidLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(-40, -40, 80, 80);

    for (int i = 1; i <= hoursInClock; ++i) {
        painter.drawText(-8, -55, 15, 20,
                         Qt::AlignCenter | Qt::AlignTop,
                         QString::number(hours[i - 1]));
        painter.rotate(degreesPerHour);
    }

    drawPointers(painter);

    painter.setPen(QPen(Qt::red, 2, Qt::SolidLine));
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(-1, -1, 2, 2);
}

void Clock::drawPointers(QPainter & painter) {
    static const int triangleMinutes[3][2] = {
        {-2, 0}, {2, 0}, {0, -38}
    };
    static const int triangleHours[3][2] = {
        {-2, 0}, {2, 0}, {0, -19}
    };
    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);

    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush(hourColor);
    painter.rotate(degreesPerMinutes * QTime::currentTime().second());
    painter.drawPolygon(QPolygon(3, &triangleMinutes[0][0]));


    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
    painter.setBrush(minuteColor);
    painter.rotate(degreesPerHour * (QTime::currentTime().hour() % 12));
    painter.drawPolygon(QPolygon(3, &triangleHours[0][0]));

}

Clock::~Clock()
{
}

