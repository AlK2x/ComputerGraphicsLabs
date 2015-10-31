#ifndef DELETEROWCOMMAND_H
#define DELETEROWCOMMAND_H

#include <QUndoCommand>
#include <set>
#include <map>
#include <utility>
#include "statstablemodel.h"

class DeleteRowCommand : public QUndoCommand
{
public:
    DeleteRowCommand(StatsTableModel &tableModel, std::set<int> deletedRows, QUndoCommand *parent = 0);

    void undo();
    void redo();

private:
    typedef std::pair<QString, int> t_row;
    StatsTableModel &m_tableModel;
    std::map<int, t_row> m_restoredValues;
    std::set<int> m_deletedRows;
};

#endif // DELETEROWCOMMAND_H
