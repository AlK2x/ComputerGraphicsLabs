#include "editcommand.h"


EditCommand::EditCommand(StatsTableModel &tableModel, int row, QString text, int value, QUndoCommand *parent)
    :QUndoCommand(parent), m_row(row), m_tableModel(tableModel)
{
    auto model = m_tableModel.statsModel();
    m_oldItem = std::make_pair(model.key(row), model.value(row));
    m_newItem = std::make_pair(text, value);
}

void EditCommand::redo()
{
    auto model = m_tableModel.statsModel();
    model.setKey(m_row, m_newItem.first);
    model.setValue(m_row, m_newItem.second);
    m_tableModel.setStatsModel(model);
}

void EditCommand::undo()
{
    auto model = m_tableModel.statsModel();
    model.setKey(m_row, m_oldItem.first);
    model.setValue(m_row, m_oldItem.second);
    m_tableModel.setStatsModel(model);
}
