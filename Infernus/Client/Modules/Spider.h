#pragma once
#include "../../Other/VComponent.h"

class Spider : public VModule {
public:
	Spider() : VModule::VModule("Spider", "Automatically ascend upwards on contact with surfaces") {
		this->addWindowObj(new VWindowSlider("Y Speed: ", &this->speed));
	};
	void onGmTick();
private:
	float speed = 0.3f;
};

void Spider::onGmTick() {
	BunnyHop* BhopMod = (BunnyHop*)ClientHandler::GetModule(BunnyHop());
	LocalPlayer* Player = Minecraft::GetLocalPlayer();
	if (Player != nullptr) {
		if (Player->toActor()->isCollidedDir() && BhopMod->usingKeys()) {
			Player->Velocity.y = speed;
		};
	};
};