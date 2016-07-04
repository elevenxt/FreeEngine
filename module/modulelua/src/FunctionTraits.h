/*
** Free game server engine
**
** Copyright (C) 2016 Eleven. See Copyright Notice in base.h
*/



#ifndef __US_FUNC_TRAINTS
#define __US_FUNC_TRAINTS

namespace ff
{
	template<typename F>
	struct function_traits;

	template<typename R, typename ...Args>
	struct function_traits<R(Args...)>
	{
		using return_type = R;
		using arguments = std::tuple<Args...>;
	};

	// 函数
	template<typename R, typename ...Args>
	struct function_traits<R(*)(Args...)> : function_traits<R(Args...)>{};

	// 成员函数
	template<typename C, typename R, typename ...Args>
	struct function_traits<R(C::*)(Args...)> : function_traits<R(C&, Args...)>
	{
	};

	// const成员函数
	template<typename C, typename R, typename ...Args>
	struct function_traits<R(C::*)(Args...) const> : function_traits<R(C const&, Args...)>
	{
	};

	// volatile成员函数
	template<typename C, typename R, typename ...Args>
	struct function_traits<R(C::*)(Args...) volatile> : function_traits<R(C volatile&, Args...)>
	{
	};

	// const volatile成员函数
	template<typename C, typename R, typename ...Args>
	struct function_traits<R(C::*)(Args...) const volatile> : function_traits<R(C const volatile&, Args...)>
	{
	};

	template<typename T>
	using is_function_pointer = std::is_function<typename std::remove_pointer<T>::type>;

	template<typename F>
	using is_void_return = std::is_same<void, typename function_traits<F>::return_type>;
	/////////////////////////////////////////////////////////////////////////////
	template<size_t... I>
	struct integer_sequence
	{
		static size_t size() { return sizeof...(I); }
		using next = integer_sequence<I..., sizeof...(I)>;
	};

	template<size_t N>
	struct sequence_generator
	{
		using type = typename sequence_generator<N - 1>::type::next;
	};

	template<>
	struct sequence_generator<0ul>
	{
		using type = integer_sequence<>;
	};

	template<size_t... I>
	using index_sequence = integer_sequence<I...>;

	template<size_t N>
	using make_integer_sequence = typename sequence_generator<N>::type;

	template<size_t N>
	using make_index_sequence = make_integer_sequence<N>;

	/////////////////////////////////////////////////
	template<typename T>
	using is_pointer_cast_allowed = std::integral_constant<bool, sizeof(T) <= sizeof(void*)>;

	template<typename T>
	union pointer_cast
	{
	private:
		void* ptr;
		T value;

	public:
		static_assert(is_pointer_cast_allowed<T>::value,
			"data size should be not greater than pointer size");

		explicit pointer_cast(void* ptr) : ptr(ptr) {}
		explicit pointer_cast(T value) : value(value) {}

		operator void*() const { return ptr; }
		operator T() const { return value; }
	};
}

#endif