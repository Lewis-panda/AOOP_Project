#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QLabel>
#include <QObject>
#include <mainwindow.h>
class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    ClickableLabel();

signals:
    void clicked();

public:
    void mousePressEvent(QMouseEvent* event);
    using QLabel::QLabel;
};

#endif // CLICKABLELABEL_H
