//
    // Created by ky3he4ik on 7/21/19.
//

#include "GridLayoutUtil.h"

// Removes the contents of the given layout row.
void GridLayoutUtil::removeRow(QGridLayout *layout, int row, bool deleteWidgets) {
    remove(layout, row, -1, deleteWidgets);
}

// Removes the contents of the given layout column.
void GridLayoutUtil::removeColumn(QGridLayout *layout, int column, bool deleteWidgets) {
    remove(layout, -1, column, deleteWidgets);
}

// Removes the contents of the given layout cell.
void GridLayoutUtil::removeCell(QGridLayout *layout, int row, int column, bool deleteWidgets) {
    remove(layout, row, column, deleteWidgets);
}

void GridLayoutUtil::removeAll(QGridLayout *layout, bool deleteWidgets) {
    remove(layout, -1, -1, deleteWidgets);
}

// Removes all layout items which span the given row and column.
void GridLayoutUtil::remove(QGridLayout *layout, int row, int column, bool deleteWidgets) {
    // We avoid usage of QGridLayout::itemAtPosition() here to improve performance.
    for (int i = layout->count() - 1; i >= 0; i--) {
        int r, c, rs, cs;
        layout->getItemPosition(i, &r, &c, &rs, &cs);
        if (
                (row == -1 || (r <= row && r + rs > row)) &&
                (column == -1 || (c <= column && c + cs > column))) {
            // This layout item is subject to deletion.
            QLayoutItem *item = layout->takeAt(i);
            if (deleteWidgets) {
                deleteChildWidgets(item);
            }
            delete item;
        }
    }
}

// Deletes all child widgets of the given layout item.
void GridLayoutUtil::deleteChildWidgets(QLayoutItem *item) {
    QLayout *layout = item->layout();
    if (layout) {
// Process all child items recursively.
        int itemCount = layout->count();
        for (int i = 0; i < itemCount; i++) {
            deleteChildWidgets(layout->itemAt(i));
        }
    }
    delete item->widget();
}
