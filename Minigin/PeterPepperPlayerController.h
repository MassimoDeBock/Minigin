#pragma once
#include "BasePlayerController.h"

namespace dae {
	class PeterPepperPlayerController final : public BasePlayerController 
	{
	public:
		PeterPepperPlayerController(const int playerID);
		virtual ~PeterPepperPlayerController();
		void Update() override;
		void Render() const override;
		void BeginPlay() override;

	private:

	};
}