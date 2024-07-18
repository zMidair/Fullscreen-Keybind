#include <Geode/Geode.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/GameManager.hpp>
using namespace geode::prelude;
using namespace keybinds;

auto* GM = GameManager::sharedState();
bool keyDown = false;

void toggleFullscreen(bool down)
{
	if(down && !keyDown)
	{
		// Prevent the user from holding the F11 key, crashing the game
		keyDown = down;

		bool CurrentValue = GM->getGameVariable("0025");
		GM->setGameVariable("0025", !CurrentValue);
		GM->reloadAll(true, CurrentValue, true);
	}
	if(!down && keyDown) keyDown = down;
}

$execute {
    BindManager::get()->registerBindable({
        // ID, should be prefixed with mod ID
        "toggle_fullscreen"_spr,
        // Name
        "Toggle Fullscreen",
        // Description, leave empty for none
        "Toggles the fullscreen setting upon press.",
        // Default binds
        { Keybind::create(KEY_F11, Modifier::None) },
        // Category; use slashes for specifying subcategories. See the
        // Category class for default categories
        "Fullscreen Keybinds"
    });

	new EventListener([=](InvokeBindEvent* event) {
    	toggleFullscreen(event->isDown());
	return ListenerResult::Propagate;
    }, InvokeBindFilter(nullptr, "toggle_fullscreen"_spr));
}