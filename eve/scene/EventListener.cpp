
// Main header
#include "eve/scene/EventListener.h"


//=================================================================================================
eve::scene::EventListenerScene::EventListenerScene(void)
	: eve::evt::Listener()
{}



//=================================================================================================
eve::scene::EventListenerSceneObject::EventListenerSceneObject(void)
	: eve::evt::Listener()
{}



//=================================================================================================
eve::scene::EventListenerSceneMaterial::EventListenerSceneMaterial(void)
	: eve::evt::Listener()
{}



//=================================================================================================
eve::scene::EventListenerSceneCamera::EventListenerSceneCamera(void)
	: eve::scene::EventListenerSceneObject()
{}



//=================================================================================================
eve::scene::EventListenerSceneLight::EventListenerSceneLight(void)
	: eve::scene::EventListenerSceneObject()
{}
