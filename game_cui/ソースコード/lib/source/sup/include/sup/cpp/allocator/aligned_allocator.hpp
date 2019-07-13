/**
* @file aligned_allocator.hpp
* @brief アライメント指定可能なアロケータ実装ファイル
*/

#ifndef SUP_LIB_CPP_ALIGNED_ALLOCATOR_HPP
#define SUP_LIB_CPP_ALIGNED_ALLOCATOR_HPP

#include <new>

namespace sup
{
inline namespace cpp
{
//----------------------------------------------------------------------------------------------------------------------------------------------------
//class declare
	/**
	* @class AlignedAllocator
	* @brief stl用アライメント指定可能なアロケータ－
	*/
	template<typename T, size_t Align>
	class AlignedAllocator
	{
	public:
		using value_type = T;

	public:
		template<typename U>
		struct rebind
		{
			using other = AlignedAllocator<U, Align>;
		};

	public:
		AlignedAllocator()noexcept = default;

	public:
		template<typename U>
		AlignedAllocator(const AlignedAllocator<U, Align>&)noexcept;

	public:
		T* allocate(std::size_t n);
		void deallocate(T* p, std::size_t n);
	};

//----------------------------------------------------------------------------------------------------------------------------------------------------
//compare override
	template <typename T, typename U, size_t Align>
	bool operator==(const AlignedAllocator<T, Align>&, const AlignedAllocator<U, Align>&)noexcept;

	template <typename T, typename U, size_t Align>
	bool operator!=(const AlignedAllocator<T, Align>&, const AlignedAllocator<U, Align>&)noexcept;
}
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//include imple file
#include<sup/cpp/allocator/aligned_allocator.inl>

#endif