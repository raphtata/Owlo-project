#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include "FrameProvider.h"
#include "HeatmapWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FrameProvider provider;

    // Fenêtre principale
    QWidget *pCentral = new QWidget;
    //Layout afin de supperposer le bouton et la heatmap
    QVBoxLayout *pLayout = new QVBoxLayout(pCentral);

    // Widget heatmap
    HeatmapWidget *pHeatmap = new HeatmapWidget(&provider);
    pLayout->addWidget(pHeatmap);

    // Bouton Play/Stop
    QPushButton *pBtn = new QPushButton("Play");
    pLayout->addWidget(pBtn);

    // Connexion du bouton
    QObject::connect(pBtn, &QPushButton::clicked, [&]() {
        if (pHeatmap->isTimerRunning()) {
            pHeatmap->stopTimer();
            pBtn->setText("Play");
        } else {
            pHeatmap->startTimer();
            pBtn->setText("Stop");
        }
    });

    QMainWindow window;
    window.setCentralWidget(pCentral);
    window.resize(600, 400);
    window.show();

    return app.exec();
}
