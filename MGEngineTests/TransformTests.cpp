#include "pch.h"
#include "CppUnitTest.h"
#include "../MGEngine/Transform.h"
#include <vector>
#include "../MGEngine/Mesh.h"
#include "../MGEngine/Model.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework {
			template<typename T> static inline std::wstring ToString(const Transform& t)
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
	TEST_CLASS(TransformTest)
	{
		void check_transform(Transform& t, Vector3<float> expPos, Quaternion expRotation, Vector3<float> expScale) {
			Assert::IsTrue(t.get_position().is_equal_approximate(expPos));
			Assert::IsTrue(t.get_scale().is_equal_approximate(expScale));
			Assert::IsTrue(t.get_rotation().to_euler().is_equal_approximate(expRotation.to_euler()));
		}

		std::pair<std::shared_ptr<GameObject>, std::shared_ptr<GameObject>> create_test_objects() {
			auto mesh = std::shared_ptr<GameObject>(GameObject::Instantiate(new GameObject()));
			auto m = GameObject::Instantiate(new GameObject());
			auto model = mesh->add_component(m);

			return std::make_pair(mesh, model);
		}

	public:
		TEST_METHOD(ParentChildrenRelations) {
			auto m_pair = create_test_objects();
			auto first = m_pair.first;
			auto subobject = m_pair.second;

			first->transform.set_local_scale(Vector3<float>(5.0f, 3.0f, 2.0f));
			first->transform.set_position(Vector3<float>(0.0f, 0.0f, 2.0f));
			first->transform.set_local_rotation(Quaternion::from_euler(Vector3<float>(0.f, 1.f, 0.f)));

			subobject->transform.set_local_position(Vector3<float>(5.0f, 0.0f, 0.0f));
			subobject->transform.set_local_scale(Vector3<float>(1.0f, 1.0f, 0.5f));

			Assert::IsTrue(subobject->has_parent());
			Assert::IsTrue(subobject->get_parent().lock().get() == first.get());

			// Expected subobject result:
			// Position: (13.5076, 0, -19.0368), Rotation: (0, 1, 0), Scale: (5, 3, 1)
			check_transform(
				subobject->transform,
				Vector3<float>(13.5076f, 0, -19.0368f),
				Quaternion::from_euler(Vector3<float>(0, 1, 0)),
				Vector3<float>(5, 3, 1)
			);

			first->transform.set_local_rotation(Quaternion::from_euler(Vector3<float>(1.2f, 0.5f, 0.25f)));
			// Expected subobject result:
			// Position: (21.2575, 5.42793, -9.98564), Rotation: (1.2, 0.5, 0.25), Scale: (5, 3, 1)
			check_transform(
				subobject->transform,
				Vector3<float>(21.2575f, 5.42793f, -9.98564f),
				Quaternion::from_euler(Vector3<float>(1.2f, 0.5f, 0.25f)),
				Vector3<float>(5, 3, 1)
			);
		}
	};
}
