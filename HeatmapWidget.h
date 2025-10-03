#ifndef HEATMAPWIDGET_H
#define HEATMAPWIDGET_H

#include <QWidget>
#include <QTimer>
#include "FrameProvider.h"

class HeatmapWidget : public QWidget {
    Q_OBJECT

public:
    explicit HeatmapWidget(FrameProvider* provider, QWidget* parent = nullptr);

    void startTimer();
    void stopTimer();
    bool isTimerRunning() const;

protected:
    void paintEvent(QPaintEvent* pEvent) override;

private slots:
    void updateFrame();

private:
    FrameProvider* p_provider;
    Frame m_currentFrame;
    double m_minVal, m_maxVal;
    QTimer* p_timer;

    QRgb colormap(double value) const;
};

#endif // HEATMAPWIDGET_H
