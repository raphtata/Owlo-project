#include "HeatmapWidget.h"
#include <QPainter>
#include <QTimer>
#include <algorithm>

HeatmapWidget::HeatmapWidget(FrameProvider* pProvider, QWidget* parent)
    : QWidget(parent), p_provider(pProvider), m_minVal(0), m_maxVal(1) {
    p_timer = new QTimer(this); //l'ajout de this permet d'enlever une possible fuite memoire 
    connect(p_timer, &QTimer::timeout, this, &HeatmapWidget::updateFrame);
}

void HeatmapWidget::startTimer() {
    p_timer->start(100); // update toutes les 100 ms
}

void HeatmapWidget::stopTimer() {
    p_timer->stop();
}

bool HeatmapWidget::isTimerRunning() const {
    return p_timer->isActive();
}

void HeatmapWidget::updateFrame() {
    m_currentFrame = p_provider->readCurrentFrame();

    m_minVal = 1e9;
    m_maxVal = -1e9;
    for (auto& row : m_currentFrame) {
        for (double val : row) {
            m_minVal = std::min(m_minVal, val);
            m_maxVal = std::max(m_maxVal, val);
        }
    }
    // appel de la methode paintEvent
    emit newFrame(m_currentFrame);
    update(); 
}

QRgb HeatmapWidget::colormap(double value) const {
    double normalized = (value - m_minVal) / (m_maxVal - m_minVal);
    if (normalized < 0) normalized = 0;
    if (normalized > 1) normalized = 1;

    int r = static_cast<int>(255 * normalized); //plus la valeur est grande, plus c’est rouge
    int g = static_cast<int>(255 * (1 - normalized)); //plus la valeur est petite plus c'est vert
    int b = static_cast<int>(255 * (0.5 - std::abs(normalized - 0.5)) * 2); //moyenne bleue

    return qRgb(r, g, b);
}

void HeatmapWidget::paintEvent(QPaintEvent* pEvent) {
    //Paintevent est appele automatiquement au premier affichage
    //lors de changement d'etat du widget
    if (m_currentFrame.empty()) return;

    int height = m_currentFrame.size();
    int width = m_currentFrame[0].size();

    QImage img(width, height, QImage::Format_RGB32);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            img.setPixel(x, y, colormap(m_currentFrame[y][x]));
        }
    }

    QPainter painter(this);
    painter.drawImage(rect(), img); // étire l’image à la taille du widget
}
