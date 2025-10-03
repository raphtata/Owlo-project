#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include "FrameProvider.h"
#include "HeatmapWidget.h"
#include "ProfileWidget.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    FrameProvider provider;

    // Fenêtre principale
    QWidget *pCentral = new QWidget;
    //Layout afin de supperposer le bouton et la heatmap
    QVBoxLayout *pLayout = new QVBoxLayout(pCentral);

    // Widget heatmap
    HeatmapWidget *pHeatmap = new HeatmapWidget(&provider);
    pLayout->addWidget(pHeatmap,3);

    // Widget du profile de moyenne en x
    ProfileWidget *pProfileX = new ProfileWidget("X", "Average Intensity");
    pLayout->addWidget(pProfileX, 1);

    // Widget du profile de moyenne en y
    ProfileWidget *pProfileY = new ProfileWidget("Y", "Average Intensity");
    pLayout->addWidget(pProfileY, 1);

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

    // Connexion : quand la heatmap reçoit une nouvelle frame, mettre à jour le profil en X
    QObject::connect(pHeatmap, &HeatmapWidget::newFrame, pProfileX, &ProfileWidget::updateProfileX);

    // Connexion : quand la heatmap reçoit une nouvelle frame, mettre à jour le profil en Y
    QObject::connect(pHeatmap, &HeatmapWidget::newFrame, pProfileY, &ProfileWidget::updateProfileY);

    QMainWindow window;
    window.setCentralWidget(pCentral);
    window.resize(800, 600);
    window.show();

    return app.exec();
}
