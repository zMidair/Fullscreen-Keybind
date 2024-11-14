#include <Geode/Geode.hpp>
#include <geode.custom-keybinds/include/Keybinds.hpp>
#include <Geode/modify/MenuLayer.hpp>
using namespace geode::prelude;
using namespace keybinds;

auto* GM = GameManager::sharedState();
bool isSwitching = false;

void toggleFullscreen()
{
	if(!isSwitching)
    {
        if(GJBaseGameLayer::get()) return;

        isSwitching = true;
        bool CurrentValue = GM->getGameVariable("0025");
        GM->setGameVariable("0025", !CurrentValue);
        GM->reloadAll(true, CurrentValue, true);
    }
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
        "Fullscreen Keybind",
        // Repeatable
        false
    });

	new EventListener([=](InvokeBindEvent* event) {
    	if(!event->isDown()) toggleFullscreen();
	return ListenerResult::Propagate;
    }, InvokeBindFilter(nullptr, "toggle_fullscreen"_spr));
}

struct ModifiedMenuLayer : Modify<ModifiedMenuLayer, MenuLayer>
{
    virtual bool init()
    {
        isSwitching = false;
        return MenuLayer::init();
    }
};