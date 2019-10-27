#include <iostream>
#include <cassert>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedLayout>

auto const MILES_PER_METER = 0.0006213711922;
auto const LBS_PER_GRAM = 0.0022046226218;
auto const FEET_PER_METER = 3.280839895;
auto const INCHES_PER_METER = 39.3700787402;

auto inches_to_meters(double inches) -> double
{
    return inches / INCHES_PER_METER;
}

auto meters_to_inches(double meters) -> double
{
    return meters * INCHES_PER_METER;
}

auto feet_to_meters(double feet) -> double
{
    return feet / FEET_PER_METER;
}

auto meters_to_feet(double meters) -> double
{
    return meters * FEET_PER_METER;
}

auto miles_to_meters(double miles) -> double
{
    return miles / MILES_PER_METER;
}

auto meters_to_miles(double km) -> double
{
    return km * MILES_PER_METER;
}

auto kelvin_to_fahrenheit(double kelvin) -> double
{
    return kelvin * 9. / 5. - 459.67;
}

auto fahrenheit_to_kelvin(double fahrenheit) -> double
{
    return (fahrenheit + 459.67) * 5.0 / 9.0;
}

auto lbs_to_grams(double lbs) -> double
{
    return lbs / LBS_PER_GRAM;
}

auto grams_to_lbs(double grams) -> double
{
    return grams * LBS_PER_GRAM;
}

enum class DistanceUnit {
    METERS,
    MILES,
    FEET,
    INCHES,
};

enum class Convert {
    FROM,
    TO,
};

auto convert_meter(double value, Convert direction, DistanceUnit unit)-> double
{
    switch (unit) {
        case DistanceUnit::METERS: {
            return value;
        } break;
        case DistanceUnit::MILES: {
            return (direction == Convert::FROM) ? miles_to_meters(value) : meters_to_miles(value);
        } break;
        case DistanceUnit::FEET: {
            return (direction == Convert::FROM) ? feet_to_meters(value) : meters_to_feet(value);
        } break;
        case DistanceUnit::INCHES: {
            return (direction == Convert::FROM) ? inches_to_meters(value) : meters_to_inches(value);
        } break;
        default: {
            assert(false);
            return 1.;
        } break;
    }
};

auto main(int argc, char** argv) -> int
{
    QApplication converterApp(argc, argv);

    auto unit1 = new QComboBox;
    auto unit2 = new QComboBox;
    unit1->addItems({ "Meters", "Miles", "Feet", "Inches" });
    unit2->addItems({ "Meters", "Miles", "Feet", "Inches" });

    auto button = new QPushButton("Convert");

    auto layout = new QHBoxLayout;
    layout->addWidget(unit1);
    layout->addWidget(unit2);
    layout->addWidget(button);
    auto section = new QWidget;
    section->setLayout(layout);
    section->show();

    QObject::connect(button, &QPushButton::clicked, [&] {
        auto value1 = convert_meter(1, Convert::FROM, (DistanceUnit) unit1->currentIndex());
        std::cout << value1 << '\n';
        auto value2 = convert_meter(value1, Convert::TO, (DistanceUnit) unit2->currentIndex());
        std::cout << value2 << '\n';
    });

    return converterApp.exec();
}
