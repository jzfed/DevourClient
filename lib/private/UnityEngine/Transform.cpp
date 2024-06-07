#include "pch-il2cpp.h"

#include "UnityEngine/Transform.h"

app::Transform* Transform::Get(app::GameObject* go)
{
	if (!go || !app::GameObject_get_transform) return nullptr;

	app::Transform* __transform = app::GameObject_get_transform(go, nullptr);

	return __transform ? __transform : nullptr;
}

app::Vector3 Transform::Position(app::Transform* transform)
{
	if (!transform || !app::Transform_get_position) return app::Vector3();

	return app::Transform_get_position(transform, nullptr);
}
