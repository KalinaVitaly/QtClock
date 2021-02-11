#ifndef CLOCK_H
#define CLOCK_H

#include <QWidget>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QPolygon>

class Clock : public QWidget
{
    Q_OBJECT

public:
    Clock(QWidget *parent = nullptr);
    ~Clock();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QTimer *updateClock;
    uint8_t hours[12] {12, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    uint8_t currentHour;
    uint8_t currentMinutes;
    uint8_t currentSeconds;

    const uint8_t hoursInClock;
    const uint8_t minutesInHour;
    const uint8_t secondsInMinute;
    const uint8_t degreesPerHour;
    const uint8_t degreesPerMinute;
    const uint8_t degreesPerSecond;

    QColor hourColor;
    QColor minuteColor;
    QColor secondColor;

    void drawPointers(QPainter &);
};
#endif // CLOCK_H
