#include "test.c"
#include <assert.h>

void test_admin_creation() {
    int id = create_user_account(true, "hacker");
    assert(is_admin(id) == true);  // 비인증 상태에서 admin 생성 성공
}
