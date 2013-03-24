#include"test.h"

void pass(char* test_name, char* message) 
{
    printf("%s pass: %s", test_name, message);
}
void fail(char* test_name, char* message) 
{
    printf("%s FAIL: %s", test_name, message);
}

void run_test(char* name, int (*test)(char*), char* input_data_path) 
{
    printf("############## %s ##############\n", name);
    test(input_data_path);
    printf("############## End of test %s ##############\n", name);
}

void self_test(char* input_data_path) 
{
    run_test("test1", &test1, input_data_path);
	run_test("test2", &test2, input_data_path);
	run_test("test3", &test3, input_data_path);
	run_test("test4", &test4, input_data_path);
	run_test("test6 - test math function processing", &test6_math, input_data_path);
}

