#include <CUnit/Basic.h>
#include "fancytrains.c" // Include your code

void test_optimal(void) {
    int a1[] = {1, 2, 3, 4, 5};
    CU_ASSERT_EQUAL(optimal(5, a1), /* expected result */);

    int a2[] = {5, 4, 3, 2, 1};
    CU_ASSERT_EQUAL(optimal(5, a2), /* expected result */);

    int a3[] = {1};
    CU_ASSERT_EQUAL(optimal(1, a3), /* expected result */);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("Fancy Trains Test Suite", 0, 0);

    CU_add_test(suite, "test of optimal()", test_optimal);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return 0;
}