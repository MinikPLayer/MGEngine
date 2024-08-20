#include "pch.hpp"
#include <CppUnitTest.h>
#include "../MGEngine/GLFWInput.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace MGEngine
{
	TEST_CLASS(InputTests)
	{
	public:
		TEST_METHOD(GLFWInputMappingTest) {
			int min = 0;
			int max = (int)KeyboardKeys::KEY_LAST;

			for (int i = 0; i <= max; i++) {
				auto key = (KeyboardKeys)i;
				auto glfwKey = GLFWInputBackend::get_glfw_key_map(key);

				if (glfwKey == -1) {
					std::wstringstream ss;
					ss << "Key " << (int)key << " not found in GLFW mapping";
					Assert::Fail(ss.str().c_str());
				}

			}
		}
	};
}
