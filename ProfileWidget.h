#pragma once
#include "qcustomplot.h"
#include <vector>

// Widget qui affiche le profil X moyen (moyenne verticale de la heatmap)
class ProfileWidget : public QCustomPlot {
    Q_OBJECT
public:
    explicit ProfileWidget(const QString& nameAxis, const QString& title, QWidget *parent = nullptr);

    // Met à jour le profil à partir d'une frame
    void updateProfileX(const std::vector<std::vector<double>> &frame);
    void updateProfileY(const std::vector<std::vector<double>> &frame);
};


