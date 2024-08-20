#include "IRenderer.hpp"
#include "Input.hpp"

bool IRenderer::poll_events() {
	auto result = _poll_events_();
	Input::update();

	return result;
}
