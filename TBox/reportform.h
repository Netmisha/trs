#ifndef REPORTFORM_H
#define REPORTFORM_H

#include <QWidget>
#include <QQuickView>
#include <QDebug>
namespace Ui {
class ReportForm;
}

class ReportForm : public QWidget
{
    Q_OBJECT


signals:
    void DateChanged();
public:
    explicit ReportForm(QWidget *parent = 0);
    ~ReportForm();

private:
    Ui::ReportForm *ui;
};

#endif // REPORTFORM_H
