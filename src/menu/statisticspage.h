#ifndef STATISTICSPAGE_H
#define STATISTICSPAGE_H

#include <QWidget>

namespace Ui {
class StatisticsPage;
}

class StatisticsPage : public QWidget
{
    Q_OBJECT

public:
    explicit StatisticsPage(QWidget *parent = nullptr);
    ~StatisticsPage();

private:
    Ui::StatisticsPage *ui;
};

#endif // STATISTICSPAGE_H
