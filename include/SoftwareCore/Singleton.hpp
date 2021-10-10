#pragma once

namespace Core
{
	template<typename Type>
	class Singleton
	{
	public:
		/// The first time this is called, the object is created, it is also properly destroyed after the
		/// program ends.
		static Type& GetInstance()
		{
			static Type instance;
			return instance;
		}
	};
}