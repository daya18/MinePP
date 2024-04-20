#pragma once

namespace mpp
{
	class Scene
	{
	public:
		virtual void Render () {};
		virtual void RenderImGui () {};
		virtual void Update ( float delta ) {};
	};
}