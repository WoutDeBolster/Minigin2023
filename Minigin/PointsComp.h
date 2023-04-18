#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class PointsComp final : public BaseComponent
	{
	public:
		PointsComp(std::shared_ptr<GameObject> pOwner, int points = 0);
		~PointsComp() = default;

		PointsComp(const PointsComp&) = delete;
		PointsComp(PointsComp&&) = delete;
		PointsComp& operator= (const PointsComp&) = delete;
		PointsComp& operator= (const PointsComp&&) = delete;

		void Update(float deltaTime) override;
		void AddPoints(int amount);

		int GetPoints();
		Subject* GetPointSubject() const;

	private:
		std::unique_ptr<Subject> m_pPointsChanged;

		int m_Points;
	};
}