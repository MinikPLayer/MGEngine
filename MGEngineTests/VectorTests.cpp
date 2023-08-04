#include "pch.h"
#include "CppUnitTest.h"
#include "../MGEngine/Vector3.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<typename T> static inline std::wstring ToString(const Vector3<T>& t)
			{
				// Write some code here to create a descriptive std::wstring
				auto str = t.to_string();
				return std::wstring(str.begin(), str.end());
			}

		}
	}
}

namespace MGEngine
{
	TEST_CLASS(VectorTests)
	{
	public:
		template<typename T>
		void testAdd() {
			Vector3<T> v1((T)1.1, (T)2.2, (T)3.3);
			Vector3<T> v2((T)4.3, (T)6.2, (T)1.1);

			Vector3<T> v3 = v1 + v2;
			Assert::IsTrue(v3.is_equal_exact(Vector3<T>((T)5.4, (T)8.4, (T)4.4)));
		}

		template<typename T>
		void testDot(T x, T y, T z, T x2, T y2, T z2, float expected) {
			Vector3<T> v1(x, y, z);
			Vector3<T> v2(x2, y2, z2);

			float dot = v1.dot(v2);
			Assert::AreEqual(expected, dot);
		}

		template<typename T>
		void testCross(T x1, T y1, T z1, T x2, T y2, T z3, T retX, T retY, T retZ) {
			Vector3<T> v1(x1, y1, z1);
			Vector3<T> v2(x2, y2, z3);

			Vector3<T> cross = v1.cross(v2);
			Assert::IsTrue(Vector3<T>(retX, retY, retZ).is_equal_approximate(cross));
		}

		TEST_METHOD(Add)
		{
			testAdd<int>();
			testAdd<float>();
			testAdd<double>();
			testAdd<long long>();
		}

		TEST_METHOD(Dot)
		{
			testDot<int>(1, 2, 3, 4, 6, 1, 19.f);
			testDot<float>(1.1, 2.1, 3.7, 4.2, 6.9, 9.0, 52.41f);
		}

		TEST_METHOD(Cross) {
			testCross<int>(1, 2, 3, 4, 6, 1, -16, 11, -2);
			testCross<float>(1.1, 2.1, 3.7, 4.2, 6.9, 9.0, -6.63, 5.64, -1.23);
		}

		TEST_METHOD(EqualTest) {
			Vector3<float> v1(1000.0f, 1000.0f, 1000.0f);

			for (float f = 0; f < 1.0f; f += 0.000001f) {
				auto v2 = v1 + Vector3<float>(f, f, f);
				if (!v2.is_equal_approximate(v1)) {
					std::stringstream ss;
					ss << "Not equal after " << f << "f" << " (" << f * 100.f / v1.x << "%)";
					Logger::WriteMessage(ss.str().c_str());
					return;
				}
			}

			Assert::Fail(L"Test failed, no difference found after 1.0f");
		}
	};
}
