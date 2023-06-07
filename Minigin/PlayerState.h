//#pragma once
//#include <memory>
//#include "GameObject.h"
//
//namespace dae
//{
//	class PlayerState
//	{
//	public:
//		PlayerState(std::shared_ptr<GameObject> pPlayer);
//		virtual ~PlayerState() = default;
//
//		PlayerState(const PlayerState&) = delete;
//		PlayerState(PlayerState&&) = delete;
//		PlayerState& operator= (const PlayerState&) = delete;
//		PlayerState& operator= (const PlayerState&&) = delete;
//
//		virtual void HandleInput() = 0;
//		virtual void Update() = 0;
//
//		static MovingState moving;
//
//	protected:
//		std::shared_ptr<GameObject> m_pPlayer;
//	};
//
//	class MovingState : public PlayerState
//	{
//	public:
//		MovingState(std::shared_ptr<GameObject> pPlayer);
//		~MovingState() = default;
//
//		MovingState(const MovingState&) = delete;
//		MovingState(MovingState&&) = delete;
//		MovingState& operator= (const MovingState&) = delete;
//		MovingState& operator= (const MovingState&&) = delete;
//
//		void HandleInput() override;
//		void Update() override;
//	private:
//
//	};
//}

