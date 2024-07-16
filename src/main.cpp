#include <Geode/Geode.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/GameManager.hpp>
using namespace geode::prelude;

auto* GM = GameManager::sharedState();

struct ModifiedCCKeyboardDispatcher : Modify<ModifiedCCKeyboardDispatcher, CCKeyboardDispatcher>
{
	bool dispatchKeyboardMSG(enumKeyCodes key, bool down, bool arr)
	{
		if(down && key == KEY_F11)
		{
			bool CurrentValue = GM->getGameVariable("0025");
			GM->setGameVariable("0025", !CurrentValue);
			GM->reloadAll(true, CurrentValue, true);
		}

		return CCKeyboardDispatcher::dispatchKeyboardMSG(key, down, arr);
	}
};