#pragma once

namespace mpp
{
	class Scene
	{
	public:
		virtual void Render () {};
		virtual void RenderGUI () {};
		virtual void Update ( float delta ) {};
	};
}