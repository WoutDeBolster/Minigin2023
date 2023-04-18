#include "PointsComp.h"

dae::PointsComp::PointsComp(std::shared_ptr<GameObject> pOwner, int points)
	: BaseComponent(pOwner)
	, m_Points{ points }
{
	m_pPointsChanged = std::make_unique<Subject>();
}

void dae::PointsComp::Update(float)
{
}

void dae::PointsComp::AddPoints(int amount)
{
	m_Points += amount;
	m_pPointsChanged.get()->Notify(*m_pGameObject.lock().get(), Event::GainPoints);
}

int dae::PointsComp::GetPoints()
{
	return m_Points;
}

dae::Subject* dae::PointsComp::GetPointSubject() const
{
	return m_pPointsChanged.get();
}
