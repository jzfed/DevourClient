#pragma once

namespace Transform {
	app::Transform* Get(app::GameObject* go);
	app::Vector3 Position(app::Transform* transform);
}