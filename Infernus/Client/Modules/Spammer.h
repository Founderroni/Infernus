#pragma once
#include "../../Other/VComponent.h"

class Spammer : public VModule {
public:
	Spammer() : VModule::VModule("Spammer", "Automatically Spam in the Chat") {
		VWindowSlider* spamDelaySlider = new VWindowSlider("Delay (MS): ", &delay_ms);
		spamDelaySlider->max = 1000.f;
		this->addWindowObj(spamDelaySlider);
	};
	void onGmTick();
public:
	float delay_ms = 0.0f;
	std::string message = std::string("Spammer is enabled, Change message via .spam <message>");
	std::chrono::time_point<std::chrono::steady_clock> savedTime;
};

void Spammer::onGmTick() {
	if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - savedTime) >= std::chrono::milliseconds((int)(delay_ms))) {
		LocalPlayer* Player = Minecraft::GetLocalPlayer();
		if (Player != nullptr) {
			int randomInt = (int)Utils::randomFloat(0, 100);
			std::string brackets = std::string("[ " + std::to_string(randomInt) + " ]");
			std::string modifiedMsg = brackets + std::string(" " + this->message + " ") + brackets;

			TextPacket newPacket(Minecraft::GetLocalPlayer()->toActor(), modifiedMsg);
			Minecraft::GetClientInstance()->LoopbackPacketSender->sendToServer(&newPacket);
		};
		savedTime = std::chrono::high_resolution_clock::now();
	};
};