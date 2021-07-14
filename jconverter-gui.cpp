#include "convertfromstrings.hpp"
#include "logic.hpp"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedLayout>

#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <limits>
#include <string_view>

template <std::size_t N>
auto to_qstringlist(std::array<std::string_view, N> const& strArray)
    -> QStringList {
  auto qstrlist = QStringList {};
  qstrlist.reserve(static_cast<int>(strArray.size()));
  for (auto const& str : strArray) {
    auto qstr = QString {};
    qstr.reserve(static_cast<int>(str.size()));
    std::transform(str.cbegin(), str.cend(), std::back_inserter(qstr),
                   [](auto const ch) { return QChar {ch}; });
    qstrlist.push_back(qstr);
  }
  return qstrlist;
}

auto main(int argc, char** argv) -> int {
  QApplication converterApp(argc, argv);

  auto unit1 = new QComboBox;
  auto unit2 = new QComboBox;

  auto const distanceQStrings = to_qstringlist(distanceStrings);
  unit1->addItems(distanceQStrings);
  unit2->addItems(distanceQStrings);

  auto button = new QPushButton("Convert");

  auto unit1SpinBox = new QDoubleSpinBox;
  unit1SpinBox->setMaximum(std::numeric_limits<double>::max());
  auto unit1SectionLayout = new QVBoxLayout;
  unit1SectionLayout->addWidget(unit1);
  unit1SectionLayout->addWidget(unit1SpinBox);
  auto unit1Section = new QWidget;
  unit1Section->setLayout(unit1SectionLayout);

  auto unit2Label = new QLabel;
  auto unit2SectionLayout = new QVBoxLayout;
  unit2SectionLayout->addWidget(unit2);
  unit2SectionLayout->addWidget(unit2Label);
  auto unit2Section = new QWidget;
  unit2Section->setLayout(unit2SectionLayout);

  auto layout = new QHBoxLayout;
  layout->addWidget(unit1Section);
  layout->addWidget(unit2Section);
  layout->addWidget(button);
  auto section = new QWidget;
  section->setLayout(layout);
  section->show();

  QObject::connect(button, &QPushButton::clicked, [&] {
    auto const fromUnit = unit1->currentText().toStdString();
    auto const toUnit = unit2->currentText().toStdString();
    auto const value = unit1SpinBox->value();
    auto const maybeResult = convert(fromUnit, toUnit, value);
    if (maybeResult) {
      unit2Label->setText(QString::number(*maybeResult));
    } else {
      unit2Label->setText("ERROR");
    }
  });

  return converterApp.exec();
}
