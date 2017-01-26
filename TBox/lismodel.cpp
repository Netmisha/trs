#include "lismodel.h"

LisModel::LisModel()
{

}
QHash<int, QByteArray> LisModel::roleNames() const
{
    return m_roleNameMapping;
}
