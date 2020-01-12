#include "tests.h"

TEST_CASE("lifetime - tables")
{
	static constexpr auto filename = "foo.toml"sv;

	parsing_should_succeed(
		S(R"(test = { val1 = "foo" })"sv),
		[&](table&& tbl) noexcept
		{
			CHECK(tbl.source().begin == source_position{ 1, 1 });
			CHECK(tbl.source().end == source_position{ 1, 25 });
			CHECK(tbl.source().path);
			CHECK(*tbl.source().path == filename);
			CHECK(tbl.size() == 1_sz);
			REQUIRE(tbl[S("test")].as<table>());
			CHECK(tbl[S("test")].as<table>()->size() == 1_sz);
			CHECK(tbl[S("test")][S("val1")] == S("foo"sv));

			table test_table;
			CHECK(test_table.source().begin == source_position{});
			CHECK(test_table.source().end == source_position{});
			CHECK(!test_table.source().path);
			CHECK(test_table.size() == 0_sz);
			CHECK(!test_table[S("test")].as<table>());

			test_table = std::move(tbl);
			CHECK(test_table.source().begin == source_position{ 1, 1 });
			CHECK(test_table.source().end == source_position{ 1, 25 });
			CHECK(test_table.source().path);
			CHECK(*test_table.source().path == filename);
			CHECK(test_table.size() == 1_sz);
			REQUIRE(test_table[S("test")].as<table>());
			CHECK(test_table[S("test")].as<table>()->size() == 1_sz);
			CHECK(test_table[S("test")][S("val1")] == S("foo"sv));
		},
		filename
	);
	
}