#include "ProfileWidget.h"

ProfileWidget::ProfileWidget(const QString& nameAxis, const QString& title, QWidget *parent)
    : QCustomPlot(parent)
{
    addGraph();
    graph(0)->setPen(QPen(Qt::blue));
    xAxis->setLabel(nameAxis);
    yAxis->setLabel(title);
}

void ProfileWidget::updateProfileX(const std::vector<std::vector<double>> &frame)
{
    if (frame.empty() || frame[0].empty()) return;

    int height = frame.size(); //nombres de lignes (axe y)
    int width = frame[0].size(); //nombre de colonnes(axe x)

    QVector<double> x(width), y(width);

    // Calcul du profil moyen en x
    for (int col = 0; col < width; ++col) {
        double sum = 0.0;
        for (int row = 0; row < height; ++row) {
            sum += frame[row][col];
        }
        x[col] = col;
        y[col] = sum / height;
    }

    graph(0)->setData(x, y);
    xAxis->setRange(0, width);
    yAxis->rescale();
    replot();
}

void ProfileWidget::updateProfileY(const std::vector<std::vector<double>> &frame)
{
    if (frame.empty() || frame[0].empty()) return;

    int height = frame.size(); //nombres de lignes (axe y)
    int width = frame[0].size(); //nombre de colonnes(axe x)

    QVector<double> x(width), y(width);

    // Calcul du profil moyen en y
    for (int row = 0; row < height; ++row) {
        double sum = 0.0;
        for (int col = 0; col < width; ++col) {
 
            sum += frame[row][col];
        }
        x[row] = row;
        y[row] = sum / height;
    }

    graph(0)->setData(x, y);
    xAxis->setRange(0, width);
    yAxis->rescale();
    replot();
}