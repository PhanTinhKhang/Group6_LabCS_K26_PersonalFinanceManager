#include <iostream>
#include <cassert>
#include "../include/Date.h"
#include "../include/DynamicArray.h"

void testConstructorsAndSetters() {
    std::cout << "[TEST 1] Constructors & Setters:\n";

    // Mặc định: 01/01/2026
    Date dDefault;
    assert(dDefault.getDay() == 1 && dDefault.getMonth() == 1 && dDefault.getYear() == 2026);

    // Năm nhuận thế kỷ
    assert(Date::isLeapYear(2000) == true);
    assert(Date::isLeapYear(1900) == false);
    assert(Date::isLeapYear(2024) == true);
    assert(Date::isLeapYear(2026) == false);

    // Số ngày trong tháng
    assert(Date::getDaysInMonth(2, 2024) == 29);
    assert(Date::getDaysInMonth(2, 2026) == 28);
    assert(Date::getDaysInMonth(4, 2026) == 30);
    assert(Date::getDaysInMonth(12, 2026) == 31);

    // Setter từ chối dữ liệu không hợp lệ
    Date d;
    assert(d.setDate(0, 5, 2026) == false);    // Ngày 0
    assert(d.setDate(32, 5, 2026) == false);   // Ngày 32
    assert(d.setDate(15, 13, 2026) == false);  // Tháng 13
    assert(d.setDate(29, 2, 2026) == false);   // 29/02 năm không nhuận
    assert(d.setDate(29, 2, 2024) == true);    // 29/02 năm nhuận -> thành công

    std::cout << " -> PASS\n\n";
}

void testComparisonsAndRange() {
    std::cout << "[TEST 2] So sanh & Loc khoang thoi gian (Statistics Module):\n";

    Date d1(10, 5, 2026);
    Date d2(15, 5, 2026);
    Date d3(10, 6, 2026);
    Date d4(10, 5, 2027);
    Date dSame(10, 5, 2026);

    // Kiểm tra isBefore
    assert(d1.isBefore(d2) == true);  // Cùng tháng năm, ngày nhỏ hơn
    assert(d1.isBefore(d3) == true);  // Cùng năm, tháng nhỏ hơn
    assert(d1.isBefore(d4) == true);  // Năm nhỏ hơn
    assert(d2.isBefore(d1) == false);
    assert(d1.isBefore(dSame) == false);

    // Kiểm tra isEqual
    assert(d1.isEqual(dSame) == true);
    assert(d1.isEqual(d2) == false);

    // Kiểm tra isInRange (bao gồm mốc biên)
    Date from(1, 5, 2026);
    Date to(31, 5, 2026);

    assert(d1.isInRange(from, to) == true);
    assert(from.isInRange(from, to) == true);
    assert(to.isInRange(from, to) == true);
    assert(d3.isInRange(from, to) == false);

    std::cout << " -> PASS\n\n";
}

void testRecurringCheck() {
    std::cout << "[TEST 3] Kiem tra chu ky thang (Recurring Module) voi const Date& other:\n";

    Date txDate(15, 11, 2026);
    Date currentMonthTarget(1, 11, 2026);  // Cùng tháng 11/2026
    Date lastMonthTarget(30, 10, 2026);    // Khác tháng (tháng 10/2026)
    Date lastYearTarget(15, 11, 2025);     // Khác năm (11/2025)

    // Kiểm tra trực tiếp bằng tham chiếu đối tượng Date
    assert(txDate.isSameMonth(currentMonthTarget) == true);
    assert(txDate.isSameMonth(lastMonthTarget) == false);
    assert(txDate.isSameMonth(lastYearTarget) == false);

    std::cout << " -> PASS\n\n";
}

