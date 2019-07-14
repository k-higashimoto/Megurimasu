/**
* @file aligned_allocator.inl
* @brief AlignedAllocatorŽÀ‘•ƒtƒ@ƒCƒ‹
*/

namespace sup
{
inline namespace cpp
{
//----------------------------------------------------------------------------------------------------------------------------------------------------
//class imple
	template<typename T, size_t Align>
	template<typename U>
	AlignedAllocator<T, Align>::AlignedAllocator(const AlignedAllocator<U, Align>& obj)noexcept
	{
	}

	template<typename T, size_t Align>
	T* AlignedAllocator<T, Align>::allocate(std::size_t n)
	{
	#if defined(_MSC_VER) || defined(__MINGW32__)
		return reinterpret_cast<T*>(_aligned_malloc(sizeof(T) * n, Align));
	#else
		void* p;
		return reinterpret_cast<T*>(posix_memalign(&p, Align, sizeof(T) * n) == 0 ? p : nullptr);
	#endif
	}

	template<typename T, size_t Align>
	void AlignedAllocator<T, Align>::deallocate(T* p, std::size_t n)
	{
	#if defined(_MSC_VER) || defined(__MINGW32__)
		_aligned_free(p);
	#else
		std::free(ptr);
	#endif
	}

//----------------------------------------------------------------------------------------------------------------------------------------------------
//compare override imple
	template <typename T, typename U, size_t Align>
	bool operator==(const sup::cpp::AlignedAllocator<T, Align>&, const sup::cpp::AlignedAllocator<U, Align>&)noexcept
	{
		return true;
	}

	template <typename T, typename U, size_t Align>
	bool operator!=(const sup::cpp::AlignedAllocator<T, Align>&, const sup::cpp::AlignedAllocator<U, Align>&)noexcept
	{
		return false;
	}
}
}