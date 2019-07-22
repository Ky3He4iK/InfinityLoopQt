//
// Created by ky3he4ik on 7/21/19.
//

#ifndef GAME_GRIDLAYOUTUTIL_H
#define GAME_GRIDLAYOUTUTIL_H


#include <QGridLayout>
#include <QWidget>

/**
 * Utility class to remove the contents of a QGridLayout row, column or
 * cell. If the deleteWidgets parameter is true, then the widgets become
 * not only removed from the layout, but also deleted. Note that we won't
 * actually remove any row or column itself from the layout, as this isn't
 * possible. So the rowCount() and columnCount() will always stay the same,
 * but the contents of the row, column or cell will be removed.
 */
class GridLayoutUtil {

public:

    // Removes the contents of the given layout row.
    static void removeRow(QGridLayout *layout, int row, bool deleteWidgets = true);

    // Removes the contents of the given layout column.
    static void removeColumn(QGridLayout *layout, int column, bool deleteWidgets = true);

    // Removes the contents of the given layout cell.
    static void removeCell(QGridLayout *layout, int row, int column, bool deleteWidgets = true);

    static void removeAll(QGridLayout *layout, bool deleteWidgets = true);

private:

    // Removes all layout items which span the given row and column.
    static void remove(QGridLayout *layout, int row, int column, bool deleteWidgets);

    // Deletes all child widgets of the given layout item.
    static void deleteChildWidgets(QLayoutItem *item);
};


#endif //GAME_GRIDLAYOUTUTIL_H
