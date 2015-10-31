#include "deleterowcommand.h"

DeleteRowCommand::DeleteRowCommand(StatsTableModel &tableModel, std::set<int> deletedRows, QUndoCommand * parent)
    :QUndoCommand(parent), m_tableModel(tableModel), m_deletedRows(deletedRows)
{

}

void DeleteRowCommand::redo()
{
    auto model = m_tableModel.statsModel();
    StatsKeyValueModel newModel;
    for (size_t i = 0; i < model.size(); ++i)
    {
        if (m_deletedRows.count(i))
        {
            m_restoredValues[i]= std::make_pair(model.key(i), model.value(i));
            continue;
        }
        newModel.append(model.key(i), model.value(i));
    }
    m_tableModel.setStatsModel(newModel);
}

void DeleteRowCommand::undo()
{
    auto model = m_tableModel.statsModel();
    StatsKeyValueModel newModel;
    std::map<int, t_row>::iterator it = m_restoredValues.begin();
    for (size_t i = 0; i < model.size(); ++i)
    {
        if (m_restoredValues.count(i))
        {
            newModel.append(it->second.first, it->second.second);
            ++it;
        }
        newModel.append(model.key(i), model.value(i));
    }

    while (it != m_restoredValues.end())
    {
        newModel.append(it->second.first, it->second.second);
        ++it;
    }
    m_tableModel.setStatsModel(newModel);
}

