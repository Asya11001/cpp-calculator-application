#https://stackoverflow.com/questions/46862737/cmake-qt-uic-failed

cmake_minimum_required(VERSION 3.5)

project(calculator_plus VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON) # To find QCustomPlot folder

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

include_directories(src)
include_directories(src)

set(CALCULATOR_SOURCES
        Model/ExpressionCalculator/common/constants.h
        Model/ExpressionCalculator/common/data_structs.h
        Model/ExpressionCalculator/common/data_types.h
        Model/ExpressionCalculator/common/error_code.h
        Model/ExpressionCalculator/Calculator.cc
        Model/ExpressionCalculator/Calculator.h
        Model/ExpressionCalculator/StackManipulation/StackManipulation.h
        Model/ExpressionCalculator/ShuntingYard/ShuntingYard.cc
        Model/ExpressionCalculator/ShuntingYard/ShuntingYard.h
        Model/ExpressionCalculator/ExpressionTokenizer/ExpressionTokenizer.cc
        Model/ExpressionCalculator/ExpressionTokenizer/ExpressionTokenizer.h
        Model/ExpressionCalculator/ExpressionTokenizer/Validator.cc
        Model/ExpressionCalculator/ExpressionTokenizer/Validator.h
        Model/ExpressionCalculator/Calculation/Calculation.cc
        Model/ExpressionCalculator/Calculation/Calculation.h
        Model/ExpressionCalculator/Calculation/CalculationHandler.h
        Model/ExpressionCalculator/Calculation/CalculationHandlers.cc
        )
set(CREDIT_CALCULATOR_SOURCES
        Model/CreditCalculator/common/constants.h
        Model/CreditCalculator/common/data_structs.h
        Model/CreditCalculator/common/data_types.h
        Model/CreditCalculator/common/error_code.h
        Model/CreditCalculator/Calculator.cc
        Model/CreditCalculator/Calculator.h
        )
set(DEPOSIT_CALCULATOR_SOURCES
        Model/DepositCalculator/common/constants.h
        Model/DepositCalculator/common/data_structs.h
        Model/DepositCalculator/common/data_types.h
        Model/DepositCalculator/common/error_code.h
        Model/DepositCalculator/BaseCalculator/BaseCalculator.cc
        Model/DepositCalculator/BaseCalculator/BaseCalculator.h
        Model/DepositCalculator/Calculator.cc
        Model/DepositCalculator/Calculator.h
        Model/DepositCalculator/Parameters/Parameters.cc
        Model/DepositCalculator/Parameters/Parameters.h
        Model/DepositCalculator/Result/Result.cc
        Model/DepositCalculator/Result/Result.h
        Model/DepositCalculator/utility/utility.h
        Model/DepositCalculator/utility/utility.cc
        Model/DepositCalculator/taxes/taxes.cc
        Model/DepositCalculator/taxes/taxes.h
        Model/DepositCalculator/logger/logger.cc
        Model/DepositCalculator/logger/logger.h
        )

set(MODEL_SOURCES
        Model/Model.cc
        Model/Model.h
        Model/utility.cc
        Model/utility.h
        )
set(CONTROLLER_SOURCES
        Controller/Controller.cc
        Controller/Controller.h)
set(VIEW_SOURCES
        View/common/constants.h
        View/common/error_code.h
        View/common/settings.h
        View/QCustomPlot/QCustomPlot.h
        View/QCustomPlot/QCustomPlot.cc
        View/View.cc
        View/View.h
        View/View.ui
        View/ViewGraph/ViewGraph.cc
        View/ViewGraph/ViewGraph.h
        View/ViewCredit/ViewCredit.cc
        View/ViewCredit/ViewCredit.h
        View/ViewDeposit/ViewDeposit.cc
        View/ViewDeposit/ViewDeposit.h
        View/ViewExpression/ViewExpression.cc
        View/ViewExpression/ViewExpression.h
        View/ViewTabSwitcher/ViewTabSwitcher.cc
        View/ViewTabSwitcher/ViewTabSwitcher.h
        View/style_handler/style_handler.cc
        View/style_handler/style_handler.h
        )

set(PROJECT_SOURCES
        ${CALCULATOR_SOURCES}
        ${CREDIT_CALCULATOR_SOURCES}
        ${DEPOSIT_CALCULATOR_SOURCES}
        ${MODEL_SOURCES}
        ${CONTROLLER_SOURCES}
        ${VIEW_SOURCES}
        main.cc
        View/number_validator/number_validator.cc View/number_validator/number_validator.h View/ViewDeposit/widgets/InterestRateWidget/InterestRateWidget.cc View/ViewDeposit/widgets/TransactionWidget/TransactionWidget.cc View/ViewDeposit/widgets/RefillsWidget/RefillsWidget.cc View/ViewDeposit/widgets/PartialWithdrawalsWidget/PartialWithdrawalsWidget.cc Model/ExpressionCalculator/StackManipulation/StackManipulation.cc)




if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(calculator_plus
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET calculator_plus APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else ()
    if (ANDROID)
        add_library(calculator_plus SHARED
                ${PROJECT_SOURCES} ${UI_HEADERS}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(calculator_plus
                ${PROJECT_SOURCES} ${UI_HEADERS}
                )
    endif ()
endif ()

target_link_libraries(calculator_plus PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)


# target_link_libraries(calculator_plus PRIVATE QCustomPlot)

if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.calculator_plus)
endif ()
set_target_properties(calculator_plus PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
        )
include(GNUInstallDirs)
install(TARGETS calculator_plus
        BUNDLE DESTINATION .
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        )
if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(calculator_plus)
endif ()
