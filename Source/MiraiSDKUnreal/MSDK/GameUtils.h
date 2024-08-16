#pragma once

class GameUtils
{
public:
template <typename T>
	static FString EnumToString(T EnumValue)
	{
		// static_assert(TIsUEnumClass<T>::Value, "'T' template parameter to EnumToString must be a valid UEnum");
		return StaticEnum<T>()->GetNameStringByValue((int64) EnumValue);
	}
};
