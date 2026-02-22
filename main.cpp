#include <icu4x/DecimalFormatter.hpp>
#include <icu4x/Logger.hpp>

#include <print>


int main()
{
    using namespace icu4x;

    // For basic logging
    Logger::init_simple_logger();

    // Create a locale object representing Bangla
    const std::unique_ptr<Locale> locale = Locale::from_string("bn").ok().value();

    std::println("Running test for locale {}", locale->to_string());

    // Create a formatter object with the appropriate settings
    const std::unique_ptr<DecimalFormatter> formatter =
        DecimalFormatter::create_with_grouping_strategy(*locale, DecimalGroupingStrategy::Auto).ok().value();

    // Create a decimal representing the number 1,000,007
    const std::unique_ptr<Decimal> decimal = Decimal::from(1000007);

    // Format it to a string
    std::string out = formatter->format(*decimal);

    // Report formatted value
    std::println("Formatted value is {}", out);
    if (out != "১০,০০,০০৭")
    {
        std::println("Output does not match expected output");
        return 1;
    }

    return 0;
}
