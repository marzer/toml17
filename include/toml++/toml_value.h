#pragma once
#include "toml_common.h"

namespace toml
{
	template <typename T>
	class value final
		: public node
	{
		static_assert(
			impl::is_value_type<T>,
			"Template type argument must be one of the basic TOML value types"
		);

		private:
			friend class impl::writer<void>;

			template <typename U>
			[[nodiscard]] TOML_ALWAYS_INLINE
			toml::value<U>* value_ptr_from_base() noexcept
			{
				if constexpr (std::is_same_v<T, U>)
					return this;
				else
					return nullptr;
			}

			template <typename U>
			[[nodiscard]] TOML_ALWAYS_INLINE
			const toml::value<U>* value_ptr_from_base() const noexcept
			{
				if constexpr (std::is_same_v<T, U>)
					return this;
				else
					return nullptr;
			}

			T val_;

		public:

			[[nodiscard]] bool is_string() const noexcept override { return std::is_same_v<T, string>; }
			[[nodiscard]] bool is_int() const noexcept override { return std::is_same_v<T, int64_t>; }
			[[nodiscard]] bool is_float() const noexcept override { return std::is_same_v<T, double>; }
			[[nodiscard]] bool is_bool() const noexcept override { return std::is_same_v<T, bool>; }
			[[nodiscard]] bool is_date() const noexcept override { return std::is_same_v<T, date>; }
			[[nodiscard]] bool is_time() const noexcept override { return std::is_same_v<T, time>; }
			[[nodiscard]] bool is_datetime() const noexcept override { return std::is_same_v<T, datetime>; }

			[[nodiscard]] toml::value<string>* as_string() noexcept override { return value_ptr_from_base<string>(); }
			[[nodiscard]] toml::value<int64_t>* as_int() noexcept override { return value_ptr_from_base<int64_t>(); }
			[[nodiscard]] toml::value<double>* as_float() noexcept override { return value_ptr_from_base<double>(); }
			[[nodiscard]] toml::value<bool>* as_bool() noexcept override { return value_ptr_from_base<bool>(); }
			[[nodiscard]] toml::value<date>* as_date() noexcept override { return value_ptr_from_base<date>(); }
			[[nodiscard]] toml::value<time>* as_time() noexcept override { return value_ptr_from_base<time>(); }
			[[nodiscard]] toml::value<datetime>* as_datetime() noexcept override { return value_ptr_from_base<datetime>(); }

			[[nodiscard]] const toml::value<string>* as_string() const noexcept override { return value_ptr_from_base<string>(); }
			[[nodiscard]] const toml::value<int64_t>* as_int() const noexcept override { return value_ptr_from_base<int64_t>(); }
			[[nodiscard]] const toml::value<double>* as_float() const noexcept override { return value_ptr_from_base<double>(); }
			[[nodiscard]] const toml::value<bool>* as_bool() const noexcept override { return value_ptr_from_base<bool>(); }
			[[nodiscard]] const toml::value<date>* as_date() const noexcept override { return value_ptr_from_base<date>(); }
			[[nodiscard]] const toml::value<time>* as_time() const noexcept override { return value_ptr_from_base<time>(); }
			[[nodiscard]] const toml::value<datetime>* as_datetime() const noexcept override { return value_ptr_from_base<datetime>(); }

			[[nodiscard]] node_type type() const noexcept override
			{
					 if constexpr (std::is_same_v<T, string>) return node_type::string;
				else if constexpr (std::is_same_v<T, int64_t>) return node_type::integer;
				else if constexpr (std::is_same_v<T, double>) return node_type::floating_point;
				else if constexpr (std::is_same_v<T, bool>) return node_type::boolean;
				else if constexpr (std::is_same_v<T, date>) return node_type::date;
				else if constexpr (std::is_same_v<T, time>) return node_type::time;
				else if constexpr (std::is_same_v<T, datetime>) return node_type::datetime;
			}

			template <typename... U>
			TOML_NODISCARD_CTOR
			explicit value(U&&... args) TOML_CONDITIONAL_NOEXCEPT(std::is_nothrow_constructible_v<T, U&&...>)
				: val_{ std::forward<U>(args)... }
			{}

			~value() noexcept = default;
	};

	value(const string_char*) -> value<string>;
	value(string_view) -> value<string>;
	value(string) -> value<string>;
	value(bool) -> value<bool>;
	value(float) -> value<double>;
	value(double) -> value<double>;
	value(int8_t) -> value<int64_t>;
	value(int16_t) -> value<int64_t>;
	value(int32_t) -> value<int64_t>;
	value(int64_t) -> value<int64_t>;
	value(uint8_t) -> value<int64_t>;
	value(uint16_t) -> value<int64_t>;
	value(uint32_t) -> value<int64_t>;
}
