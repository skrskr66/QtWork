#include "muiscstyleditemdelegate.h"
#include "qrowtableview.h"
#include <QTableView>

MuiscStyledItemDelegate::MuiscStyledItemDelegate()
    : QStyledItemDelegate ()
{

}
//https://github.com/lowbees/Hover-entire-row-of-QTableView
//该方法根据mvc模式的代理对数据项item整行hover选中
void MuiscStyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    opt.state &= ~QStyle::State_HasFocus;

    QRowTableView *view = qobject_cast<QRowTableView*>(opt.styleObject);
    QTableView::SelectionBehavior behavior = view->selectionBehavior();
    QModelIndex hoverIndex = view->hoverIndex();

    if (!(option.state & QStyle::State_Selected) && behavior != QTableView::SelectItems)
    {
        if (behavior == QTableView::SelectRows && hoverIndex.row() == index.row())
        {
            opt.state |= QStyle::State_MouseOver;
        }
        if (behavior == QTableView::SelectColumns && hoverIndex.column() == index.column())
        {
            opt.state |= QStyle::State_MouseOver;
        }
    }
    QStyledItemDelegate::paint(painter, opt, index);
}

