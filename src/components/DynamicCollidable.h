#pragma once

namespace tag
{
	// This is a tag to indicate that the solver is allowed to update
	// the position of the entity, and that it's not just a map static.
	struct DynamicCollidable
	{
	};
}
