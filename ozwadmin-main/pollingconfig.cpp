#include <limits>

#include <QIntValidator>

#include "pollingconfig.h"
#include "ozwcore.h"
#include "util.h"

PollingConfig::PollingConfig(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PollingConfig)
{
    ui->setupUi(this);

    auto pollInterval = OZWCore::get()->getQTOZWManager()->getPollInterval();

    ui->pollingInterval->setText(QString::number(pollInterval));
    ui->pollingInterval->setValidator(new QIntValidator(0, std::numeric_limits<qint32>::max(), this));
    connect(ui->buttonBox, &QDialogButtonBox::clicked,
              this, &PollingConfig::clicked);
}

PollingConfig::~PollingConfig() {
    delete ui;
}

void PollingConfig::clicked(QAbstractButton *btn)
{
    switch (ui->buttonBox->buttonRole(btn)) {
    case QDialogButtonBox::AcceptRole:
        OZWCore::get()->getQTOZWManager()->setPollInterval(ui->pollingInterval->text().toInt(), true);
        this->close();
        break;

    case QDialogButtonBox::RejectRole:
        this->close();
        break;

    default:
        break;
    }
}
