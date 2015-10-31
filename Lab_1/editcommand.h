#ifndef EDITCOMMAND_H
#define EDITCOMMAND_H

#include <QUndoCommand>
#include "statstablemodel.h"
#include <utility>

class EditCommand : public QUndoCommand
{
public:
    EditCommand(StatsTableModel &tableMode, int row, QString text, int value, QUndoCommand *parent = 0);

    void redo();
    void undo();

private:
    StatsTableModel &m_tableModel;
    typedef std::pair<QString, int> Item;
    int m_row;
    Item m_oldItem;
    Item m_newItem;
};

#endif // EDITCOMMAND_H
