#ifndef POLLINGCONFIGURATION_H
#define POLLINGCONFIGURATION_H

#include <QObject>

#include "ui_pollingconfig.h"

class PollingConfig : public QDialog
{
    Q_OBJECT
public:
    explicit PollingConfig(QWidget *parent = nullptr);
    ~PollingConfig();

signals:

public slots:
    void clicked(QAbstractButton * = nullptr);

private:
    Ui::PollingConfig *ui;
};

#endif // POLLINGCONFIGURATION_H
