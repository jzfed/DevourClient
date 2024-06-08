#pragma once

namespace Transform {
	app::Transform* GetTransform(app::GameObject* go);
	app::Vector3 GetPosition(app::Transform* transform);
	app::Quaternion GetRotation(app::Transform* transform);
	app::Vector3 GetForward(app::Transform* transform);
	app::Vector3 GetRight(app::Transform* transform);
	app::Vector3 GetEulerAngles(app::Quaternion rotation);
	app::Quaternion QuaternionEuler(app::Vector3 eulerAngles);
}