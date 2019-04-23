#pragma once

//暂时没用上。之后代码规范化的时候再弄
enum class LayerData_ReturnValue
{
	False = 0,
	True = 1,
	ok = 2,
	bad_param = -1,
	failed = -2,

	//only for layerData::flip()
	this_function_is_only_allowed_to_be_called_through_upper_layer = -101,

	//call check() or removeAllRepeatIndependently() before call this function, and make sure the inner data is available for further usage
	dirty = -102,

	//upper layer is not able to rotate at this position. Call isAbleToRotateAt()to check.
	upper_layer_is_not_able_to_rotate_at_this_position = -103,

	//lower layer is not able to rotate at this position. Call isAbleToRotateAt()to check.
	lower_layer_is_not_able_to_rotate_at_this_position = -104,

};