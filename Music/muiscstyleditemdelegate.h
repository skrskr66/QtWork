#ifndef MUISCSTYLEDITEMDELEGATE_H
#define MUISCSTYLEDITEMDELEGATE_H

#include <QStyledItemDelegate>

class MuiscStyledItemDelegate: public QStyledItemDelegate
{
public:
    MuiscStyledItemDelegate();

public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
};

#endif // MUISCSTYLEDITEMDELEGATE_H
