#include "IInputBackend.hpp"

Vector2f IInputBackend::get_scroll_value() {
    return scroll_value;
}

void IInputBackend::_scroll_callback_(Vector2f scrollDelta) {
    scroll_value = Vector2f(scroll_value.x + scrollDelta.x, scroll_value.y + scrollDelta.y);
}

Vector2f IInputBackend::scroll_value = Vector2f::zero();