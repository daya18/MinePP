#pragma once

#include "Scene.hpp"

namespace mpp
{
	class Application;
	class Window;

	class MainMenu : public Scene
	{
	public:
		MainMenu ( Application & );

		void Render () override;
		void RenderGUI () override;
		void Update ( float delta ) override;

	private:
		Application * application;
	};
}