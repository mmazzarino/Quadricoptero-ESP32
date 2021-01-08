#ifndef IHM_DRONE_H
#define IHM_DRONE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class IHM_Drone; }
QT_END_NAMESPACE

class IHM_Drone : public QMainWindow
{
    Q_OBJECT

public:
    IHM_Drone(QWidget *parent = nullptr);
    ~IHM_Drone();

private slots:
    void on_pushButton_clicked();

private:
    Ui::IHM_Drone *ui;
};
#endif // IHM_DRONE_H