void testStringParsing() {
    std::cout << "[TEST 4] toString & fromString (Input & CLI View):\n";

    // Test toString có chèn số 0
    Date dSingleDigit(5, 4, 2026);
    assert(dSingleDigit.toString() == "05/04/2026");

    // Test fromString các trường hợp hợp lệ
    Date parsed1 = Date::fromString("20/11/2026");
    assert(parsed1.getDay() == 20 && parsed1.getMonth() == 11 && parsed1.getYear() == 2026);

    Date parsed2 = Date::fromString("5-4-2026"); // Dấu gạch ngang
    assert(parsed2.getDay() == 5 && parsed2.getMonth() == 4 && parsed2.getYear() == 2026);

    Date parsed3 = Date::fromString("  15 / 08 / 2026  "); // Có khoảng trắng
    assert(parsed3.getDay() == 15 && parsed3.getMonth() == 8 && parsed3.getYear() == 2026);

    // Test fromString trường hợp nhập sai -> fallback an toàn 01/01/2026
    Date bad1 = Date::fromString("31/02/2026");
    assert(bad1.getDay() == 1 && bad1.getMonth() == 1 && bad1.getYear() == 2026);

    Date bad2 = Date::fromString("chuoi_lung_tung");
    assert(bad2.getDay() == 1 && bad2.getMonth() == 1 && bad2.getYear() == 2026);

    Date bad3 = Date::fromString("10/10"); // Thiếu năm
    assert(bad3.getDay() == 1 && bad3.getMonth() == 1 && bad3.getYear() == 2026);

    std::cout << " -> PASS\n\n";
}

void testIntegrationWithDynamicArray() {
    std::cout << "[TEST 5] Tich hop Date voi DynamicArray (Task 2 + Task 3):\n";

    DynamicArray<Date> dateList;
    dateList.push(Date(1, 1, 2026));
    dateList.push(Date(15, 6, 2026));
    dateList.push(Date(31, 12, 2026));
    dateList.push(Date(20, 11, 2026));
    dateList.push(Date(2, 9, 2026)); // Kích hoạt resize từ capacity 4 -> 8

    assert(dateList.getSize() == 5);
    assert(dateList[0].toString() == "01/01/2026");
    assert(dateList[4].toString() == "02/09/2026");

    // Test xóa phần tử
    Date removed = dateList.pop(1); // Xóa 15/06/2026
    assert(removed.toString() == "15/06/2026");
    assert(dateList.getSize() == 4);
    assert(dateList[1].toString() == "31/12/2026"); // Các phần tử sau dồn lên

    std::cout << "Danh sach ngay con lai trong DynamicArray:\n";
    for (int i = 0; i < dateList.getSize(); ++i) {
        std::cout << "  [" << i << "] " << dateList[i] << "\n";
    }

    std::cout << " -> PASS\n\n";
}

int main() {
    std::cout << "========================================\n";
    std::cout << " BAT DAU KIEM THU TOAN DIEN STRUCT/CLASS DATE\n";
    std::cout << "========================================\n\n";

    testConstructorsAndSetters();
    testComparisonsAndRange();
    testRecurringCheck();
    testStringParsing();
    testIntegrationWithDynamicArray();

    std::cout << ">>> TAT CA CAC TEST CASES DEU HOAT DONG CHINH XAC 100%! <<<\n";
    return 0;
}
//g++ test/test_date_full.cpp src/Date.cpp -Iinclude -o test/test_date_full.exe 
// ./test/test_date_full.exe

/*
========================================
 BAT DAU KIEM THU TOAN DIEN STRUCT/CLASS DATE
========================================

[TEST 1] Constructors & Setters:
 -> PASS

[TEST 2] So sanh & Loc khoang thoi gian (Statistics Module):
 -> PASS

[TEST 3] Kiem tra chu ky thang (Recurring Module) voi const Date& other:
 -> PASS

[TEST 4] toString & fromString (Input & CLI View):
 -> PASS

[TEST 5] Tich hop Date voi DynamicArray (Task 2 + Task 3):
Danh sach ngay con lai trong DynamicArray:
  [0] 01/01/2026
  [1] 31/12/2026
  [2] 20/11/2026
  [3] 02/09/2026
 -> PASS

>>> TAT CA CAC TEST CASES DEU HOAT DONG CHINH XAC 100%! <<<*/