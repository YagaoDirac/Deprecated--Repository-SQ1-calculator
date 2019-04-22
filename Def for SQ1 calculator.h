#pragma once

enum class sq1ReturnValue
{
	ok,
	bad_param,
	failed,

	//only for layerData::flip()
	this_function_is_only_allowed_to_be_called_through_upper_layer

};