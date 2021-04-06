#pragma once
#ifndef QROWTABLEVIEW_H
#define QROWTABLEVIEW_H

#include <QTableView>

class QRowTableView : public QTableView
{
    Q_OBJECT
public:
    QRowTableView(QWidget *parent = nullptr);

    QModelIndex hoverIndex() const { return model()->index(mHoverRow, mHoverColumn); }

    // QWidget interface
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
signals:
    void sgnRClickMenu();
private:
    int mHoverRow, mHoverColumn;
};
#endif // QROWTABLEVIEW_H
