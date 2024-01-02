#pragma once
#include <functional>
#include <vector>

template<typename Sender, typename... Args>
class Event {
	std::vector<std::function<void(Sender, Args...)>> callbacks;

public:
	void operator+=(std::function<void(Sender, Args...)> callback) {
		callbacks.push_back(callback);
	}

	void operator-=(std::function<void(Sender, Args...)> callback) {
		for (auto it = callbacks.begin(); it != callbacks.end(); ++it) {
			if (*it == callback) {
				callbacks.erase(it);
				break;
			}
		}
	}

	void operator()(Sender sender, Args... args) {
		for (auto& callback : callbacks) {
			callback(sender, args...);
		}
	}
};